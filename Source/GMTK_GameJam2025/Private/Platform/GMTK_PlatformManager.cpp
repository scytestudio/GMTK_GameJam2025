// Scyte Studio 2025 ⓒ Copyright


#include "Platform/GMTK_PlatformManager.h"
#include "Engine/TextureRenderTarget2D.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AGMTK_PlatformManager::AGMTK_PlatformManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGMTK_PlatformManager::BeginPlay()
{
	Super::BeginPlay();

    CatRef = Cast<AGMTK_CatBase>(UGameplayStatics::GetActorOfClass(this, AGMTK_CatBase::StaticClass()));
    VisionBox = CatRef->FindComponentByClass<UBoxComponent>();

	GetInitialPlatformActors();
    UpdatePlatformMaterials();
}

// Called every frame
void AGMTK_PlatformManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGMTK_PlatformManager::UpdatePlatformMaterials()
{
    for (AGMTK_PlatformActor* PlatformActor : PlatformActors)
    {
        FVector ActorLocation = PlatformActor->GetActorLocation();
        float Z = ActorLocation.Z;

        // Find the matching track based on Y and Tolerance
        EGMTK_PlatformTracks MatchedTrack = EGMTK_PlatformTracks::EPTS_Lead; // Replace with your default if needed
        bool bFound = false;
        for (const TPair<EGMTK_PlatformTracks, float>& Pair : PlatformTrackZ)
        {
            if (FMath::Abs(Pair.Value - Z) <= Tolerance)
            {
                MatchedTrack = Pair.Key;
                bFound = true;
                break;
            }
        }

        if (!bFound)
            continue;

        // Get the material instance for the matched track
        UMaterialInstance* MaterialInstance = nullptr;
        if (PlatformTrackMaterials.Contains(MatchedTrack))
            MaterialInstance = PlatformTrackMaterials[MatchedTrack];

        PlatformActor->PlatformTrack = MatchedTrack;

        // Set our material.
        UStaticMeshComponent* MeshComp = PlatformActor->FindComponentByClass<UStaticMeshComponent>();
        if (MeshComp)
            MeshComp->SetMaterial(0, MaterialInstance);
    }
}

void AGMTK_PlatformManager::GetInitialPlatformActors()
{
    TArray<AActor*> ChildrenCpy;
    GetAttachedActors(ChildrenCpy);

    // WHY OH WHY DOES TARRAY NOT HAVE A FILTER.
    for (AActor* Child : ChildrenCpy)
    {
        AGMTK_PlatformActor* PlatformActor = Cast<AGMTK_PlatformActor>(Child);
        if (!PlatformActor)
            continue;

        PlatformActors.Add(PlatformActor);
    }
}

TArray<AGMTK_PlatformActor*> AGMTK_PlatformManager::GetPlatformsInView()
{
    TArray<AGMTK_PlatformActor*> InView;

    TArray<AActor*> OverlappingActors;
    VisionBox->GetOverlappingActors(OverlappingActors, AGMTK_PlatformActor::StaticClass());

    for (AActor* Actor : OverlappingActors)
    {
        if (AGMTK_PlatformActor* Platform = Cast<AGMTK_PlatformActor>(Actor))
            InView.Add(Platform);
    }

    return InView;
}

void AGMTK_PlatformManager::RandomizeInView(int N) 
{
    // Get our in view platforms and filter out any that are static.
    TArray<AGMTK_PlatformActor*> inView = GetPlatformsInView();
    inView.RemoveAll([this](AGMTK_PlatformActor* a) {
        return !PlatformActors.Contains(a);
    });

    if (inView.Num() == 0 || N <= 0)
        return;
    N = FMath::Min(N, inView.Num());

    // Shuffle and pick N random platforms
    inView.Sort([](const AGMTK_PlatformActor& A, const AGMTK_PlatformActor& B) { return FMath::Rand() < FMath::Rand(); });
    TArray<AGMTK_PlatformActor*> Selected;
    for (int i = 0; i < N; ++i)
        Selected.Add(inView[i]);

    for (AGMTK_PlatformActor* Platform : Selected)
    {
        FVector OriginalLocation = Platform->GetActorLocation();
        UBoxComponent* BoxComp = Platform->FindComponentByClass<UBoxComponent>();
        if (!BoxComp)
            continue;

        bool bPlaced = false;
        const int MaxAttempts = 10;
        for (int Attempt = 0; Attempt < MaxAttempts && !bPlaced; ++Attempt)
        {
            FVector NewLocation = OriginalLocation;

            // Randomly choose to move on X or Z
            bool bMoveX = FMath::RandBool();
            float Step = bMoveX ? XStep : ZStep;
            float Offset = FMath::RandBool() ? Step : -Step;

            if (bMoveX)
                NewLocation.X += Offset;
            else
                NewLocation.Z += Offset;

            NewLocation.X = FMath::Clamp(NewLocation.X, XMin, XMax);
            NewLocation.Z = FMath::Clamp(NewLocation.Z, ZMin, ZMax);

            // Prepare collision shape and transform
            FCollisionShape BoxShape = FCollisionShape::MakeBox(BoxComp->GetUnscaledBoxExtent());
            FTransform BoxTransform = Platform->GetActorTransform();
            BoxTransform.SetLocation(NewLocation);

            // Set up query params to ignore this platform
            FCollisionQueryParams Params;
            Params.AddIgnoredActor(Platform);

            // Check for overlap at the new location
            bool bOverlaps = Platform->GetWorld()->OverlapAnyTestByChannel(
                NewLocation,
                BoxTransform.GetRotation(),
                BoxComp->GetCollisionObjectType(),
                BoxShape,
                Params
            );

            if (!bOverlaps)
            {
                Platform->SetActorLocation(NewLocation);
                bPlaced = true;
            }
        }
    }
}