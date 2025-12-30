
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStoryLine.generated.h"


class UImage;
class UButton;
class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterStoryLine : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Close;

	void Init(UTexture2D* Image, const FString& Name, const FString& Story);
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CharacterName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_StoryLine;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Character;
};
