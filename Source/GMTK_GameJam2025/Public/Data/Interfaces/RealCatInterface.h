// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RealCatInterface.generated.h"

enum class EGMTK_RealCatHandStates : uint8;
enum class EGMTK_RealCatBodyStates : uint8;
// This class does not need to be modified.
UINTERFACE()
class URealCatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GMTK_GAMEJAM2025_API IRealCatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateCatBodyAnimation(EGMTK_RealCatBodyStates NewState);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateCatHandAnimation(EGMTK_RealCatHandStates NewState);
};
