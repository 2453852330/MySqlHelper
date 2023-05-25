// Fill out your copyright notice in the Description page of Project Settings.


#include "MySqlHelperLib.h"


bool UMySqlHelperLib::GetBool(const FSqlData& data)
{
	return data.value.get<bool>();
}

float UMySqlHelperLib::GetFloat(const FSqlData& data)
{
	return data.value.get<float>();
}

int UMySqlHelperLib::GetInt(const FSqlData& data)
{
	return data.value.get<int>();
}

FString UMySqlHelperLib::GetString(const FSqlData& data)
{
	std::string str = data.value.get<std::string>();
	return FString(UTF8_TO_TCHAR(str.c_str()));
}

void UMySqlHelperLib::DebugRow(const FSqlRow& Row)
{
	FString tmp = TEXT("(");
	for (int32 i = 0; i < Row.data.Num(); ++i)
	{
		switch (Row.data[i].value.getType())
		{
		case mysqlx::Value::VNULL:
			{
				tmp += TEXT("null,");
				break;
			}
		case mysqlx::Value::INT64:
			{
				tmp += FString::FromInt(GetInt(Row.data[i])) + TEXT("[NULL],");
				break;
			}
		case mysqlx::Value::BOOL:
			{
				tmp += FString(GetBool(Row.data[i])?TEXT("True"):TEXT("False")) + TEXT("[BOOL],");
				break;
			}
		case mysqlx::Value::FLOAT:
			{
				tmp += FString::SanitizeFloat(GetFloat(Row.data[i])) + TEXT("[FLOAT],");
				break;
			}
		case mysqlx::Value::STRING:
			{
				tmp += GetString(Row.data[i]) + TEXT("[STIRNG],");
				break;
			}
		default:
			{
				tmp += TEXT("[unknowType],");
				break;
			}
		}
	}
	tmp.RemoveFromEnd(TEXT(","));
	tmp += TEXT(")");
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:%s"),__FUNCTIONW__,__LINE__,*tmp);
}

int32 UMySqlHelperLib::GetColumnNum(const FSqlRow& Row)
{
	return Row.data.Num();
}

// ********************************************************** get data by index **********************************************************

bool UMySqlHelperLib::GetBoolByIndex(const FSqlRow& Row,int32 Index)
{
	return GetBool(Row.data[Index]);
}

float UMySqlHelperLib::GetFloatByIndex(const FSqlRow& data,int32 Index)
{
	return GetFloat(data.data[Index]);
}

int UMySqlHelperLib::GetIntByIndex(const FSqlRow& data,int32 Index)
{
	return GetInt(data.data[Index]);
}

FString UMySqlHelperLib::GetStringByIndex(const FSqlRow& data,int32 Index)
{
	return GetString(data.data[Index]);
}
