#pragma once

#include <fstream>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "debugging.generated.h"

UCLASS()
class DYNAMODBDEMO_API Udebugging : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static std::ofstream outputHandle;
	static bool debuggingEnabled;

	/**
	* Opens a debug log file. Should be called before any other debugging functions
	* 
	* @param path Must be in format "C:\\path\\to\\output.log", or left empty
	*/
	UFUNCTION(BlueprintCallable, Category = "Debugging")
	static void initDebugFile(FString path);

	/**
	* Writes a debug message out to the log. InitDebugFile must be called before this
	* 
	* @param message The debug message to be written out to disk
	*/
	UFUNCTION(BlueprintCallable, Category = "Debugging")
	static void logDebugMessage(FString message);

	/**
	* Returns the current time as an FString
	* 
	* @param time The current time, formatted as Hour:Minutes:Seconds
	*/
	UFUNCTION(BlueprintCallable, Category = "Debugging")
	static void debugTime(FString& time);
	
};
