// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class XmasGiftDeliveryEditorTarget : TargetRules
{
	public XmasGiftDeliveryEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "XmasGiftDelivery" } );
	}
}
