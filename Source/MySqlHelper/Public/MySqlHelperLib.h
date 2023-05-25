// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MySqlType.h"
#include "MySqlHelperLib.generated.h"

/**
 * 
 */
UCLASS()
class MYSQLHELPER_API UMySqlHelperLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// data
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static bool GetBool(const FSqlData & data);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static float GetFloat(const FSqlData & data);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static int GetInt(const FSqlData & data);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static FString GetString(const FSqlData & data);
	// row
	UFUNCTION(BlueprintCallable,Category="SqlLib")
	static void DebugRow(const FSqlRow & Row);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static int32 GetColumnNum(const FSqlRow & Row);
	// get data by index
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static bool GetBoolByIndex(const FSqlRow & Row,int32 Index);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static float GetFloatByIndex(const FSqlRow & data,int32 Index);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static int GetIntByIndex(const FSqlRow & data,int32 Index);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="SqlLib")
	static FString GetStringByIndex(const FSqlRow & data,int32 Index);
};
