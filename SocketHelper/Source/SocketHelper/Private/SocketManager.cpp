// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketManager.h"

#include "SocketActor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

TSharedRef<FInternetAddr> G_IPAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();



bool SocketManager::Init()
{
	_socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("SOCKETHELPERINFO"));

	if (!_socket)
	{
		UE_LOG(LogTemp,Warning,TEXT("[SocketManager][socket create failed, retry in 1s...]"));
		return false;
	}

	bool bSetSuccess;
	G_IPAddress->SetIp(*_ip,bSetSuccess);
	G_IPAddress->SetPort(_port);

	if (!bSetSuccess)
	{
		UE_LOG(LogTemp,Warning,TEXT("[SocketManager][Set IP and Port Failed]"));
		return false;
	}

	// connect
	bool ret = _socket->Connect(G_IPAddress.Get());
	if (!ret)
	{
		UE_LOG(LogTemp,Warning,TEXT("[SocketManager][socket connect failed]"));
		return false;
	}

	this->bRunning = true;
	UE_LOG(LogTemp,Warning,TEXT("[SocketManager][Socket Connect Success]"));
	return true;
}

uint32 SocketManager::Run()
{
	while (bRunning)
	{
		if (_socket)
		{
			TArray<uint8> buffer;
			buffer.Init(0,_buffer_size);
			int32 real_data_size;
			
			// _socket->SetNonBlocking();
			UE_LOG(LogTemp,Warning,TEXT("[SocketManager][socket recv blocking]"));
			bool ret = _socket->Recv(buffer.GetData(),_buffer_size,real_data_size);
			// _socket->SetNonBlocking(false);
			
			if (ret)
			{
				_obj->CF_ReceiveData(buffer,real_data_size);	
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("[SocketManager][connect break , try re connect]"));
				if (!bRunning)
				{
					break;
				}
				FPlatformProcess::Sleep(2.f);
				if (_socket)
				{
					ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(_socket);
				}
				_socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("SOCKETHELPERINFO"));
				if (_socket)
				{
					if (_socket->Connect(G_IPAddress.Get()))
					{
						UE_LOG(LogTemp,Warning,TEXT("[SocketManager][socket reconnect success]"));	
					}
				}
			}
			
		}
		FPlatformProcess::Sleep(0.02f);
	}	
	return 0;
}

void SocketManager::Stop()
{
	UE_LOG(LogTemp,Warning,TEXT("[SocketManager][socket managet stop]"));
	bRunning = false;
	if (_socket)
	{
		_socket->Close();
		delete _socket;
		_socket = nullptr;
	}
}

void SocketManager::Exit()
{
	UE_LOG(LogTemp,Warning,TEXT("[SocketManager][socket manager exit]"));
}



SocketManager::SocketManager(FString InIp, int32 InPort, int32 InBufferSize, ASocketActor* InObj)
{
	_ip=InIp;
	_port = InPort;
	_buffer_size = InBufferSize;
	_obj = InObj;
}


