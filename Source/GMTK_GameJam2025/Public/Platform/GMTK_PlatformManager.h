// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstance.h"
#include "Data/GMTK_Enums.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/BoxComponent.h"
#include "Platform/GMTK_PlatformActor.h"
#include "Character/GMTK_CatBase.h"
#include "GMTK_PlatformManager.generated.h"

UCLASS()
class GMTK_GAMEJAM2025_API AGMTK_PlatformManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGMTK_PlatformManager();

	void GetInitialPlatformActors();
	void UpdatePlatformMaterials();
	void RandomizeInView(int N);
	TArray<AGMTK_PlatformActor*> GetPlatformsInView();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AGMTK_PlatformActor*> PlatformActors;
	AGMTK_CatBase* CatRef = nullptr;
	UBoxComponent* VisionBox = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	float XStep = 51.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	float ZStep = 211.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	float XMin = -1546.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	float XMax = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	float ZMin = 149.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	float ZMax = 995.0f;

	// Dictionary for material instances
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	TMap<EGMTK_PlatformTracks, UMaterialInstance*> PlatformTrackMaterials;

	// Dictionary for positional values per track
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	TMap<EGMTK_PlatformTracks, float> PlatformTrackZ;

	// Individual float for Y tolerance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Data")
	float Tolerance = 100.0f;
};
