// Copyright (c) 2020 Nineva Studios

#include "Stats/GPPlayerStats.h"

#include "GooglePlayLog.h"

#if PLATFORM_ANDROID
#include "Async/Async.h"
#include "Android/Utils/GPMethodCallUtils.h"
#endif

static const ANSICHAR* GPPlayerStatsClassName = "com/ninevastudios/googleplay/GPPlayerStats";

UGPPlayerStatsLibrary::FGPLoadStatsDelegate UGPPlayerStatsLibrary::OnLoadStatsDelegate;

void UGPPlayerStatsLibrary::LoadPlayerStats(const FGPLoadStatsDelegate& OnLoadStats, bool ForceRefresh)
{
	UGPPlayerStatsLibrary::OnLoadStatsDelegate = OnLoadStats;
#if PLATFORM_ANDROID
	GPMethodCallUtils::CallStaticVoidMethod(GPPlayerStatsClassName, "getPlayerStats", "(Landroid/app/Activity;Z)V",
		FJavaWrapper::GameActivityThis, ForceRefresh);
#endif
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_googleplay_GPPlayerStats_onPlayerStatsCallback(
	JNIEnv* env, jclass clazz, int DaysSinceLastPlayed, int NumberOfSessions, float AverageSessionLength,
	float SessiaonPercentile, int NumberOfPurchases, float SpendPercentile)
{
	FGPPlayerStats Stats;
	Stats.DaysSinceLastPlayed = DaysSinceLastPlayed;
	Stats.NumberOfSessions = NumberOfSessions;
	Stats.AverageSessionLength = AverageSessionLength;
	Stats.SessiaonPercentile = SessiaonPercentile;
	Stats.NumberOfPurchases = NumberOfPurchases;
	Stats.SpendPercentile = SpendPercentile;

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UGPPlayerStatsLibrary::OnLoadStatsDelegate.ExecuteIfBound(Stats);
	});
}

#endif
