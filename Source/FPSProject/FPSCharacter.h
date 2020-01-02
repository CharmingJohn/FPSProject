// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//전후 이동 처리
	UFUNCTION()
	void MoveForward(float Value);

	//좌우 이동 처리
	UFUNCTION()
	void MoveRight(float Value);

	//키를 누르면 점프 플래그 설정
	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	//발사 함수
	UFUNCTION()
	void Fire();

	//FPS 카메라
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	//폰 메시: 1인칭 시점 - 자신에게만 보이는 팔
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	//카메라 위치에서의 총구 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	//스폰시킬 프로젝타일 클래스
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

};
