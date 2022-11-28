// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketExample.h"

void ASocketExample::CF_ReceiveData(TArray<uint8> buffer, int32 size)
{
	// call this function to let the code run in game thread;
	// CF_HandleFunction();

	
	UE_LOG(LogTemp,Warning,TEXT("[SocketExample][receive {%d} data ]"),size);

	/** @LOG {2022/11/28-16:59} cant call here , will crash ... */
	// Assertion failed: IsInGameThread() || HasAnyFlags(RF_ClassDefaultObject|RF_ArchetypeObject) || IsPostLoadThreadSafe() || IsA(UClass::StaticClass())
	{
		// if (SpawnActorClass && SpawnActorList.Num() < 100)
		// {
		// 	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass,CF_GetRandomVector(500.f),CF_GetRandomRotator());
		// 	if (SpawnedActor)
		// 	{
		// 		SpawnActorList.Add(SpawnedActor);
		// 	}
		// }
	}


	/** @LOG {2022/11/28-17:01} try call in function */
	// CF_TrySpawnInFunction();

	/** @LOG {2022/11/28-17:03} try spawn in u function */
	// CF_TrySpawnInUFUNCTION();

	/** @LOG {2022/11/28-17:06} try call in game thread */
	CF_TryCallInGameThread();
}

void ASocketExample::CF_HandleFunction()
{
	// you can do any handle in there for game thread;
	UE_LOG(LogTemp,Warning,TEXT("[SocketExample][%d]"),CF_GetPort());
}

FVector ASocketExample::CF_GetRandomVector(float Radius)
{
	return GetActorLocation() + FVector(FMath::RandRange(0.f,Radius),FMath::RandRange(0.f,Radius),FMath::RandRange(0.f,Radius));
}

FRotator ASocketExample::CF_GetRandomRotator()
{
	return FRotator(FMath::RandRange(0.f,360.f),FMath::RandRange(0.f,360.f),FMath::RandRange(0.f,360.f));
}

void ASocketExample::CF_TrySpawnInFunction()
{
	if (SpawnActorClass && SpawnActorList.Num() < 100)
	{
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass,CF_GetRandomVector(500.f),CF_GetRandomRotator());
		if (SpawnedActor)
		{
			SpawnActorList.Add(SpawnedActor);
		}
	}
}

void ASocketExample::CF_TrySpawnInUFUNCTION()
{
	if (SpawnActorClass && SpawnActorList.Num() < 100)
	{
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass,CF_GetRandomVector(500.f),CF_GetRandomRotator());
		if (SpawnedActor)
		{
			SpawnActorList.Add(SpawnedActor);
		}
	}
}

void ASocketExample::CF_TryCallInGameThread()
{
	AsyncTask(ENamedThreads::GameThread,[this]()
	{
		if (SpawnActorClass && SpawnActorList.Num() < SpawnNum)
		{
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass,CF_GetRandomVector(SpawnRadius),CF_GetRandomRotator());
			if (SpawnedActor)
			{
				SpawnActorList.Add(SpawnedActor);
			}
		}
	});
}
