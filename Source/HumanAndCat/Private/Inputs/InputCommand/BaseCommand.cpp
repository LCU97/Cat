// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/InputCommand/BaseCommand.h"

UBaseCommand::UBaseCommand()
{
	
}

void UBaseCommand::ActionExecute_Implementation(const UInputBufferingObject* BufferingObject)
{
	IInterface_InputCommand::ActionExecute_Implementation(BufferingObject);
}
