#include "FGCloudFunctionsBoolCallback.h"
#include "Async/Async.h"

UFGCloudFunctionsBoolCallback::UFGCloudFunctionsBoolCallback()
{
	if (StaticClass()->GetDefaultObject() != this)
	{
		AddToRoot();
	}
}

void UFGCloudFunctionsBoolCallback::BindSuccessDelegate(const FCloudFunctionsBoolDelegate& OnSuccess)
{
	OnCallBoolFunctionSuccessDelegate = OnSuccess;
}

void UFGCloudFunctionsBoolCallback::ExecuteSuccess(bool Bool)
{
	AsyncTask(ENamedThreads::GameThread, [this, Bool]() {
		OnCallBoolFunctionSuccessDelegate.ExecuteIfBound(Bool);
		this->RemoveFromRoot();
	});
}
