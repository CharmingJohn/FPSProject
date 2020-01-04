// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class FPSPROJECT_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//��ü �ݸ��� ������Ʈ
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	//������Ÿ�� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	//������Ÿ���� �ӵ��� �߻� �������� �ʱ�ȭ
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
};
