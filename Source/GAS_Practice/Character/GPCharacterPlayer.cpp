// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GPCharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Data/Input/GPInputData.h"
#include "AbilitySystemComponent.h"
#include "Player/GPPlayerState.h"
#include "GameAbility/Tags/GPTags.h"
#include "Components/GPEquipComponent.h"

AGPCharacterPlayer::AGPCharacterPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);

	EquipComp = CreateDefaultSubobject<UGPEquipComponent>(TEXT("Equip Component"));

	ASComp = nullptr;
}

void AGPCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->IMC_Default, 0);
		}
	}
}

void AGPCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputData->IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(InputData->IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(InputData->IA_Jump, ETriggerEvent::Started, this, &ThisClass::GASInputPressed, 0);
	EnhancedInputComponent->BindAction(InputData->IA_Jump, ETriggerEvent::Completed, this, &ThisClass::GASInputReleased, 0);
	EnhancedInputComponent->BindAction(InputData->IA_Attack, ETriggerEvent::Started, this, &ThisClass::GASInputPressed, 1);
}

void AGPCharacterPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGPCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void AGPCharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

UAbilitySystemComponent* AGPCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASComp;
}

void AGPCharacterPlayer::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (ASComp)
	{
		ASComp->GetOwnedGameplayTags(TagContainer);
	}
}

void AGPCharacterPlayer::InitAbilityActorInfo()
{
	AGPPlayerState* PS = GetPlayerState<AGPPlayerState>();
	if (PS)
	{
		ASComp = PS->GetAbilitySystemComponent();
		ASComp->InitAbilityActorInfo(PS, this);

		for (const TSubclassOf<UGameplayAbility>& DefaultAbility : DefaultAbilities)
		{
			FGameplayAbilitySpec DefaultSpec(DefaultAbility);
			ASComp->GiveAbility(DefaultSpec);
		}

		for (const TPair<TSubclassOf<UGameplayAbility>, int32>& InputAbility : InputAbilities)
		{
			FGameplayAbilitySpec InputSpec(InputAbility.Key);
			InputSpec.InputID = InputAbility.Value;
			ASComp->GiveAbility(InputSpec);
		}

		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}

void AGPCharacterPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, InputValue.X);
	AddMovementInput(RightVector, InputValue.Y);
}

void AGPCharacterPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(-InputValue.Y);
}

void AGPCharacterPlayer::GASInputPressed(int32 InputID)
{
	FGameplayAbilitySpec* Spec = ASComp->FindAbilitySpecFromInputID(InputID);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASComp->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASComp->TryActivateAbility(Spec->Handle);
		}
	}
}

void AGPCharacterPlayer::GASInputReleased(int32 InputID)
{
	FGameplayAbilitySpec* Spec = ASComp->FindAbilitySpecFromInputID(InputID);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASComp->AbilitySpecInputReleased(*Spec);
		}
	}
}
