// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGAudioAttributesUsage.generated.h"

UENUM(BlueprintType)
enum AudioAttributesUsage
{
	/*Usage value to use when the usage is unknown.*/
	NotSpecified = 0 UMETA(DisplayName = "NotSpecified"),
	/*Usage value to use when the usage is media, such as music, or movie soundtracks.*/
	Media = 1 UMETA(DisplayName = "Media"),
	/*Usage value to use when the usage is voice communications, such as telephony or VoIP.*/
	VoiceCommunication = 2 UMETA(DisplayName = "VoiceCommunication"),
	/*Usage value to use when the usage is in-call signalling, such as with a "busy" beep, or DTMF tones.*/
	VoiceCommunicationSignalling = 3 UMETA(DisplayName = "VoiceCommunicationSignalling"),
	/*Usage value to use when the usage is an alarm (e.g. wake-up alarm).*/
	Alarm = 4 UMETA(DisplayName = "Alarm"),
	/*Usage value to use when the usage is notification. See other notification usages for more specialized uses.*/
	Notification = 5 UMETA(DisplayName = "Notification"),
	/*Usage value to use when the usage is telephony ringtone.*/
	NotificationRingtone = 6 UMETA(DisplayName = "NotificationRingtone"),
	/*Usage value to use when the usage is a request to enter/end a communication, such as a VoIP communication or video-conference.*/
	NotificationCommunicationRequest = 7 UMETA(DisplayName = "NotificationCommunicationRequest"),
	/*Usage value to use when the usage is notification for an "instant" communication such as a chat, or SMS.*/
	NotificationCommunicationInstant = 8 UMETA(DisplayName = "NotificationCommunicationInstant"),
	/*Usage value to use when the usage is notification for a non-immediate type of communication such as e-mail.*/
	NotificationCommunicationDelayed = 9 UMETA(DisplayName = "NotificationCommunicationDelayed"),
	/*Usage value to use when the usage is to attract the user's attention, such as a reminder or low battery warning.*/
	NotificationEvent = 10 UMETA(DisplayName = "NotificationEvent"),
	/*Usage value to use when the usage is for accessibility, such as with a screen reader.*/
	AssistanceAccessibility = 11 UMETA(DisplayName = "AssistanceAccessibility"),
	/*Usage value to use when the usage is driving or navigation directions.*/
	AssistanceNavigationGuidance = 12 UMETA(DisplayName = "AssistanceNavigationGuidance"),
	/*Usage value to use when the usage is sonification, such as with user interface sounds.*/
	AssistanceSonification = 13 UMETA(DisplayName = "AssistanceSonification"),
	/*Usage value to use when the usage is for game audio.*/
	Game = 14 UMETA(DisplayName = "Game"),
	/*Usage value to use for audio responses to user queries, audio instructions or help utterances.*/
	Assistant = 16 UMETA(DisplayName = "Assistant"),
};
