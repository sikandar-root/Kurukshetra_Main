// Fill out your copyright notice in the Description page of Project Settings.

// #include "Database/FGDatabaseRef.h"
#include "FirebaseLobby_Subsystem.h"

// #include "GeometryTypes.h"
// #include "InteractiveToolActionSet.h"
// #include "Database/FGDataSnapshot.h"
// #include "Common/FGValueVariantAccess.h"

// UFGDatabaseRef* UFirebaseLobby_Subsystem::GetDatabase_ref(const FString UserID)
// {
// 	// Step 1: Make a Database Ref from "users" path
// 	UFGDatabaseRef* UsersDatabaseRef  = UFGDatabaseRef::MakeDatabaseRefFromPath(TEXT("users"));
//
// 	UFGDatabaseRef* UserDatabaseRef  = UsersDatabaseRef->Child(UserID);
//
// 	UFGDatabaseRef* ProfileDatabaseRef  = UserDatabaseRef->Child(TEXT("Profile"));
//
// 	return ProfileDatabaseRef;
// }
//
// UFGDatabaseRef* UFirebaseLobby_Subsystem::GetLobbyStatusDatabaseRef(const FString UserID)
// {
// 	// Step 1: Create a reference to the "users" path
// 	UFGDatabaseRef* UsersDatabaseRef = UFGDatabaseRef::MakeDatabaseRefFromPath(TEXT("users"));
//
// 	// Step 2: Navigate to the child corresponding to the UID
// 	UFGDatabaseRef* UserDatabaseRef = UsersDatabaseRef->Child(UserID);
//
// 	// Step 3: Navigate to the "Profile" child
// 	UFGDatabaseRef* ProfileDatabaseRef = UserDatabaseRef->Child(TEXT("Profile"));
//
// 	// Step 4: Navigate to the "Lobby" child
// 	UFGDatabaseRef* LobbyDatabaseRef = ProfileDatabaseRef->Child(TEXT("Lobby"));
//
// 	// Return the final "Lobby" reference
// 	return LobbyDatabaseRef;
// }
//
//
//
// void UFirebaseLobby_Subsystem::GetLobbyValue(const UFGDataSnapshot* Data, bool& InLobby, int32& LobbyID)
// {
// 	
// 	if (Data)
// 	{
// 		// Look for the "IsInLobby" key in the DataMap
// 		const FFGValueVariant* InLobbyVariant = Data->DataMap.Find(TEXT("IsInLobby"));
// 		if (InLobbyVariant)
// 		{
// 			// Use UFGValueVariantAccess to extract the boolean value
// 			InLobby = UFGValueVariantAccess::GetBool(*InLobbyVariant);
// 		}
// 		else
// 		{
// 			InLobby = false;  // Default to false if not found
// 		}
//
// 		// Look for the "LobbyID" key in the DataMap
// 		const FFGValueVariant* LobbyIDVariant = Data->DataMap.Find(TEXT("LobbyID"));
// 		if (LobbyIDVariant)
// 		{
// 			// Use UFGValueVariantAccess to extract the integer value
// 			LobbyID = UFGValueVariantAccess::GetInteger(*LobbyIDVariant);
// 		}
// 		else
// 		{
// 			LobbyID = -1;  // Default to -1 if not found
// 		}
// 	}
// }
//
// ULobbyStatus* ULobbyStatus::LobbyStatus(UFirebaseLobby_Subsystem* Subsystem, FString UserID)
// {
// 	// Create a new instance of the async action
// 	ULobbyStatus* AsyncAction = NewObject<ULobbyStatus>();
//
// 	// Assign the passed values to the class members
// 	AsyncAction->Subsystem = Subsystem;
// 	AsyncAction->UserID = UserID;
//
// 	return AsyncAction;
// }
//
// void ULobbyStatus::Activate()
// {
// 	Subsystem->GetLobbyStatusDatabaseRef(UserID)->GetValue(OnCompleted, OnCancelled);
//
// 	OnCompleted.BindDynamic(this, &ULobbyStatus::OnDataChanged);
// }
//
// void ULobbyStatus::OnDataChanged(UFGDataSnapshot* Data)
// {
// 	Subsystem->GetLobbyValue(Data);
// }
//
//
// UCreateLobby* UCreateLobby::CreateLobby(UFirebaseLobby_Subsystem* InSubsystem, FString InUserID)
// {
// 	// Create a new instance of the async action
// 	UCreateLobby* AsyncAction = NewObject<UCreateLobby>();
//
// 	// Assign the passed values to the class members
// 	AsyncAction->Subsystem = InSubsystem;
// 	AsyncAction->UserID = InUserID;
//
// 	return AsyncAction;
// }
//
// void UCreateLobby::Activate()
// {
// 	// Bind the dynamic delegates
// 	OnCompleted.BindDynamic(this, &UCreateLobby::OnDataChanged);
// 	OnCancelled.BindDynamic(this, &UCreateLobby::OnCancelledOperation);
//
// 	// Make sure to dereference Subsystem (as it's now a pointer)
// 	DatabaseRef = Subsystem->GetDatabase_ref(UserID);
// 	DatabaseRef->GetValue(OnCompleted, OnCancelled);
// }
//
// void UCreateLobby::CheckLobbyAlreadyExist()
// {
// 	// Step 1: Generate a random integer between 55555 and 99999 for the Lobby ID
// 	int32 MinLobbyID = 55555;
// 	int32 MaxLobbyID = 99999;
// 	LobbyID = FMath::RandRange(MinLobbyID, MaxLobbyID);
//
// 	// Step 2: Create a reference to the "lobbies" path in Firebase
// 	UFGDatabaseRef* LobbiesRef = UFGDatabaseRef::MakeDatabaseRefFromPath(TEXT("lobbies"));
//
// 	// Step 3: Create a reference to the specific lobby ID in the "lobbies" path
// 	UFGDatabaseRef* LobbyRef = LobbiesRef->Child(FString::FromInt(LobbyID));
//
// 	// Bind the dynamic delegates
// 	OnCompleted.BindDynamic(this, &UCreateLobby::JoinLobby);
//
// 	// Step 4: Get the value from the database to check if the lobby already exists
// 	LobbyRef->GetValue(OnCompleted, OnCancelled);
//
// 	return ;
// }
//
// void UCreateLobby::JoinLobby(UFGDataSnapshot* Data)
// {
// 	
// 	FFGValueVariant Value;
// 	TMap<FString, FFGValueVariant> Value2;
// 	bool Value3;
// 	
// 	
// 	OnCompleted.Unbind();
// 	if (!Data->Exists())
// 	{
// 		Value = Data->GetValue();
// 		Value2 = Value.Value.GetValue<TMap<FString, FFGValueVariant>>();
// 		 Value3 = Value2.Find(LobbyKey);
// 		
// 		
// 	}
// }
//
//
// void UCreateLobby::OnDataChanged(UFGDataSnapshot* Data)
// {
// 	
// 	// Removed local declaration of LobbyID
// 	if (!Data->Exists())
// 	{
// 		// The lobby does not exist, create a new lobby
// 		UE_LOG(LogTemp, Log, TEXT("Lobby ID %d does not exist. Creating new lobby."), LobbyID);
// 	}
// 	else
// 	{
// 		// The lobby already exists, join the existing lobby
// 		UE_LOG(LogTemp, Log, TEXT("Lobby ID %d already exists. Joining the lobby."), LobbyID);
// 	}
// }
//
// void UCreateLobby::OnCancelledOperation(int ErrorCode, FString ErrorMessage)
// {
// 	// Log error and handle the cancellation
// 	UE_LOG(LogTemp, Error, TEXT("Firebase operation cancelled with error: %d - %s"), ErrorCode, *ErrorMessage);
//
// 	if (OnCancelled.IsBound())
// 	{
// 		OnCancled.Broadcast(nullptr, ErrorMessage);
// 	}
// }
//
//


// void UFirebaseLobby_Subsystem::CalculateRaceData(const TMap<AActor*, FCarInputData>& CarInputMap,
// 	TMap<float, FAllCarsOutput>& OutRaceData)
// {
// 	const float TrackLength = 47030.0f; // Track length in cm
//     const float MinCarDistance = 500.0f;      // Minimum distance between cars in cm
//     const int32 NumSplines = 4;               // Number of spline paths (0 and 3 for overtaking, 1 and 2 for regular)
//
//     // Step 1: Iterate over the car input map to assign cars to spline paths and calculate their positions over time
//     for (const auto& Entry : CarInputMap)
//     {
//         AActor* CarActor = Entry.Key;
//         const FCarInputData& InputData = Entry.Value;
//
//         int32 SplineIndex = InputData.StartPosition % NumSplines; // Assign spline based on start position
//         float StartTime = 90.0f + (InputData.FinishRank - 1);    // Calculate the start time based on rank
//         float CarSpeed = TrackLength / (InputData.GameTime - StartTime); // Speed in cm per second
//
//         // Step 2: Iterate over time (1-second intervals) to calculate positions
//         for (float CurrentTime = 0; CurrentTime <= InputData.GameTime; CurrentTime += 1.0f)
//         {
//             FCarOutputData CarOutput;
//             CarOutput.CarActor = CarActor;
//             CarOutput.SplineIndex = SplineIndex;
//
//             // Calculate the distance along the spline
//             float DistanceTraveled = CarSpeed * (CurrentTime - StartTime);
//             CarOutput.DistanceAlongSpline = FMath::Clamp(DistanceTraveled, 0.0f, TrackLength);
//
//             // Maintain minimum distance between cars on the same spline
//             if (CurrentTime > 0)
//             {
//                 const TArray<FCarOutputData>& PrevCars = OutRaceData[CurrentTime - 1].CarsData;
//                 for (const FCarOutputData& PrevCar : PrevCars)
//                 {
//                     if (PrevCar.SplineIndex == SplineIndex && FMath::Abs(CarOutput.DistanceAlongSpline - PrevCar.DistanceAlongSpline) < MinCarDistance)
//                     {
//                         CarOutput.DistanceAlongSpline = PrevCar.DistanceAlongSpline + MinCarDistance;
//                     }
//                 }
//             }
//
//             // Step 3: Store the car data at the current time
//             if (!OutRaceData.Contains(CurrentTime))
//             {
//                 FAllCarsOutput NewData;
//                 OutRaceData.Add(CurrentTime, NewData);
//             }
//
//             OutRaceData[CurrentTime].CarsData.Add(CarOutput);
//         }
//     }
// }

void UFirebaseLobby_Subsystem::CalculateRaceData(const TMap<AActor*, FCarInputData>& CarInputMap, float RaceEndTime,
	float SplineLength, TMap<float, FAllCarsOutput>& OutRaceData)
{
	const float MinSameSplineDistance = 500.0f; // Minimum distance between cars on the same spline (500 cm)
    const float MinDiffSplineDistance = 250.0f; // Minimum distance between cars on different splines (250 cm)
    const int32 NumSplines = 4;                 // Number of splines (0 and 3 for overtaking, 1 and 2 for regular)
    const float DeltaTime = 0.01f;              // Time step (0.01 seconds)
    const float OvertakeTime = RaceEndTime * 0.10f; // 10% of the race end time for overtaking

    TMap<int32, bool> OvertakeSplineOccupied; // Track if splines 0 and 3 are occupied (0: available, 1: occupied)

    // Initialize spline availability for overtaking splines (0 and 3)
    OvertakeSplineOccupied.Add(0, false);
    OvertakeSplineOccupied.Add(3, false);

    for (const auto& Entry : CarInputMap)
    {
        AActor* CarActor = Entry.Key;
        const FCarInputData& InputData = Entry.Value;

        // Determine if overtaking/downtaking is needed
        bool bNeedsOvertake = InputData.FinishRank < InputData.StartPosition;
        bool bNeedsDowntake = InputData.FinishRank > InputData.StartPosition;

        // Assign default spline (1 or 2)
        int32 DefaultSplineIndex = InputData.StartPosition % 2 + 1; // Spline 1 or 2
        int32 OvertakeSplineIndex = (InputData.StartPosition % 2 == 0) ? 0 : 3; // Spline 0 or 3 for overtaking/downtaking

        float Speed = SplineLength / (RaceEndTime + InputData.FinishRank); // Speed based on finish rank

        // Variable to track if the car has already overtaken or downtaken
        bool bHasCompletedOvertake = false;

        for (float CurrentTime = 0; CurrentTime <= RaceEndTime; CurrentTime += DeltaTime)
        {
            FCarOutputData CarOutput;
            CarOutput.CarActor = CarActor;

            // Overtake or Downtake logic
            if (bNeedsOvertake || bNeedsDowntake)
            {
                // Check if overtaking spline is free
                if (!OvertakeSplineOccupied[OvertakeSplineIndex] && CurrentTime <= OvertakeTime && !bHasCompletedOvertake)
                {
                    // Use overtaking spline (0 or 3)
                    CarOutput.SplineIndex = OvertakeSplineIndex;
                    OvertakeSplineOccupied[OvertakeSplineIndex] = true; // Mark spline as occupied
                    bHasCompletedOvertake = true;
                }
                else if (bHasCompletedOvertake)
                {
                    // Return to regular spline after overtaking/downtaking
                    CarOutput.SplineIndex = DefaultSplineIndex;
                    OvertakeSplineOccupied[OvertakeSplineIndex] = false; // Free up the spline
                }
                else
                {
                    // Stay on the default spline if overtaking isn't possible yet
                    CarOutput.SplineIndex = DefaultSplineIndex;
                }
            }
            else
            {
                // No overtaking needed, use default spline
                CarOutput.SplineIndex = DefaultSplineIndex;
            }

            // Calculate distance traveled
            float DistanceTraveled = Speed * CurrentTime;

            // Step 3: Ensure cars maintain minimum distance
            if (!OutRaceData.Contains(CurrentTime))
            {
                FAllCarsOutput NewData;
                OutRaceData.Add(CurrentTime, NewData);
            }

            const TArray<FCarOutputData>& PrevCars = OutRaceData[CurrentTime].CarsData;
            for (const FCarOutputData& PrevCar : PrevCars)
            {
                if (PrevCar.SplineIndex == CarOutput.SplineIndex)
                {
                    // Maintain 500 cm distance on same spline
                    if (DistanceTraveled <= (PrevCar.DistanceAlongSpline + MinSameSplineDistance))
                    {
                        DistanceTraveled = PrevCar.DistanceAlongSpline + MinSameSplineDistance;
                    }
                }
                else
                {
                    // Maintain 250 cm distance on different splines
                    if (FMath::Abs(DistanceTraveled - PrevCar.DistanceAlongSpline) < MinDiffSplineDistance)
                    {
                        DistanceTraveled = PrevCar.DistanceAlongSpline + MinDiffSplineDistance;
                    }
                }
            }

            // Clamp distance to spline length
            CarOutput.DistanceAlongSpline = FMath::Clamp(DistanceTraveled, 0.0f, SplineLength);

            // Step 4: Store the output
            OutRaceData[CurrentTime].CarsData.Add(CarOutput);
        }
    }
}
