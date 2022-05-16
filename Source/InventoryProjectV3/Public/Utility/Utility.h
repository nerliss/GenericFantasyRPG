// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"

// Print string on screen macro
#define DEBUGMESSAGE(x, y, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, x, FColor::Red, FString::Printf(TEXT(y), __VA_ARGS__));}


class INVENTORYPROJECTV3_API Utility
{
public:
	Utility();
	~Utility();
};
