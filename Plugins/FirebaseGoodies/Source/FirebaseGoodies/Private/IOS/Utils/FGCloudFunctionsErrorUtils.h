// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Containers/UnrealString.h"
#import <Foundation/Foundation.h>

namespace CloudFunctionsErrorUtils
{
FString HandleError(NSError* error);
}
