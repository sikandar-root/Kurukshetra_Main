// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebaseDatabase_Subsystem.h"
#include "Database/FGDatabaseRef.h"
#include "Database/FGDataSnapshot.h"
#include "Engine/Engine.h"



USetValue_Async* USetValue_Async::SetValueWithResponce(UFGDatabaseRef* DatabaseRef, const FFGValueVariant& Value,
	const FFGValueVariant& Priority)
{
	// Create a new instance of the async action
	USetValue_Async* AsyncAction = NewObject<USetValue_Async>();
    
	// Store the database reference and values
	AsyncAction->DatabaseRef = DatabaseRef;
	AsyncAction->Values = Value;
	AsyncAction->Prioritys = Priority;
    
	// Return the async function object so it can be activated
	return AsyncAction;
}

void USetValue_Async::Activate()
{
	// Bind your delegate
	OnCompleted.BindDynamic(this, &USetValue_Async::OnDataChanged);
	OnCancelled.BindDynamic(this, &USetValue_Async::OnCancelledOperation);
    
	// Call the AddValueListener
	DatabaseRef->AddValueListener(OnCompleted, OnCancelled);
    
	// Call SetValue when activated
	DatabaseRef->SetValue(Values, Prioritys);

	// Log completion of activation
	UE_LOG(LogTemp, Log, TEXT("Activate: Activation complete"));
}

void USetValue_Async::OnDataChanged(UFGDataSnapshot* Data)
{
	UE_LOG(LogTemp, Log, TEXT("OnValueChanged: Activated"));

	// Trigger the OnCancelled delegate when the operation is cancelled
	On_Completed.Broadcast(true, Data, FString("SucessfullyLoaded"));
    
	// Remove the listener on cancellation
	DatabaseRef->RemoveValueListener();
}

void USetValue_Async::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
	// Log the operation cancellation
	UE_LOG(LogTemp, Log, TEXT("OnCancelledOperation: Operation cancelled. ErrorCode: %d, ErrorMessage: %s"), ErrorCode, *ErrorMessage);

	// Trigger the OnCancelled delegate when the operation is cancelled
	On_Completed.Broadcast(true,DataSnapshot, ErrorMessage);
    
	// Remove the listener on cancellation
	DatabaseRef->RemoveValueListener();
}

UUpdateChildren_Async* UUpdateChildren_Async::UpdateChildrenWithResponce(UFGDatabaseRef* DatabaseRef,
	 const TMap<FString, FFGValueVariant>& Value)
{
	UUpdateChildren_Async* AsyncTask = NewObject<UUpdateChildren_Async>();

	AsyncTask->DatabaseRef = DatabaseRef;
	AsyncTask->Values = Value;

	return AsyncTask;
}

void UUpdateChildren_Async::Activate()
{
	// Bind your delegate
	OnCompleted.BindDynamic(this, &UUpdateChildren_Async::OnDataChanged);
	OnCancelled.BindDynamic(this, &UUpdateChildren_Async::OnCancelledOperation);
    
	// Call the AddValueListener
	DatabaseRef->AddChildListener(OnCompleted, OnCancelled);
    
	// Call SetValue when activated
	DatabaseRef->UpdateChildren(Values);

	// Log completion of activation
	UE_LOG(LogTemp, Log, TEXT("Activate: Activation complete"));
}

void UUpdateChildren_Async::OnDataChanged(EChileEventType EventType, UFGDataSnapshot* Data, FString PreviousChildName)
{
	On_Completed.Broadcast(true, Data,PreviousChildName);

	DatabaseRef->RemoveChildListener();
}

void UUpdateChildren_Async::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
	On_Completed.Broadcast(false, DataSnapshot,ErrorMessage);

	DatabaseRef->RemoveChildListener();
}

UListenValue_Async* UListenValue_Async::ActivateValueListner(UFGDatabaseRef* DatabaseRef)
{
	UListenValue_Async* AsyncTask = NewObject<UListenValue_Async>();

	AsyncTask->DatabaseRef = DatabaseRef;

	return AsyncTask;
}

void UListenValue_Async::Activate()
{
	// Bind your delegate
	OnCompleted.BindDynamic(this, &UListenValue_Async::OnDataChanged);
	OnCancelled.BindDynamic(this, &UListenValue_Async::OnCancelledOperation);
    
	// Call the AddValueListener
	DatabaseRef->AddValueListener(OnCompleted, OnCancelled);
}

void UListenValue_Async::OnDataChanged(UFGDataSnapshot* Data)
{
	On_Completed.Broadcast(true,Data, FString("Sucessfully ValueListener Activated"));
}

void UListenValue_Async::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
	On_Completed.Broadcast(false,DataSnapshot,ErrorMessage);
}

UListenChildren_Async* UListenChildren_Async::ActivateChildListner(UFGDatabaseRef* DatabaseRef)
{
	UListenChildren_Async* AsyncTask = NewObject<UListenChildren_Async>();

	AsyncTask->DatabaseRef = DatabaseRef;

	return AsyncTask;
}

void UListenChildren_Async::Activate()
{
	// Bind your delegate
	OnCompleted.BindDynamic(this, &UListenChildren_Async::OnDataChanged);
	OnCancelled.BindDynamic(this, &UListenChildren_Async::OnCancelledOperation);
    
	// Call the AddValueListener
	DatabaseRef->AddChildListener(OnCompleted, OnCancelled);
}

void UListenChildren_Async::OnDataChanged(EChileEventType EventType, UFGDataSnapshot* Data, FString PreviousChildName)
{
	On_Completed.Broadcast(true,Data, FString("Sucessfully ChildrenListener Activated"));
}

void UListenChildren_Async::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
	On_Completed.Broadcast(false,DataSnapshot,ErrorMessage);
}

UGetValue_Async* UGetValue_Async::GetValue_Async(UFGDatabaseRef* DatabaseRef)
{
	UGetValue_Async* AsyncTask = NewObject<UGetValue_Async>();

	AsyncTask->DatabaseRef = DatabaseRef;

	return AsyncTask;
}

void UGetValue_Async::Activate()
{
	// Bind your delegate
	OnCompleted.BindDynamic(this, &UGetValue_Async::OnDataChanged);
	OnCancelled.BindDynamic(this, &UGetValue_Async::OnCancelledOperation);
    
	// Call the AddValueListener
	DatabaseRef->GetValue(OnCompleted, OnCancelled);
}

void UGetValue_Async::OnDataChanged(UFGDataSnapshot* Data)
{
	On_Completed.Broadcast(true,Data, FString("Sucessfully Get Value"));
}

void UGetValue_Async::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
{
	On_Completed.Broadcast(false,DataSnapshot,ErrorMessage);
}
