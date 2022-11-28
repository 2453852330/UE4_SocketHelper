// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketActor.h"
#include "SocketExample.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETHELPER_API ASocketExample : public ASocketActor
{
	GENERATED_BODY()

public:
	virtual void CF_ReceiveData(TArray<uint8> buffer, int32 size) override;
	
	// we need a function to handle CF_ReceiveData() function in game thread
	void CF_HandleFunction();


	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnActorClass = nullptr;

	UPROPERTY()
	TArray<AActor*> SpawnActorList;

	/** @LOG {2022/11/28-16:59} helper */
	FVector CF_GetRandomVector(float Radius);
	FRotator CF_GetRandomRotator();

	// it's also crash with same reason
	void CF_TrySpawnInFunction();

	// it's also crash with same reason
	UFUNCTION()
	void CF_TrySpawnInUFUNCTION();

	// it's run normal , cant find why crash when stop run ???
	void CF_TryCallInGameThread();


	// spawn num
	UPROPERTY(EditAnywhere)
	int32 SpawnNum = 1000;
	UPROPERTY(EditAnywhere)
	float SpawnRadius = 1000.f;


	/** @LOG {2022/11/28-17:17}  cant find crash reason ? maybe is other reason ... */
};

