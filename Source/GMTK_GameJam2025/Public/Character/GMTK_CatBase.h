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
	bool bCanVerticalJump{ true };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cat|Params")
	bool bCanShrink{ true };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cat|Params")
	bool bFacingRight{ true };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cat|Params")
	bool bIsCtrlPressed{ false };

	
	// Animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cat|Animations")
	UPaperZDAnimSequence* DashAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cat|Animations")
	UPaperZDAnimSequence* ShrinkAnimSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cat|Animations")
	UPaperZDAnimSequence* VerticalJumpAnimSequence;

	//Delegates
	FZDOnAnimationOverrideEndSignature OnDashOverrideEndDelegate;
	FZDOnAnimationOverrideEndSignature OnShrinkOverrideEndDelegate;
	FZDOnAnimationOverrideEndSignature OnVerticalJumpOverrideEndDelegate;
	
	// Helper Functions
	void UpdateDirection(float MoveDirection);
	void OnDashOverrideAnimEnd(bool Completed);
	void OnShrinkOverrideAnimEnd(bool Completed);
	void OnVerticalJumpOverrideAnimEnd(bool Completed);

	void MoveCat(float Direction);
	void DashCat();
	void ShrinkCat();
	void VerticalJumpCat();
	void JumpCat();

	FTimerHandle OnJumpTimer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
