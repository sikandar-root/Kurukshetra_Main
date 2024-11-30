// Copyright (c) 2022 Nineva Studios

#include "Common/FGValueVariant.h"

template int32 FFGValueVariant::GetValue<int32>() const;
template float FFGValueVariant::GetValue<float>() const;
template bool FFGValueVariant::GetValue<bool>() const;
template FString FFGValueVariant::GetValue<FString>() const;
template TArray<FFGValueVariant> FFGValueVariant::GetValue<TArray<FFGValueVariant>>() const;
template TMap<FString, FFGValueVariant> FFGValueVariant::GetValue<TMap<FString, FFGValueVariant>>() const;
template FDateTime FFGValueVariant::GetValue<FDateTime>() const;