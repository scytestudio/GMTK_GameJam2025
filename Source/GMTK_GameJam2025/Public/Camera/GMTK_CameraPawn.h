// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GMTK_CameraPawn.generated.h"


struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class AGMTK_CatBase;
class AGMTK_PlatformManager;

UCLASS()
class GMTK_GAMEJAM2025_API AGMTK_CameraPawn : public APawn
{
	GENERATED_BODY()

public:
	AGMTK_CameraPawn();

	// Cat Reference
	AGMTK_CatBase* CatRef{ nullptr };
	//Platform Manager Ref
	AGMTK_PlatformManager* PlatformManagerRef{  nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera|Components")
	UCameraComponent* Camera;

	
	// Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs")
	UInputMappingContext* GMTKMap;

	// Cat Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs|Cat")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs|Cat")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs|Cat")
	UInputAction* VerticalJumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs|Cat")
	UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs|Cat")
	UInputAction* ShrinkAction;

	// Platform Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs|Cat")
	UInputAction* MovePlatformAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera|Inputs|Cat")
	UInputAction* SelectPlatformAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Inputs|Cat")
	UInputAction* Debug_RandomizePlatformsAction;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Cat Input Bindings
	void MoveCat(const FInputActionValue& Value);
	void JumpCatStart(const FInputActionValue& Value);
	void JumpCatEnd(const FInputActionValue& Value);
	void DashCat(const FInputActionValue& Value);
	void VerticalJumpCat(const FInputActionValue& Value);
	void ShrinkCat(const FInputActionValue& Value);
	
	void MovePlatform(const FInputActionValue& Value);
	void SelectPlatform(const FInputActionValue& Value);
	void DEBUG_RandomizePlatforms(const FInputActionValue& Value);
};
