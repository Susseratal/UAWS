//// Local Header Files ////
#include "awsLibrary.h"
#include "debugging.h"

//// Standard Header Files ////
#include <iostream>

//// Unreal Header Files ////
#include <Engine/Engine.h>

//// AWS Header Files ////
#include "aws/core/Aws.h"
#include "aws/core/utils/Outcome.h"
#include "aws/dynamodb/DynamoDBClient.h"
#include "aws/dynamodb/model/AttributeDefinition.h"
#include "aws/dynamodb/model/PutItemRequest.h"
#include "aws/dynamodb/model/PutItemResult.h"
#include "aws/dynamodb/model/UpdateItemRequest.h"
#include "aws/dynamodb/model/UpdateItemResult.h"
#include "aws/dynamodb/model/GetItemRequest.h"
#include "aws/auth/auth.h"
#include "aws/auth/credentials.h"
#include "aws/core/auth/AWSCredentialsProvider.h"
#include "aws/common/string.h"

using namespace std;
using namespace Aws;
namespace ddb = Aws::DynamoDB;

const Aws::String table = "UnrealDemo";
const Aws::String key = "Index";
ddb::DynamoDBClient* dynamoClient;

void UawsLibrary::initAPI(FString accessKey, FString secretKey, bool& success) {
	if (dynamoClient == NULL) {
		Udebugging::logDebugMessage("API Init Called");
		SDKOptions initOptions;
		Aws::InitAPI(initOptions);

		Client::ClientConfiguration clientConfig;
		clientConfig.region = "eu-west-2"; // London

		Auth::AWSCredentials credentials;
		string accessStr = TCHAR_TO_ANSI(*accessKey);
		string secretStr = TCHAR_TO_ANSI(*secretKey);
		Aws::String accessStrAws(accessStr.c_str(), accessStr.size());
		Aws::String secretStrAws(secretStr.c_str(), secretStr.size());
		credentials.SetAWSAccessKeyId(accessStrAws);
		credentials.SetAWSSecretKey(secretStrAws);

		dynamoClient = new ddb::DynamoDBClient(credentials, clientConfig);
		success = true;
	}
	else {
		Udebugging::logDebugMessage("API already running");
		success = true;
	}
}

void UawsLibrary::setItem(int index, FddbData data) {
	if (dynamoClient == NULL) { return; }
	else {
		Udebugging::logDebugMessage("Set Item Called");
		ddb::Model::PutItemRequest setRequest;
		setRequest.SetTableName(table);

		ddb::Model::AttributeValue kv;
		ddb::Model::AttributeValue av;
		ddb::Model::AttributeValue bv;
		ddb::Model::AttributeValue cv;
		kv.SetS(to_string(index));
		av.SetN(to_string(data.a));
		bv.SetN(to_string(data.b));
		cv.SetN(to_string(data.c));

		setRequest.AddItem(key, kv);
		setRequest.AddItem("a", av);
		setRequest.AddItem("b", bv);
		setRequest.AddItem("c", cv);

		const ddb::Model::PutItemOutcome result = dynamoClient->PutItem(setRequest);
		if (!result.IsSuccess()) { Udebugging::logDebugMessage(result.GetError().GetMessage().c_str()); }
	}
}

void UawsLibrary::updateItem(int index, FString choice) {
	Udebugging::logDebugMessage("Update item called");
	if (dynamoClient == NULL) { return; }
	else {
		Aws::String indexName;
		ddb::Model::UpdateItemRequest updateRequest;
		updateRequest.SetTableName(table);

		ddb::Model::AttributeValue kv;
		kv.SetS(to_string(index));
		updateRequest.AddKey(key, kv);

		Aws::String choiceStr = TCHAR_TO_ANSI(*choice);
		ddb::Model::AttributeValue av;
		av.SetN(1);
		Aws::String incr = ":incr";
		Aws::String updateExpression = ("SET #choiceStr = #choiceStr + :incr");
		updateRequest.SetUpdateExpression(updateExpression);
		Aws::Map<Aws::String, Aws::String> stringMap;
		stringMap["#choiceStr"] = choiceStr;
		updateRequest.SetExpressionAttributeNames(stringMap);
		Aws::Map<Aws::String, ddb::Model::AttributeValue> attribMap;
		attribMap[incr] = av;
		updateRequest.SetExpressionAttributeValues(attribMap);
		ddb::Model::UpdateItemOutcome result = dynamoClient->UpdateItem(updateRequest);

		if (!result.IsSuccess()) { Udebugging::logDebugMessage(result.GetError().GetMessage().c_str()); }
	}
}

void UawsLibrary::getItem(int index, FddbData& data) {
	if (dynamoClient == NULL) { return; }
	else {
		// const Aws::String keyVal = to_string(index);
		ddb::Model::GetItemRequest getRequest;
		ddb::Model::AttributeValue av;
		getRequest.SetTableName(table);
		av.SetS(to_string(index));
		getRequest.AddKey(key, av);

		int x;
		int count = 1;
		const ddb::Model::GetItemOutcome& result = dynamoClient->GetItem(getRequest);
		if (result.IsSuccess()) {
			const Aws::Map<Aws::String, ddb::Model::AttributeValue>& item = result.GetResult().GetItem();
			if (item.size() > 0) {
				// I think there ought to be a better way of doing this
				for (const auto& i : item) {
					switch (count) {
					case 1:
						count++;
						break;
					case 2:
						x = stoi(i.second.GetN());
						data.a = x;
						count++;
						break;
					case 3:
						x = stoi(i.second.GetN());
						data.b = x;
						count++;
						break;
					case 4:
						x = stoi(i.second.GetN());
						data.c = x;
						count++;
						break;
					}
				}
			}
		}
	}
}
