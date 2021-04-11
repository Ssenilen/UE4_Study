// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(UnrealStudy, Log, All);

#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
//#define ABLOG_S(Verbosity) UE_LOG(UnrealStudy, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
//#define ABLOG(Verbosity, Format, ...) UE_LOG(UnrealStudy, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
//#define debugf(Format, ...) UE_LOG(UnrealStudy, Warning, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))


#define debugf(Format, ...) UE_LOG(UnrealStudy, Warning, TEXT("%s"), *FString::Printf(Format, ##__VA_ARGS__))