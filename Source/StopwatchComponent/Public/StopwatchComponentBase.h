// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "StopwatchComponentBase.generated.h"


UCLASS(Blueprintable)
class STOPWATCHCOMPONENT_API UStopwatchComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStopwatchComponentBase();

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void PlayTimelineFromStart(float duration);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void PlayTimeline(float duration);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void PlayTimelineFromPosition(float duration, float position);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void ReverseTimelineFromEnd(float duration);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void ReverseTimeline(float duration);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void ReverseTimelineFromPosition(float duration, float position);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void PlaySpecificPosition(float position);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void StopTimeline();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TimelineActorComp")
		float GetPlayBackPosition();

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void SetFloatCurve(UCurveFloat* NewCurveFloat);

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void SetTimelineLooping(bool NewLooping);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TimelineActorComp")
		bool GetTimelineLooping();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TimelineActorComp")
		bool GetTimelinePlaying();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TimelineActorComp")
		bool GetTimelineReversing();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TimelineActorComp")
		float GetPlayRate();

	UFUNCTION(BlueprintCallable, Category = "TimelineActorComp")
		void SetPlayRate(float NewPlayRate);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TimelineActorComp")
		void OnTimelineStarted();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TimelineActorComp")
		void OnTimelineFinished();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TimelinenActorComp")
		void OutputCurveFloatValue(float Value);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimeline Timeline;

	UPROPERTY()
		float playrate;

	UPROPERTY()
		float test;

	UPROPERTY(EditAnywhere, Category = "TimelineActorComp")
		UCurveFloat* CurveFloat;

	UPROPERTY(BlueprintReadOnly, Category = "TimelineActorComp")
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
