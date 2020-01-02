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

	//���� �̵� ó��
	UFUNCTION()
	void MoveForward(float Value);

	//�¿� �̵� ó��
	UFUNCTION()
	void MoveRight(float Value);

	//Ű�� ������ ���� �÷��� ����
	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	//�߻� �Լ�
	UFUNCTION()
	void Fire();

	//FPS ī�޶�
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	//�� �޽�: 1��Ī ���� - �ڽſ��Ը� ���̴� ��
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	//ī�޶� ��ġ������ �ѱ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	//������ų ������Ÿ�� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

};
