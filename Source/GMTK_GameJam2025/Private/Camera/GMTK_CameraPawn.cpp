// Scyte Studio 2025 ⓒ Copyright


#include "Camera/GMTK_CameraPawn.h"

#include "Camera/CameraComponent.h"
#include "Character/GMTK_CatBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlatformManager.h"
#include "Kismet/GameplayStatics.h"

AGMTK_CameraPawn::AGMTK_CameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
}

void AGMTK_CameraPawn::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController = GetController<APlayerController>())
	{
		if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(GMTKMap, 0);
		}
	}
	CatRef = Cast<AGMTK_CatBase>(UGameplayStatics::GetActorOfClass(this, AGMTK_CatBase::StaticClass()));
	PlatformManagerRef = Cast<APlatformManager>(UGameplayStatics::GetActorOfClass(this, APlatformManager::StaticClass()));
	if (CatRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cat is alive"));
	}
	
}

void AGMTK_CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGMTK_CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Cat Binding
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this
		, &AGMTK_CameraPawn::MoveCat);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this
		, &AGMTK_CameraPawn::JumpCatStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this
		, &AGMTK_CameraPawn::JumpCatEnd);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this
		, &AGMTK_CameraPawn::DashCat);

		// Platform Binding
		EnhancedInputComponent->BindAction(MovePlatformAction, ETriggerEvent::Started, this
			, &AGMTK_CameraPawn::MovePlatform);
		
		EnhancedInputComponent->BindAction(SelectPlatformAction, ETriggerEvent::Started, this
			, &AGMTK_CameraPawn::SelectPlatform);
	}
}

void AGMTK_CameraPawn::MoveCat(const FInputActionValue& Value)
{
	if (CatRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cat is Moving"));
		float MoveActionValue = Value.Get<float>();
		CatRef->MoveCat(MoveActionValue);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cat Not Found"));
	}
}

void AGMTK_CameraPawn::JumpCatStart(const FInputActionValue& Value)
{
	if (CatRef)
	{
		CatRef->Jump();
	}
}

void AGMTK_CameraPawn::JumpCatEnd(const FInputActionValue& Value)
{
	if (CatRef)
	{
		CatRef->StopJumping();
	}
}

void AGMTK_CameraPawn::DashCat(const FInputActionValue& Value)
{
	if (CatRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dash Pressed"));
		CatRef->DashCat();
	}
}

void AGMTK_CameraPawn::MovePlatform(const FInputActionValue& Value)
{
	if (PlatformManagerRef)
	{
		// Log for debug
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan,
			FString::Printf(TEXT("Platform Manager Ref Found - Can Move Platform")));
	}
}

void AGMTK_CameraPawn::SelectPlatform(const FInputActionValue& Value)
{
	if (PlatformManagerRef)
	{
		// Log for debug
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan,
			FString::Printf(TEXT("Platform Manager Ref Found - Can Select Platform")));
	}
}

