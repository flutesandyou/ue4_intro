// Copyright Epic Games, Inc. All Rights Reserved.

#include "IntroCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "WheeledVehicle.h"
#include "Kismet/GameplayStatics.h"
#include "IntroGameInstance.h"

//////////////////////////////////////////////////////////////////////////
// AIntroCharacter

AIntroCharacter::AIntroCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AIntroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("SitInACar", IE_Pressed, this, &AIntroCharacter::SitInACar);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AIntroCharacter::Fire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AIntroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIntroCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AIntroCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AIntroCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AIntroCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AIntroCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AIntroCharacter::OnResetVR);
}


void AIntroCharacter::ExitACar()
{
	AController* CurrentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (IsValid(CurrentActiveChar))
	{
		CurrentController->Possess(CurrentActiveChar);
	}

 	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetVisibility(true);
}

void AIntroCharacter::SitInACar()
{
	AController* CurrentController = GetController();
	if (IsValid(CurrentActiveCar))
	{
		CurrentController->Possess(CurrentActiveCar);
	}
	AttachToActor(CurrentActiveCar, FAttachmentTransformRules::KeepRelativeTransform);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
	GetMesh()->SetVisibility(false);
}

void AIntroCharacter::OnResetVR()
{
	// If Intro is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Intro.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AIntroCharacter::Fire()
{
	if (!IsValid(ProjectileType))
	{
		return;
	}
	FRotator SpawningRotation = GetActorRotation();
	FVector SpawningLocation = GetActorLocation() + SpawningRotation.RotateVector(FiringOffset);
	AActor* SpawnedActor = GetWorld()->SpawnActor(ProjectileType, &SpawningLocation, &SpawningRotation);
	if (IsValid(SpawnedActor))
	{
		UPrimitiveComponent* RootPrimitive = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
		if (IsValid(RootPrimitive))
		{
			RootPrimitive->AddImpulse(RootPrimitive->GetForwardVector() * FireVelocity, NAME_None, true);
		}
	}
}

void AIntroCharacter::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceDynamic* NewMaterialInstance = GetMesh()->CreateDynamicMaterialInstance(0);
	UIntroGameInstance* GameInstance = Cast<UIntroGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GameInstance) && IsValid(NewMaterialInstance))
	{
		NewMaterialInstance->SetVectorParameterValue(FName("BodyColor"), FLinearColor(GameInstance->GetPlayerColor()));
	}
}

void AIntroCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AIntroCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AIntroCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AIntroCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AIntroCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AIntroCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}