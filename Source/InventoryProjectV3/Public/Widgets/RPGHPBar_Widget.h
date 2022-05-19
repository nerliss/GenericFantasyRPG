// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGHPBar_Widget.generated.h"

class UProgressBar;
class ARPGPlayerCharacter;
class UTextBlock;
class UOverlay;
class UHorizontalBox;

UCLASS()
class INVENTORYPROJECTV3_API URPGHPBar_Widget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	bool Initialize() override;

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UOverlay* MainOverlay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHorizontalBox* TextHorizontalBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CurrentHPText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* SlashText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* MaxHPText;

	ARPGPlayerCharacter* PlayerRef;

private:

	float GetCurrentHP();

	float GetCurrentHP_Percent();

	float GetMaxHP();

};
