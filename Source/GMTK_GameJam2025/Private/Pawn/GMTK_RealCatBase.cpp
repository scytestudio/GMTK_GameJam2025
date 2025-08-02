// Scyte Studio 2025 ⓒ Copyright


#include "Pawn/GMTK_RealCatBase.h"

#include "PaperFlipbookComponent.h"


// Sets default values
AGMTK_RealCatBase::AGMTK_RealCatBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	CatHandFlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("Cat Hand Flip Book");
	CatHandFlipBook->SetupAttachment(GetSprite());
}

void AGMTK_RealCatBase::UpdateCatState(EGMTK_RealCatStates NewState)
{
	CurrentState = NewState;
	// only update the hand Flipbook
	if (CatHandFLBK)
	{
		if (CurrentState == EGMTK_RealCatStates::ERCS_Hand)
		{CatHandFlipBook->SetFlipbook(CatHandFLBK);}
		else
		{
			CatHandFlipBook->SetFlipbook(nullptr);
		}
	}
}

// Called when the game starts or when spawned
void AGMTK_RealCatBase::BeginPlay()
{
	Super::BeginPlay();
	UpdateCatState(EGMTK_RealCatStates::ERCS_Sleep);
	
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

