#pragma once
#pragma warning(disable: 4668)

#define USE_WINDOWS_DLL_SEMANTICS
#define USE_IMPORT_EXPORT

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "awsLibrary.generated.h"

USTRUCT(BlueprintType) struct FddbData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int a;

	UPROPERTY(BlueprintReadWrite)
	int b;

	UPROPERTY(BlueprintReadWrite)
	int c;
};

UCLASS()
class DYNAMODBDEMO_API UawsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "AWS")
	static void initAPI(FString accessKey, FString secretKey, bool& success);

	UFUNCTION(BlueprintCallable, Category = "AWS")
	static void setItem(int index, FddbData data);

	UFUNCTION(BlueprintCallable, Category = "AWS")
	static void updateItem(int index, FString choice);
	
	UFUNCTION(BlueprintCallable, Category = "AWS")
	static void getItem(int index, FddbData& data);
};
