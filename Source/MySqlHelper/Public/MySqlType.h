#pragma once
#include "mysqlx/xdevapi.h"
#include "MySqlType.generated.h"


USTRUCT(BlueprintType)
struct FSqlData
{
	GENERATED_BODY()
	mysqlx::Value value;
};

USTRUCT(BlueprintType)
struct FSqlRow
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FSqlData> data;
};

USTRUCT(BlueprintType)
struct FSqlExecResult
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bSuccess = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool hasData = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 dataNum = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 colNum = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FSqlRow> rowList;
};
