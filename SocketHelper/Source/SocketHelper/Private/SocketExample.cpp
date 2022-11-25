// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketExample.h"

void ASocketExample::CF_ReceiveData(TArray<uint8> buffer, int32 size)
{
	// call this function to let the code run in game thread;
	CF_HandleFunction();
}

void ASocketExample::CF_HandleFunction()
{
	// you can do any handle in there for game thread;
	UE_LOG(LogTemp,Warning,TEXT("[SocketExample][%d][receive data size = {%d}]"),CF_GetPort(),size);
}
