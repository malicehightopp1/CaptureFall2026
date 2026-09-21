
#include "Characters/CCharacter.h"
#include "Abilitysystem/CAbilitySystemComponent.h"
#include "Abilitysystem/CAttributeSet.h"
#include "Capture/Capture.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/OverHeadStatusGauge.h"

// Sets default values
ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Created like any components are 
	AbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UCAttributeSet>(TEXT("AttributeSet"));	
	
	OverheadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Overhead Widget");
	OverheadWidgetComponent->SetupAttachment(GetRootComponent());
	
	//ignore channels
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_CameraBoom, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_CameraBoom, ECR_Ignore);
}

void ACCharacter::ServerSideInit()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this); //sets owner and editor of ability system
	AbilitySystemComponent->ApplyInitialEffects();
	AbilitySystemComponent->GiveInitialAbilities();
}
//init called on server and client side
void ACCharacter::ClientSideInit()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this); //sets owner and editor of ability system
}

void ACCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ConfigureOverheadWidgetComponent();
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ACCharacter::IsLocallyControlledByPlayer() const
{
	return IsLocallyControlled() && GetController()->IsPlayerController();
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACCharacter::ConfigureOverheadWidgetComponent()
{
	if (!OverheadWidgetComponent){return;}
	
	if (IsLocallyControlledByPlayer())
	{
		OverheadWidgetComponent->SetHiddenInGame(true);
		return;
	}
	
	UOverHeadStatusGauge* OverHeadStatusGauge = Cast<UOverHeadStatusGauge>(OverheadWidgetComponent->GetUserWidgetObject());
	
	if (OverHeadStatusGauge)
	{
		OverHeadStatusGauge->ConfigureWithAbilitySystemComponent(GetAbilitySystemComponent());
	}
}

