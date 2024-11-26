// Copyright (c) 2018 Nineva Studios

#pragma once

#include "AGAlarmDaysData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGAlarmClockBPL.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGAlarmClock : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Set the alarm. 
	* @param hour - hour of the alarm being set (ranges from 0 to 23)
	* @param minute - minutes of the alarm being set (ranges from 0 to 59. If not provided, it defaults to 0)
	* @param message - custom message for the alarm
	* @param days - weekdays for repeating alarm. If not set the alarm will be once. 1 - Sunday, 2 - Monday and so on
	* @param vibrate - whether or not to activate the device vibrator for this alarm
	* @param skipUi - whether or not to display an activity for setting this alarm
	* @note this feature is supported starting from Android API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SetAlarm(int hour, int minute, FString message, FAGAlarmDaysData days, bool vibrate, bool skipUi);

	/**
	* Open or start the countdown timer application.
	* @param lengthSeconds - timer length in seconds (ranges from 1 to 86400 (24 hours))
	* @param message - custom message for the timer
	* @param skipUi - whether or not to display an activity for setting this timer
	* @note this feature is supported starting from Android API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SetTimer(int lengthSeconds, FString message, bool skipUi);

	/**
	* Show all alarms.
	* @note this feature is supported starting from Android API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowAllAlarms();

	/**
	* Show all timers.
	* @note this feature is supported starting from Android API level 26
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void ShowAllTimers();

	/**
	* Check if any app to set alarms is installed
	* @note this feature is supported starting from Android API level 9
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool CanSetAlarm();

	/**
	* Check if any app to set timer is installed
	* @note this feature is supported starting from Android API level 19
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static bool CanSetTimer();

	/**
	* Snooze the currently ringing alarm.
	* @param snoozeDurationMinutes - alarm snooze duration
	* @note The alarm should ring again after the snooze duration.
	* @note If there is no currently ringing alarm, then this is a no-op.
	* @note this feature is supported starting from Android API level 23
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies")
	static void SnoozeAlarm(int snoozeDurationMinutes = 10);
};
