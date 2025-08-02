// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperZDAnimInstance.h"
#include "GMTK_CatBase.generated.h"

class USpringArmComponent;
class USceneCaptureComponent2D;
/**
 * 
 */
UCLASS()
class GMTK_GAMEJAM2025_API AGMTK_CatBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AGMTK_CatBase();

	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Cat|Components")
	USceneCaptureComponent2D* CaptureComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Cat|Components")
	USpringArmComponent* SpringArm;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cat|Params")
	bool bCanMove{ true };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cat|Params")
	bool bCanDash{ true };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cat|Params")
	bool bFacingRight{ true };

	
	// Animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cat|Animations")
	UPaperZDAnimSequence* DashAnimSequence;

	//Delegates
	FZDOnAnimationOverrideEndSignature OnDashOverrideEndDelegate;
	
	// Helper Functions
	void UpdateDirection(float MoveDirection);
	void OnDashOverrideAnimEnd(bool Completed);

	void MoveCat(float Direction);
	void DashCat();
	void JumpCat();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
