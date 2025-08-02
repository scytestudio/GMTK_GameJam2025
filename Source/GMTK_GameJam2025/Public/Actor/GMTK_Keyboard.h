// Scyte Studio 2025 ⓒ Copyright

#pragma once

#include "CoreMinimal.h"
#include "Data/GMTK_Enums.h"
#include "GameFramework/Actor.h"
#include "GMTK_Keyboard.generated.h"

enum class EGMTK_KeyboardStates : uint8;
class UPaperFlipbook;

UCLASS()
class GMTK_GAMEJAM2025_API AGMTK_Keyboard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGMTK_Keyboard();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="00|Keyboard|Components")
	class UPaperFlipbookComponent* RightKeyBoard;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="00|Keyboard|Components")
	UPaperFlipbookComponent* LeftKeyboard;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="00|Keyboard|Params")
	UPaperFlipbook* LeftIdleFlipBook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="00|Keyboard|Params")
	UPaperFlipbook* LeftPlayFlipBook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="00|Keyboard|Params")
	UPaperFlipbook* RightIdleFlipBook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="00|Keyboard|Params")
	UPaperFlipbook* RightPlayFlipBook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="00|Keyboard|Params")
	EGMTK_KeyboardStates CurrentKeyboardState{ EGMTK_KeyboardStates::EKS_PlayBoth };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
