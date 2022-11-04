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

// Called every frame
void ASocketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASocketActor::CF_ReceiveData(TArray<uint8> buffer, int32 size)
{
	const char * data = reinterpret_cast<const char *>(buffer.GetData());
	UE_LOG(LogTemp,Warning,TEXT("[SocketActor][receive %d data]"),size);
	if (data)
	{
		UE_LOG(LogTemp,Warning,TEXT("[SocketActor][%s]"),*FString(ANSI_TO_TCHAR(data)));
	}
}



void ASocketActor::CF_CreateSocket(FString Ip, int32 Port, int32 BufferSize)
{
	_socket = new SocketManager(Ip,Port,BufferSize,this);
	if (_socket)
	{
		_runnable = FRunnableThread::Create(_socket,TEXT("SOCKETTHREADNAME"));
	}
}

void ASocketActor::CF_CloseSocket()
{
	_runnable->Kill();
	delete _socket;
	_runnable = nullptr;
	_socket = nullptr;
}

