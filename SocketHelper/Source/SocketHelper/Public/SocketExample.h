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
};
