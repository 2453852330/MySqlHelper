// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

// custom include
#include "mysqlx/xdevapi.h"
#include "MySqlType.h"
// end include

#include "MySqlObject.generated.h"



UCLASS(BlueprintType)
class MYSQLHELPER_API UMySqlObject : public UObject
{
	GENERATED_BODY()
	
	struct FMySqlConnectInfo
	{
		FString Host = TEXT("localhost");
		int32 Port = 33060;
		FString User = TEXT("root");
		FString Pwd;
	};
	// fstring to std::string
	std::string to_std_string(FString In)
	{
		return std::string(TCHAR_TO_UTF8(*In));
	}
	
	// session connect info
	FMySqlConnectInfo _sql_connect_info;
	// default use lib
	std::string _sql_lib_name;
	//
	mysqlx::Row make_row_data_from_string(FString & inData);
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateSqlConnect(FString host,int32 port,FString user,FString pwd);
	UFUNCTION(BlueprintCallable)
	void SetLibName(FString sqlLibName);
	
	UFUNCTION(BlueprintCallable)
	FSqlExecResult ExecSql(FString sqlCode);

	
	UFUNCTION(BlueprintCallable)
	void InsertData(FString tableName,FString insertData);

};
