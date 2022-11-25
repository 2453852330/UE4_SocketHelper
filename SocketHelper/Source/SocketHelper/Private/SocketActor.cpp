// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketActor.h"

// Sets default values
ASocketActor::ASocketActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASocketActor::BeginPlay()
{
	Super::BeginPlay();
	
}



void ASocketActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CF_CloseSocket();
	Super::EndPlay(EndPlayReason);
}

void ASocketActor::Destroyed()
{
	CF_CloseSocket();
	Super::Destroyed();
}

void ASocketActor::CF_ReceiveData(TArray<uint8> buffer, int32 size)
{
}



void ASocketActor::CF_CreateSocket(FString Ip, int32 Port, int32 BufferSize)
{
	_ip=Ip;
	_port = Port;
	_buffer_size = BufferSize;
	
	_socket = new SocketManager(Ip,Port,BufferSize,this);
	if (_socket)
	{
		_runnable = FRunnableThread::Create(_socket,TEXT("SOCKETTHREADNAME"));
	}
}

void ASocketActor::CF_CloseSocket()
{
	if(_runnable){
		_runnable->Kill();
	}
	delete _socket;
	_runnable = nullptr;
	_socket = nullptr;
}

void ASocketActor::CF_GetThreadInfo(FString& Name, uint32& ID)
{
	if (_runnable)
	{
		Name = _runnable->GetThreadName();
		ID = _runnable->GetThreadID();
	}
	else
	{
		Name = TEXT("Error");
		ID = 0;
	}
}

