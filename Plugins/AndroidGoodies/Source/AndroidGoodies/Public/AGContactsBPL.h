// Copyright (c) 2019 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGContact.h"
#include "AGContactsBPL.generated.h"

UCLASS()
class ANDROIDGOODIES_API UAGContactsBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* Get the phone number, stored on the SIM card. 
	* Requires the "android.permission.READ_PHONE_STATE" permission.
	* This method only works on devices where the number is stored on the SIM card, which only some carriers do.
	* Returns an empty string if the number is unavailable.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Contacts")
	static FString GetUserPhoneNumber();

	/**
	* Get the list of contacts containing the given name.
	* Requires the "android.permission.READ_CONTACTS" permission.
	*
	* @param name - the contact name to search for.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Contacts")
	static TArray<FAGContact> GetContactsWithName(FString name);

	/**
	* Get the list of contacts containing with the given number.
	* Requires the "android.permission.READ_CONTACTS" permission.
	*
	* @param number - the phone number to search for.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Contacts")
	static TArray<FAGContact> GetContactsWithNumber(FString number);

	/**
	* Get the list of all contacts.
	* Requires the "android.permission.READ_CONTACTS" permission.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Contacts")
	static TArray<FAGContact> GetAllContacts();

	/**
	* Add a contact to the phone book.
	* Requires the "android.permission.WRITE_CONTACTS" permission.
	*
	* @param contact - contact to add.
	* @return - true if the operation was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "AndroidGoodies|Contacts")
	static bool AddContact(FAGContact contact);
};
