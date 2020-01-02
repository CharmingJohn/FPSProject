// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSCharacter.h"
#include "Engine.h"
#include "FPSProjectile.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1��Ī ī�� ������Ʈ ����
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//ī�޶� ������Ʈ�� ĸ�� ������Ʈ�� ����
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	//ī�޶� ��ġ�� �� ��¦ ����
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	//���� ī�޶� �����̼� ��� ����մϴ�.
	FPSCameraComponent->bUsePawnControlRotation = true;

	//����Ī �޽� ������Ʈ
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	//���� �÷��̾ �޽ø� �� �� ����
	FPSMesh->SetOnlyOwnerSee(true);

	//FPSMesh�� FPSCamera�� ����
	FPSMesh->SetupAttachment(FPSCameraComponent);

	//�Ϻ� ȯ�� �������� �� �޽ð� �ϳ��� �� ���̴� ������ ����
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//�ڽ� �̿� ��ΰ� �Ϲ� ���� �޽ø� �� �� �ֽ��ϴ�.
	GetMesh()->SetOwnerNoSee(true);
	
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter"));
	}
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//"movement" ���ε� ����
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// "look" ���ε� ����
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	//"action" ���ε� ����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump); //�۵� �� ��.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	
}

void AFPSCharacter::MoveForward(float Value) {
	//���� �̵�, ����ؼ� ���� �Ѱ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value) {
	//�¿� �̵�, ����ؼ� ���� �Ѱ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump() {
	bPressedJump = true;
}

void AFPSCharacter::StopJump() {
	bPressedJump = false;
}

void AFPSCharacter::Fire() {
	//������Ÿ�� �߻� �õ�
	if (ProjectileClass)
	{
		//ī�޶� Ʈ������ ����
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//MuzzleOffset�� ī�޶� �����̽����� ���� �����̽��� ��ȯ�մϴ�.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;

		//������ �ణ �������� �÷��ݴϴ�.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();

		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//�ѱ� ��ġ�� �߻�ü�� ������ŵ�ϴ�.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile)
			{
				//�߻� ������ �˾Ƴ��ϴ�.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}
