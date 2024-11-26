// Copyright (c) 2019 Nineva Studios

#pragma once

#include "AGAudioAttributesContentType.generated.h"

UENUM(BlueprintType)
enum AudioAttributesContentType
{
	/*Content type value to use when the content type is unknown, or other than the ones defined.*/
	AudioAttributesContentTypeUnknown = 0 UMETA(DisplayName = "Unknown"),
	/*Content type value to use when the content type is speech.*/
	Speech = 1 UMETA(DisplayName = "Speech"),
	/*Content type value to use when the content type is music.*/
	Music = 2 UMETA(DisplayName = "Music"),
	/*Content type value to use when the content type is a soundtrack, typically accompanying a movie or TV program.*/
	Movie = 3 UMETA(DisplayName = "Movie"),
	/**
	* Content type value to use when the content type is a sound used to accompany a user action, 
	* such as a beep or sound effect expressing a key click, or event, such as the type of a sound for a bonus being received in a game. 
	* These sounds are mostly synthesized or short Foley sounds.
	*/
	Sonification = 4 UMETA(DisplayName = "Sonification"),
};
