// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGMTK_RealCatStates : uint8
{
	ERCS_Awake UMETA(DisplayName = "Awake"),
	ERCS_Hand UMETA(DisplayName = "Hand"),
	ERCS_Petting UMETA(DisplayName = "Petting"),
	ERCS_Sleep UMETA(DisplayName = "Sleep"),
};
/**
 * 
 */
class GMTK_GAMEJAM2025_API GMTK_Enums
{
public:
	GMTK_Enums();
	~GMTK_Enums();
};
