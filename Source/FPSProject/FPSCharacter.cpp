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

	//1인칭 카페 컴포넌트 생성
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//카메라 컴포넌트를 캡슐 컴포넌트에 붙임
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	//카메라 위치를 눈 살짝 위로
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	//폰의 카메라 로테이션 제어를 허용합니다.
	FPSCameraComponent->bUsePawnControlRotation = true;

	//일인칭 메시 컴포넌트
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	//소유 플레이어만 메시를 볼 수 있음
	FPSMesh->SetOnlyOwnerSee(true);

	//FPSMesh를 FPSCamera에 붙임
	FPSMesh->SetupAttachment(FPSCameraComponent);

	//일부 환경 섀도잉을 꺼 메시가 하나인 듯 보이는 느낌을 유지
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//자신 이외 모두가 일반 몸통 메시를 볼 수 있습니다.
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

	//"movement" 바인딩 구성
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// "look" 바인딩 구성
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	//"action" 바인딩 구성
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump); //작동 안 됨.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	
}

void AFPSCharacter::MoveForward(float Value) {
	//전후 이동, 기록해서 값을 넘겨줌
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value) {
	//좌우 이동, 기록해서 값을 넘겨줌
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
	//프로젝타일 발사 시도
	if (ProjectileClass)
	{
		//카메라 트랜스폼 구현
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//MuzzleOffset을 카메라 스페이스에서 월드 스페이스로 변환합니다.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;

		//조준을 약간 윗쪽으로 올려줍니다.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();

		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//총구 위치에 발사체를 스폰시킵니다.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile)
			{
				//발사 방향을 알아냅니다.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}
