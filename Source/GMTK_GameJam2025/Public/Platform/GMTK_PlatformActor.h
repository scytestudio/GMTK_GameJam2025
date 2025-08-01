// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/GMTK_Enums.h"
#include "GMTK_PlatformActor.generated.h"

UCLASS()
class GMTK_GAMEJAM2025_API AGMTK_PlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGMTK_PlatformActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	EGMTK_PlatformTracks PlatformTrack;
};
