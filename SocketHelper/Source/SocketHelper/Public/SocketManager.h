// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class SOCKETHELPER_API SocketManager : public FRunnable
{
public:
	
	/** @LOG [interface] */
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	
	
	/** @LOG [socket data] */
	SocketManager(FString InIp,int32 InPort,int32 InBufferSize,class ASocketActor * InObj);
	FString _ip;
	int32 _port;
	int32 _buffer_size;
	ASocketActor * _obj = nullptr;

	
private:
	bool bRunning = false;
	FSocket * _socket = nullptr;
};
