// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketManager.h"
#include "GameFramework/Actor.h"
#include "SocketActor.generated.h"

UCLASS(Abstract)
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

	virtual void CF_ReceiveData(TArray<uint8> buffer,int32 size);

	UFUNCTION(BlueprintCallable)
	void CF_CreateSocket(FString Ip,int32 Port,int32 BufferSize);
	
	void CF_CloseSocket();

	void CF_GetThreadInfo(FString & Name,uint32 & ID);
	int32 CF_GetPort(){return _port;}
	FString CF_GetIp(){return  _ip;}
	int32 CF_GetBufferSize(){return _buffer_size;}
private:
	SocketManager * _socket = nullptr;
	FRunnableThread * _runnable = nullptr;

	FString _ip;
	int32 _port;
	int32 _buffer_size;
};
