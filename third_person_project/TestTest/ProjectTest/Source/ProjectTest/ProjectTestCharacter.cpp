// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectTestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectTestCharacter

AProjectTestCharacter::AProjectTestCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AProjectTestCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BEGIN PLAY START"));

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		UE_LOG(LogTemp, Warning, TEXT("GAS initialized"));

		//  TEST DAMAGE
		FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();

		TSubclassOf<UGameplayEffect> DamageEffect = LoadClass<UGameplayEffect>(
			nullptr, TEXT("/Game/ThirdPerson/Blueprints/GE_Damage.GE_Damage_C"));

		if (!DamageEffect)
		{
			UE_LOG(LogTemp, Error, TEXT("DamageEffect NOT FOUND"));
			return;
		}

		FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(
			DamageEffect, 1.f, Context);

		if (Spec.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());

			UE_LOG(LogTemp, Warning, TEXT("Damage Applied"));

			UE_LOG(LogTemp, Warning, TEXT("BEGIN PLAY START"));

			GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
				{
					UE_LOG(LogTemp, Warning, TEXT("Health AFTER: %f"),
						AttributeSet->GetHealth());
				});

				}
		UE_LOG(LogTemp, Warning, TEXT("BEFORE HEAL"));

			TSubclassOf<UGameplayEffect> HealEffect = LoadClass<UGameplayEffect>(
				nullptr, TEXT("/Game/ThirdPerson/Blueprints/GE_Heal.GE_Heal_C"));

			UE_LOG(LogTemp, Warning, TEXT("Reached Heal Block"));

		if (!HealEffect)
			
		{
			UE_LOG(LogTemp, Error, TEXT("HealEffect NOT FOUND"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("INSIDE HEAL BLOCK"));

			FGameplayEffectSpecHandle HealSpec =
				AbilitySystemComponent->MakeOutgoingSpec(HealEffect, 1.f, Context);

			if (HealSpec.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*HealSpec.Data.Get());

				UE_LOG(LogTemp, Warning, TEXT("Heal Applied"));

				GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
					{
						UE_LOG(LogTemp, Warning, TEXT("Health AFTER HEAL: %f"),
							AttributeSet->GetHealth());
					});
			}
		}
		

		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->SetViewTarget(this);
		}
		}
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectTestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectTestCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjectTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
UAbilitySystemComponent* AProjectTestCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}