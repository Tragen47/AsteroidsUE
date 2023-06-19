#pragma once
#include "CoreMinimal.h"

UENUM()
enum class InputTypesEnum : uint8
{
	Keyboard,
	Mouse,
	MAX UMETA(Hidden)
};

extern InputTypesEnum CurrentInputType;