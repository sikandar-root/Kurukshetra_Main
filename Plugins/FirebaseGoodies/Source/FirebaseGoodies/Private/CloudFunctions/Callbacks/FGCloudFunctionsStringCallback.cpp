#include "FGCloudFunctionsStringCallback.h"
#include "Async/Async.h"

UFGCloudFunctionsStringCallback::UFGCloudFunctionsStringCallback()
{
	if (StaticClass()->GetDefaultObject() != this)
	{
		AddToRoot();
	}
}

void UFGCloudFunctionsStringCallback::BindSuccessDelegate(const FCloudFunctionsStringDelegate& OnSuccess)
{
	OnCallStringFunctionSuccessDelegate = OnSuccess;
}

void UFGCloudFunctionsStringCallback::ExecuteSuccess(FString String)
{
	AsyncTask(ENamedThreads::GameThread, [this, String]() {
		OnCallStringFunctionSuccessDelegate.ExecuteIfBound(String);
		this->RemoveFromRoot();
	});
}
