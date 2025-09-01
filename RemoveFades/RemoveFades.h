#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

struct FColor
{
	uint8_t B;
	uint8_t G;
	uint8_t R;
	uint8_t A;
};

struct FVector2D
{
	float X;
	float Y;
};

struct ACamera_X_execSetCameraFade_Params
{
	bool bNewEnableFading : 1;
	FColor NewFadeColor;
	FVector2D NewFadeAlpha;
	float NewFadeTime;
	bool bNewFadeAudio : 1;
};

class RemoveFades: public BakkesMod::Plugin::BakkesModPlugin
	,public SettingsWindowBase // Uncomment if you wanna render your own tab in the settings menu
	//,public PluginWindowBase // Uncomment if you want to render your own plugin window
{
	//Boilerplate
	void onLoad() override;
	//void onUnload() override; // Uncomment and implement if you need a unload method

	void OnReplayStart(std::string eventName);
	void OnReplayEnd(std::string eventName);

	std::shared_ptr<bool> removeFades_DuringReplays;
	bool removeFades = false;

public:
	void RenderSettings() override; // Uncomment if you wanna render your own tab in the settings menu
	//void RenderWindow() override; // Uncomment if you want to render your own plugin window
};
