// Scyte Studio 2025 ⓒ Copyright


#include "Character/GMTK_RealCatBase.h"

#include "PaperFlipbookComponent.h"


// Sets default values
AGMTK_RealCatBase::AGMTK_RealCatBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGMTK_RealCatBase::BeginPlay()
{
	Super::BeginPlay();
	// UpdateCatState(EGMTK_RealCatBodyStates::ERCS_Sleep);
	
}

// Called every frame
void AGMTK_RealCatBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGMTK_RealCatBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGMTK_RealCatBase::UpdateCatBodyAnimation_Implementation(EGMTK_RealCatBodyStates NewState)
{
	CurrentState = NewState;
}

