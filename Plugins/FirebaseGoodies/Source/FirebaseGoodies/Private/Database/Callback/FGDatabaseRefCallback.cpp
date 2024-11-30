// Copyright (c) 2022 Nineva Studios

#include "FGDatabaseRefCallback.h"
#include "Async/Async.h"

#include "Database/FGDataSnapshot.h"

UFGDatabaseRefCallback::UFGDatabaseRefCallback()
{
	if (StaticClass()->GetDefaultObject() != this)
	{
		AddToRoot();
	}
}

void UFGDatabaseRefCallback::BindDataChangedDelegate(const FOnDataChangedDelegate& OnDataChanged)
{
	OnDataChangedDelegate = OnDataChanged;
}

void UFGDatabaseRefCallback::BindCancelDelegate(const FOnCancelledDelegate& OnCancelled)
{
	OnCancelledDelegate = OnCancelled;
}

void UFGDatabaseRefCallback::BindOnChildEventDelegate(const FOnChildEventDelegate& OnChildEvent)
{
	OnChildEventDelegate = OnChildEvent;
}

void UFGDatabaseRefCallback::ExecuteDataChanged(UFGDataSnapshot* Data)
{
	AsyncTask(ENamedThreads::GameThread, [this, Data]() {
		OnDataChangedDelegate.ExecuteIfBound(Data);
	});
	if (AutoRemoveAfterExecution)
	{
		this->RemoveFromRoot();
	}
}

void UFGDatabaseRefCallback::ExecuteCancel(int ErrorCode, const FString& ErrorMessage)
{
	AsyncTask(ENamedThreads::GameThread, [this, ErrorCode, ErrorMessage]() {
		OnCancelledDelegate.ExecuteIfBound(ErrorCode, ErrorMessage);
	});
	if (AutoRemoveAfterExecution)
	{
		this->RemoveFromRoot();
	}
}

void UFGDatabaseRefCallback::ExecuteOnChildEvent(EChileEventType EventType, UFGDataSnapshot* Data, const FString& PreviousChildName)
{
	AsyncTask(ENamedThreads::GameThread, [this, EventType, Data, PreviousChildName]() {
		OnChildEventDelegate.ExecuteIfBound(EventType, Data, PreviousChildName);
	});
	if (AutoRemoveAfterExecution)
	{
		this->RemoveFromRoot();
	}
}
