// Destruction Games. 2022


#include "Widgets/RPGHPBar_Widget.h"
#include "Characters/RPGPlayerCharacter.h"
#include "Components/RPGHealth_Component.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

bool URPGHPBar_Widget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}

	if (MainOverlay)
	{
		UOverlaySlot* HPBarSlot = CastChecked<UOverlaySlot>(MainOverlay->GetSlots()[0]);
		UOverlaySlot* TextHorizontalBoxSlot = CastChecked<UOverlaySlot>(MainOverlay->GetSlots()[1]);

		HPBarSlot->SetHorizontalAlignment(HAlign_Fill);
		HPBarSlot->SetVerticalAlignment(VAlign_Fill);

		TextHorizontalBoxSlot->SetHorizontalAlignment(HAlign_Fill);
		TextHorizontalBoxSlot->SetVerticalAlignment(VAlign_Fill);
	}

	if (HPBar)
	{
		HPBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f, 1.f));

		HPBar->PercentDelegate.BindUFunction(this, "GetCurrentHP_Percent");
	}

	if (TextHorizontalBox)
	{
		UHorizontalBoxSlot* CurrentHPTextSlot = CastChecked<UHorizontalBoxSlot>(TextHorizontalBox->GetSlots()[0]);
		UHorizontalBoxSlot* SlashTextSlot = CastChecked<UHorizontalBoxSlot>(TextHorizontalBox->GetSlots()[1]);
		UHorizontalBoxSlot* MaxHPTextSlot = CastChecked<UHorizontalBoxSlot>(TextHorizontalBox->GetSlots()[2]);

		FSlateChildSize CurrentHPTextSlotSize;
		CurrentHPTextSlotSize.SizeRule = ESlateSizeRule::Fill;
		CurrentHPTextSlotSize.Value = 0.3f;

		CurrentHPTextSlot->SetSize(CurrentHPTextSlotSize);
		CurrentHPTextSlot->SetHorizontalAlignment(HAlign_Right);
		CurrentHPTextSlot->SetVerticalAlignment(VAlign_Center);

		FSlateChildSize SlashTextSlotSize;
		SlashTextSlotSize.SizeRule = ESlateSizeRule::Fill;
		SlashTextSlotSize.Value = 0.01f;

		SlashTextSlot->SetSize(SlashTextSlotSize);
		SlashTextSlot->SetHorizontalAlignment(HAlign_Center);
		SlashTextSlot->SetVerticalAlignment(VAlign_Center);

		MaxHPTextSlot->SetSize(CurrentHPTextSlotSize); // Uses the same params as CurrentHPTextSlot
		MaxHPTextSlot->SetHorizontalAlignment(HAlign_Left);
		MaxHPTextSlot->SetVerticalAlignment(VAlign_Center);
	}

	if (CurrentHPText)
	{
		CurrentHPText->TextDelegate.BindUFunction(this, "GetCurrentHP");
	}

	if (SlashText)
	{
		SlashText->SetText(FText::FromString("/"));
	}

	if (MaxHPText)
	{
		MaxHPText->TextDelegate.BindUFunction(this, "GetMaxHP");
	}

	return true;
}

void URPGHPBar_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

float URPGHPBar_Widget::GetCurrentHP()
{
	return PlayerRef->HPComp->GetCurrentHP();
}

float URPGHPBar_Widget::GetCurrentHP_Percent()
{
	return GetCurrentHP() / 100.f;
}

float URPGHPBar_Widget::GetMaxHP()
{
	return PlayerRef->HPComp->GetMaxHP();
}
