// Fill out your copyright notice in the Description page of Project Settings.


#include "MySqlObject.h"

mysqlx::Row UMySqlObject::make_row_data_from_string(FString & inData)
{
	TArray<FString> data_list;
	inData.ParseIntoArray(data_list,TEXT(","), false);
	UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:find %d data"), __FUNCTIONW__, __LINE__, data_list.Num());
	// str 0/-1 , int 1 , float 2
	TArray<int64> is_num;
	is_num.AddZeroed(data_list.Num());
	UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:add zeroed data finish, num is %d"), __FUNCTIONW__, __LINE__, is_num.Num());
	TArray<uint32> int_list;
	int_list.AddZeroed(data_list.Num());
	TArray<float> float_list;
	float_list.AddZeroed(data_list.Num());
	// check data
	for (int32 i = 0; i < data_list.Num(); ++i)
	{
		// is str
		if (data_list[i].StartsWith(TEXT("'")) && data_list[i].EndsWith(TEXT("'")))
		{
			data_list[i].ReplaceInline(TEXT("'"),TEXT(""));
			is_num[i] = 0;
		}
		// is float
		else if (data_list[i].EndsWith(TEXT("f")))
		{
			is_num[i] = 2;
			float_list[i] = FCString::Atof(*data_list[i]);
		}
		// is int
		else if (data_list[i].IsNumeric())
		{
			int_list[i] = FCString::Atoi64(*data_list[i]);
			is_num[i] = 1;
		}
		// is null
		else if (data_list[i].Compare(TEXT("null")) == 0 || data_list[i].Len() == 0)
		{
			is_num[i] = -2;
		}
		else
		{
			is_num[i] = -1;
		}
	}


	mysqlx::Row row = mysqlx::Row();
	UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:-----------------------------------------"), __FUNCTIONW__, __LINE__);
	for (int32 m = 0; m < is_num.Num(); ++m)
	{
		// str
		if (is_num[m] == 0 || is_num[m] == -1)
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:str value :%s"), __FUNCTIONW__, __LINE__, *data_list[m]);
			row.set(m, to_std_string(data_list[m]));
		}
		// int
		else if (is_num[m] == 1)
		{
			row.set(m, int_list[m]);
			UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:int value :%d"), __FUNCTIONW__, __LINE__, int_list[m]);
		}
		// is null
		else if (is_num[m] == -2)
		{
			row.set(m, mysqlx::Value());
			UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:int value :null value"), __FUNCTIONW__, __LINE__);
		}
		else // float
		{
			row.set(m, float_list[m]);
			UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:float value:%f"), __FUNCTIONW__, __LINE__, float_list[m]);
		}
	}
	return row;
}

void UMySqlObject::UpdateSqlConnect(FString host, int32 port, FString user, FString pwd)
{
	_sql_connect_info.Host = host;
	_sql_connect_info.Port = port;
	_sql_connect_info.User = user;
	_sql_connect_info.Pwd = pwd;
}

void UMySqlObject::SetLibName(FString sqlLibName)
{
	_sql_lib_name = to_std_string(sqlLibName);
}

FSqlExecResult UMySqlObject::ExecSql(FString sqlCode)
{
	FSqlExecResult exec_result;
	try
	{
		// create session
		mysqlx::Session session(mysqlx::SessionSettings(
			to_std_string(_sql_connect_info.Host),
			_sql_connect_info.Port,
			to_std_string(_sql_connect_info.User),
			to_std_string(_sql_connect_info.Pwd)));
		// use this lib
		session.sql(std::string("use ").append(_sql_lib_name)).execute();
		// exec sql code
		mysqlx::SqlResult result = session.sql(to_std_string(sqlCode)).execute();
		if (result.hasData())
		{
			// set
			exec_result.hasData = true;
			// 
			UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:execute success , find %d datas"), __FUNCTIONW__, __LINE__, result.count());
			int32 col_count = result.getColumnCount();
			// set
			exec_result.colNum = col_count;
			// 
			UE_LOG(LogTemp, Warning, TEXT("[%s::%d]:has %d column"), __FUNCTIONW__, __LINE__, col_count);
			auto datas = result.fetchAll();
			int32 num = 0;
			for (auto it = datas.begin(); it != datas.end(); ++it)
			{
				num++;
				// create new row
				FSqlRow row;
				for (int32 i = 0; i < col_count; ++i)
				{
					FSqlData data;
					data.value = (*it)[i];
					row.data.Add(data);
				}
				// set
				exec_result.dataNum = num;
				exec_result.rowList.Add(row);
			}
		}
		else
		{
			exec_result.hasData = false;
		}
		exec_result.bSuccess = true;
		// close
		session.close();

		return exec_result;
	}
	catch (const std::exception& e)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s::%d]:%s"), __FUNCTIONW__, __LINE__, UTF8_TO_TCHAR(e.what()));
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:catch the exception , test is exec this ?"),__FUNCTIONW__,__LINE__);
		exec_result.bSuccess = false;
		return exec_result;
	}
}


void UMySqlObject::InsertData(FString tableName, FString insertData)
{
	if (insertData.Len() <= 0)
	{
		return;
	}
	try
	{
		// create
		mysqlx::Session session(mysqlx::SessionSettings(
			to_std_string(_sql_connect_info.Host),
			_sql_connect_info.Port,
			to_std_string(_sql_connect_info.User),
			to_std_string(_sql_connect_info.Pwd)));
		session.sql(std::string("use ").append(_sql_lib_name)).execute();
		// get lib
		mysqlx::Schema current_schema = session.getSchema(_sql_lib_name);
		// get table
		mysqlx::Table current_table = current_schema.getTable(to_std_string(tableName));
		// insert
		current_table.insert().values(make_row_data_from_string(insertData)).execute();
		session.close();
	}
	catch (const std::exception& e)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s::%d]:%s"), __FUNCTIONW__, __LINE__, UTF8_TO_TCHAR(e.what()));
	}
}
