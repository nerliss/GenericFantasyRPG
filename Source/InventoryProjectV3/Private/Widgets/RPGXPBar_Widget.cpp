// Destruction Games. 2022


#include "Widgets/RPGXPBar_Widget.h"
#include "Components/ProgressBar.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/RPGXP_Component.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/RPGPlayerCharacter.h"

bool URPGXPBar_Widget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}

	// Set reference to player
	PlayerRef = Cast<ARPGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (MainOverlay)
	{
		UOverlaySlot* Bar_BufferSlot = CastChecked<UOverlaySlot>(MainOverlay->GetSlots()[0]);
		UOverlaySlot* Bar_XPSlot = CastChecked<UOverlaySlot>(MainOverlay->GetSlots()[1]);
		UOverlaySlot* MainHorizontalBoxSlot = CastChecked<UOverlaySlot>(MainOverlay->GetSlots()[2]);

		Bar_BufferSlot->SetHorizontalAlignment(HAlign_Fill);
		Bar_BufferSlot->SetVerticalAlignment(VAlign_Fill);

		Bar_XPSlot->SetHorizontalAlignment(HAlign_Fill);
		Bar_XPSlot->SetVerticalAlignment(VAlign_Fill);

		MainHorizontalBoxSlot->SetHorizontalAlignment(HAlign_Fill);
		MainHorizontalBoxSlot->SetVerticalAlignment(VAlign_Center);
	}

	if (Bar_Buffer)
	{
		Bar_Buffer->SetFillColorAndOpacity(FLinearColor(0.79f, 0.f, 0.6f, 1.f));

		Bar_Buffer->PercentDelegate.BindUFunction(this, "GetCurrentPercentageBuffer");
	}

	if (Bar_XP)
	{
		Bar_XP->SetFillColorAndOpacity(FLinearColor(0.17f, 0.f, 0.13f, 1.f));

		Bar_XP->PercentDelegate.BindUFunction(this, "GetCurrentPercentageXP");
	}

	if (MainHorizontalBox)
	{
		UHorizontalBoxSlot* LevelTextSlot = CastChecked<UHorizontalBoxSlot>(MainHorizontalBox->GetSlots()[0]);
		UHorizontalBoxSlot* ExperienceHorizontalBoxSlot = CastChecked<UHorizontalBoxSlot>(MainHorizontalBox->GetSlots()[1]);

		LevelTextSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		LevelTextSlot->SetHorizontalAlignment(HAlign_Fill);
		LevelTextSlot->SetVerticalAlignment(VAlign_Fill);

		ExperienceHorizontalBoxSlot->SetSize(FSlateChildSize());
		ExperienceHorizontalBoxSlot->SetHorizontalAlignment(HAlign_Center);
		ExperienceHorizontalBoxSlot->SetVerticalAlignment(VAlign_Center);
	}

	if (LevelText)
	{
		LevelText->TextDelegate.BindUFunction(this, "GetCurrentLevel");
	}

	if (ExperienceHorizontalBox)
	{
		UHorizontalBoxSlot* XP_CurrentTextSlot = CastChecked<UHorizontalBoxSlot>(ExperienceHorizontalBox->GetSlots()[0]);
		UHorizontalBoxSlot* SlashTextSlot = CastChecked<UHorizontalBoxSlot>(ExperienceHorizontalBox->GetSlots()[1]);
		UHorizontalBoxSlot* XP_MaxTextSlot = CastChecked<UHorizontalBoxSlot>(ExperienceHorizontalBox->GetSlots()[2]);

		XP_CurrentTextSlot->SetVerticalAlignment(VAlign_Fill);
		XP_CurrentTextSlot->SetHorizontalAlignment(HAlign_Fill);

		SlashTextSlot->SetVerticalAlignment(VAlign_Fill);
		SlashTextSlot->SetHorizontalAlignment(HAlign_Fill);

		XP_MaxTextSlot->SetVerticalAlignment(VAlign_Fill);
		XP_MaxTextSlot->SetHorizontalAlignment(HAlign_Fill);
	}

	if (XP_CurrentText)
	{
		XP_CurrentText->TextDelegate.BindUFunction(this, "GetCurrentXP");
	}

	if (SlashText)
	{
		SlashText->SetText(FText::FromString("/"));
	}

	if (XP_MaxText)
	{
		XP_MaxText->TextDelegate.BindUFunction(this, "GetCurrentMaxXP");
	}

	return true;
}

void URPGXPBar_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

int32 URPGXPBar_Widget::GetCurrentLevel()
{
	return PlayerRef->XPComp->GetLevelCurrent();
}

float URPGXPBar_Widget::GetCurrentXP()
{
	return PlayerRef->XPComp->GetXP_Current();
}

float URPGXPBar_Widget::GetCurrentMaxXP()
{
	return PlayerRef->XPComp->GetXP_Current_Max();
}

float URPGXPBar_Widget::GetCurrentPercentageBuffer()
{
	return PlayerRef->XPComp->GetCurrentPercentage_Buffer();
}

float URPGXPBar_Widget::GetCurrentPercentageXP()
{
	return PlayerRef->XPComp->GetCurrentPercentage_XP();
}
