// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGMTK_RealCatBodyStates : uint8
{
	ERCS_Awake UMETA(DisplayName = "Awake"),
	ERCS_Petting UMETA(DisplayName = "Petting"),
	ERCS_Sleep UMETA(DisplayName = "Sleep"),
};

UENUM(BlueprintType)
enum class EGMTK_RealCatHandStates : uint8
{
	ERCS_HandIdle UMETA(DisplayName = "Hand Idle"),
	ERCS_HandMoving UMETA(DisplayName = "Hand Moving"),
};

UENUM(BlueprintType)
enum class EGMTK_PlatformTracks : uint8
{
	EPTS_Percussion UMETA(DisplayName = "Percussion"),
	EPTS_Bass UMETA(DisplayName = "Bass"),
	EPTS_Lead UMETA(DisplayName = "Lead"),
	EPTS_Pad UMETA(DisplayName = "Pad"),
	EPTS_Arpeggio UMETA(DisplayName = "Arpeggio"),
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
