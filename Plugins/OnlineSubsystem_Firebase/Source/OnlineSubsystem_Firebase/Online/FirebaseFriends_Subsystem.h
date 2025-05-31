// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Database/FGDatabaseRef.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseFriends_Subsystem.generated.h"

UENUM(BlueprintType)
enum class EFriendRequestResult : uint8
{
    Success,
    Failed,
    Pending
};

USTRUCT(BlueprintType)
struct FFriendData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Friends")
    FString UserID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Friends")
    FString ChatID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFriendRequestResultDelegate, bool, bWasSuccessful, FString, FriendUserID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFriendListDelegate, const TArray<FFriendData>&, Friends, bool, bWasSuccessful);

/**
 * Subsystem for managing friend relationships using Firebase
 */
UCLASS()
class ONLINESUBSYSTEM_FIREBASE_API UFirebaseFriends_Subsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /** Cached friend data */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Friends")
    TArray<FFriendData> FriendData;

    /** Convert string to UniqueNetId */
    UFUNCTION(BlueprintCallable, Category = "Friends")
    FUniqueNetIdRepl CreateUniqueIdFromString(const FString& StringId);

    /** Set network ID for player state */
    UFUNCTION(BlueprintCallable, Category = "Friends")
    static void SetPlayerNetworkID(APlayerState* PlayerState, FUniqueNetIdRepl NetId);
};

/**
 * Async action for retrieving friend list
 */
UCLASS()
class UGetFriendListAsync : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static UGetFriendListAsync* GetFriendList(UObject* WorldContextObject, const FString& UserID);

    UPROPERTY(BlueprintAssignable)
    FFriendListDelegate OnCompleted;

    virtual void Activate() override;

private:
    UFUNCTION()
    void OnDataReceived(UFGDataSnapshot* Data);
    UFUNCTION()
    void OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage);

    UPROPERTY()
    FOnDataChangedDelegate OnDataChangedDelegate;

    UPROPERTY()
    FOnCancelledDelegate OnCancelledDelegate;

    FString TargetUserID;
    UFirebaseFriends_Subsystem* FriendsSubsystem;
};

/**
 * Async action for finding users
 */
UCLASS()
class UFindUserAsync : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static UFindUserAsync* FindUser(UObject* WorldContextObject, const FString& UsernameOrID);

    UPROPERTY(BlueprintAssignable)
    FFriendRequestResultDelegate OnCompleted;

    virtual void Activate() override;

private:
    void OnDataReceived(UFGDataSnapshot* Data);
    void OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage);

    UPROPERTY()
    FOnDataChangedDelegate OnDataChangedDelegate;

    UPROPERTY()
    FOnCancelledDelegate OnCancelledDelegate;

    FString SearchQuery;
    UFGDatabaseRef* DatabaseRef;
};

/**
 * Base class for friend request operations
 */
UCLASS(Abstract)
class UFriendRequestAsyncBase : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

protected:
    FString SenderUserID;
    FString TargetUserID;

    UPROPERTY(BlueprintAssignable)
    FFriendRequestResultDelegate OnCompleted;

    TMap<FString, FFGValueVariant> CreateFriendDataValue(const FString& UserID, const FString& FriendID, bool bIsFriendRecord);
};

/**
 * Async action for sending friend requests
 */
UCLASS()
class USendFriendRequestAsync : public UFriendRequestAsyncBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static USendFriendRequestAsync* SendFriendRequest(UObject* WorldContextObject, const FString& SenderUserID, const FString& TargetUserID);

    virtual void Activate() override;

private:
    void OnUserFound(UFGDataSnapshot* Data);
    void OnOperationCancelled(int32 ErrorCode, const FString ErrorMessage);

    UPROPERTY()
    FOnDataChangedDelegate OnDataChangedDelegate;

    UPROPERTY()
    FOnCancelledDelegate OnCancelledDelegate;

    UFGDatabaseRef* UserDatabaseRef;
};

/**
 * Async action for accepting friend requests
 */
UCLASS()
class UAcceptFriendRequestAsync : public UFriendRequestAsyncBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static UAcceptFriendRequestAsync* AcceptFriendRequest(UObject* WorldContextObject, const FString& SenderUserID, const FString& TargetUserID);

    virtual void Activate() override;
};

/**
 * Async action for rejecting friend requests
 */
UCLASS()
class URejectFriendRequestAsync : public UFriendRequestAsyncBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
    static URejectFriendRequestAsync* RejectFriendRequest(UObject* WorldContextObject, const FString& SenderUserID, const FString& TargetUserID);

    virtual void Activate() override;
};