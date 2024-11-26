#include "FGCloudFunctionsCallback.h"
#include "Async/Async.h"

UFGCloudFunctionsCallback::UFGCloudFunctionsCallback()
{
	if (StaticClass()->GetDefaultObject() != this)
	{
		AddToRoot();
	}
}

void UFGCloudFunctionsCallback::BindErrorDelegate(const FCloudFunctionsStringDelegate& OnError)
{
	OnCallErrorDelegate = OnError;
}

void UFGCloudFunctionsCallback::ExecuteError(FString ErrorMessage)
{
	AsyncTask(ENamedThreads::GameThread, [this, ErrorMessage]()
	{
		OnCallErrorDelegate.ExecuteIfBound(ErrorMessage);
		this->RemoveFromRoot();
	});
}
