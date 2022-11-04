// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketManager.h"
#include "GameFramework/Actor.h"
#include "SocketActor.generated.h"

UCLASS()
class SOCKETHELPER_API ASocketActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocketActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void CF_ReceiveData(TArray<uint8> buffer,int32 size);

	UFUNCTION(BlueprintCallable)
	void CF_CreateSocket(FString Ip,int32 Port,int32 BufferSize);

	UFUNCTION(BlueprintCallable)
	void CF_CloseSocket();

	SocketManager * _socket = nullptr;
	FRunnableThread * _runnable = nullptr;
};
