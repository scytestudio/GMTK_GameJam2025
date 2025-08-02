// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GMTK_CatBase.h"

#include "PaperFlipbookComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGMTK_CatBase::AGMTK_CatBase()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent2D");
	CaptureComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AGMTK_CatBase::UpdateDirection(float MoveDirection)
{
	if (MoveDirection < 0.0f)
	{
		FVector SpriteVectorScale = FVector(-0.25f, 0.25f, 0.25f);
		GetSprite()->SetWorldScale3D(SpriteVectorScale);
		bFacingRight = false;
	}
	if (MoveDirection > 0.0f)
	{
		FVector SpriteVectorScale = FVector(0.25f, 0.25f, 0.25f);
		GetSprite()->SetWorldScale3D(SpriteVectorScale);
		bFacingRight = true;
	}
}

void AGMTK_CatBase::OnDashOverrideAnimEnd(bool Completed)
{
	bCanDash = true;
	
	UE_LOG(LogTemp, Warning, TEXT("Dash Completed"));
}

void AGMTK_CatBase::MoveCat(float Direction)
{
	if (bCanMove)
	{
		UpdateDirection(Direction);
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Direction);
	}
}

void AGMTK_CatBase::DashCat()
{
	if (bCanDash && bCanMove && !GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("Initiate Dash"));
		bCanDash = false;
		float LaunchVelocityX = bFacingRight ? 1000.0f : -1000.0f;
		float LaunchVelocityZ = 1000.0f;
		FVector LaunchVelocity = FVector(LaunchVelocityX, 0.0f, LaunchVelocityZ);
		LaunchCharacter(LaunchVelocity, false, false);
		GetAnimInstance()->PlayAnimationOverride(DashAnimSequence, FName("DefaultSlot"), 1.0f, 0.0f, OnDashOverrideEndDelegate);
		
	}
}

void AGMTK_CatBase::JumpCat()
{
	if (bCanMove)
	{
		Jump();
	}
}
