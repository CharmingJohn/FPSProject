// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSProjectile.h"
#include "Engine.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//구체를 단순 컬리전 표현으로 사용함
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPhereComponent"));

	//컬리전 반경 설정
	CollisionComponent->InitSphereRadius(15.0f);

	//루트 컴포넌트를 컬리전 컴포넌트로 설정.
	RootComponent = CollisionComponent;

	//ProjectileMovementComponent를 이용하여 발사체의 운동을 관장.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection) {
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

