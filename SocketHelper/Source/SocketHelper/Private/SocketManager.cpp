// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketManager.h"

#include "SocketActor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"



#define LOG_INFO(Info) if (_obj)\
		{\
			_obj->OnReceiveInfo(Info);\
		}

bool SocketManager::Init()
{
	_socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("SOCKETHELPERINFO"));

	if (!_socket)
	{
		LOG_INFO(TEXT("Socket Init Failed"))
		return false;
	}

	bool bSetSuccess;
	_ip_address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	_ip_address->SetIp(*_ip,bSetSuccess);
	_ip_address->SetPort(_port);

	if (!bSetSuccess)
	{
		LOG_INFO(TEXT("Socket Port Set Failed"))
		return false;
	}

	// connect
	bool ret = _socket->Connect(*_ip_address.Get());
	if (!ret)
	{
		LOG_INFO(TEXT("Socket Connect Failed"))
		return false;
	}

	this->bRunning = true;
	LOG_INFO(TEXT("Socket Connect Success"))
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
			// UE_LOG(LogTemp,Warning,TEXT("[SocketManager][socket recv blocking]"));
			bool ret = _socket->Recv(buffer.GetData(),_buffer_size,real_data_size);
			// _socket->SetNonBlocking(false);
			
			if (ret)
			{
				_obj->OnReceiveData(buffer,real_data_size);	
			}
			else
			{
				LOG_INFO(TEXT("Socket Connect Break , Try Reconnect after 2s"))
				if (!bRunning)
				{
					LOG_INFO(TEXT("Socket Exec Finish"))
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
					if (_socket->Connect(*_ip_address.Get()))
					{
						LOG_INFO(TEXT("Socket Reconnect Success"))	
					}
				}
			}
			
		}
	}	
	return 0;
}

void SocketManager::Stop()
{
	LOG_INFO(TEXT("Socket Stop Exec"))
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
	LOG_INFO(TEXT("Socket Exit"))
}



SocketManager::SocketManager(FString InIp, int32 InPort, int32 InBufferSize, ASocketActor* InObj)
{
	_ip=InIp;
	_port = InPort;
	_buffer_size = InBufferSize;
	_obj = InObj;
}


