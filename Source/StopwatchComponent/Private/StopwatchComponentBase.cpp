// Fill out your copyright notice in the Description page of Project Settings.


#include "StopwatchComponentBase.h"

// Sets default values for this component's properties
UStopwatchComponentBase::UStopwatchComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStopwatchComponentBase::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineEvent EventTrackOnFinished;
	EventTrackOnFinished.BindUFunction(this, FName("OnTimelineFinished"));
	Timeline.AddEvent(1.0, EventTrackOnFinished);

	FOnTimelineEvent EventTrackOnStart;
	EventTrackOnStart.BindUFunction(this, FName("OnTimelineStarted"));
	Timeline.AddEvent(0.0, EventTrackOnStart);

	Timeline.SetPropertySetObject(this);
	Timeline.SetDirectionPropertyName(FName("TimelineDirection"));

	if (CurveFloat) {
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("OutputCurveFloatValue"));
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress, "test", "TimelineProgress");
	}
	else {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Error : CurveFloat Invalid")));
	}
}


// Called every frame
void UStopwatchComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Timeline.TickTimeline(DeltaTime);
}

void UStopwatchComponentBase::PlayTimelineFromStart(float duration)
{
	if (duration <= 0) {
		TimelineDirection = ETimelineDirection::Forward;
		OnTimelineFinished();
	}
	else {
		playrate = 1.0 / duration;
		Timeline.SetPlayRate(playrate);
		Timeline.PlayFromStart();
	}
}

void UStopwatchComponentBase::PlayTimeline(float duration)
{
	if (duration <= 0) {
		TimelineDirection = ETimelineDirection::Forward;
		OnTimelineFinished();
	}
	else {
		playrate = 1.0 / duration;
		Timeline.SetPlayRate(playrate);
		Timeline.Play();
	}
}

void UStopwatchComponentBase::PlayTimelineFromPosition(float duration, float position)
{
	Timeline.SetPlaybackPosition(position, true, true);
	PlayTimeline(duration);
}

void UStopwatchComponentBase::ReverseTimelineFromEnd(float duration)
{
	if (duration <= 0) {
		TimelineDirection = ETimelineDirection::Backward;
		OnTimelineStarted();
	}
	else {
		playrate = 1.0 / duration;
		Timeline.SetPlayRate(playrate);
		Timeline.ReverseFromEnd();
	}
}

void UStopwatchComponentBase::ReverseTimeline(float duration)
{
	if (duration <= 0) {
		TimelineDirection = ETimelineDirection::Backward;
		OnTimelineStarted();
	}
	else {
		playrate = 1.0 / duration;
		Timeline.SetPlayRate(playrate);
		Timeline.Reverse();
	}
}

void UStopwatchComponentBase::ReverseTimelineFromPosition(float duration, float position)
{
	Timeline.SetPlaybackPosition(position, true, true);
	ReverseTimeline(duration);
}

void UStopwatchComponentBase::PlaySpecificPosition(float position)
{
	StopTimeline();
	Timeline.SetPlaybackPosition(position, true, true);
}

void UStopwatchComponentBase::StopTimeline()
{
	if (Timeline.IsPlaying()) {
		Timeline.Stop();
	}
}

float UStopwatchComponentBase::GetPlayBackPosition()
{
	return Timeline.GetPlaybackPosition();
}

void UStopwatchComponentBase::SetFloatCurve(UCurveFloat* NewCurveFloat)
{
	if (NewCurveFloat != nullptr)
		Timeline.SetFloatCurve(NewCurveFloat, FName("TimelineProgress"));
}

void UStopwatchComponentBase::SetTimelineLooping(bool NewLooping)
{
	Timeline.SetLooping(NewLooping);
}

bool UStopwatchComponentBase::GetTimelineLooping()
{
	return Timeline.IsLooping();
}

bool UStopwatchComponentBase::GetTimelinePlaying()
{
	return Timeline.IsPlaying();
}

bool UStopwatchComponentBase::GetTimelineReversing()
{
	return Timeline.IsReversing();
}

float UStopwatchComponentBase::GetPlayRate()
{
	return Timeline.GetPlayRate();
}

void UStopwatchComponentBase::SetPlayRate(float NewPlayRate)
{
	Timeline.SetPlayRate(NewPlayRate);
}

void UStopwatchComponentBase::OnTimelineStarted_Implementation()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Timeline Started")));
}

void UStopwatchComponentBase::OnTimelineFinished_Implementation()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Timeline Finished")));
}

void UStopwatchComponentBase::OutputCurveFloatValue_Implementation(float Value)
{
	FString TheFloatStr = FString::SanitizeFloat(Value);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TheFloatStr);

	//if (Timeline.GetTimelineDirectionEnum.Equal(ETimelineDirection::Forward)) {

	//}
}