// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Data/GMTK_Enums.h"
#include "Data/Interfaces/RealCatInterface.h"
#include "GameFramework/Pawn.h"
#include "GMTK_RealCatBase.generated.h"

class UPaperFlipbook;
enum class EGMTK_RealCatBodyStates : uint8;
enum class EGMTK_RealCatHandStates : uint8;

UCLASS()
class GMTK_GAMEJAM2025_API AGMTK_RealCatBase : public APaperZDCharacter, public IRealCatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGMTK_RealCatBase();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="00|Real Cat|Components")
	class UPaperFlipbookComponent* CatHandFlipBook;
	
	// Flipbooks
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="00|Real Cat|FlipBooks")
	UPaperFlipbook* CatHandFLBK;
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="00|Real Cat|Props",meta=(AllowPrivateAccess = "true"))
	EGMTK_RealCatBodyStates CurrentState{ EGMTK_RealCatBodyStates::ERCS_Sleep };

	
protected:
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void UpdateCatBodyAnimation_Implementation(EGMTK_RealCatBodyStates NewState) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EGMTK_RealCatBodyStates GetCatState() const { return CurrentState; }
};
