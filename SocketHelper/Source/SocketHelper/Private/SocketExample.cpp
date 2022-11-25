// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketExample.h"

void ASocketExample::CF_ReceiveData(TArray<uint8> buffer, int32 size)
{
	UE_LOG(LogTemp,Warning,TEXT("[SocketExample][%d][receive data size = {%d}]"),CF_GetPort(),size);
}
