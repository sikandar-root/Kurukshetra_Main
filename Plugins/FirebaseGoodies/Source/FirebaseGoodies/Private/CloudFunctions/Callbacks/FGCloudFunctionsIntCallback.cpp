#include "FGCloudFunctionsIntCallback.h"
#include "Async/Async.h"

UFGCloudFunctionsIntCallback::UFGCloudFunctionsIntCallback()
{
	if (StaticClass()->GetDefaultObject() != this)
	{
		AddToRoot();
	}
}

void UFGCloudFunctionsIntCallback::BindSuccessDelegate(const FCloudFunctionsIntDelegate& OnSuccess)
{
	OnCallIntFunctionSuccessDelegate = OnSuccess;
}


void UFGCloudFunctionsIntCallback::ExecuteSuccess(int Num)
{
	AsyncTask(ENamedThreads::GameThread, [this, Num]() {
		OnCallIntFunctionSuccessDelegate.ExecuteIfBound(Num);
		this->RemoveFromRoot();
	});
}
