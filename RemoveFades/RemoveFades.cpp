#include "pch.h"
#include "RemoveFades.h"


BAKKESMOD_PLUGIN(RemoveFades, "Remove Fades", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void RemoveFades::onLoad()
{
	_globalCvarManager = cvarManager;

	removeFades_DuringReplays = std::make_shared<bool>();
	cvarManager->registerCvar("removefades_during_replays", "1", "Remove fades during replays", true, true, 0, true, 1).bindTo(removeFades_DuringReplays);

	gameWrapper->HookEvent("Function GameEvent_Soccar_TA.ReplayPlayback.BeginState", std::bind(&RemoveFades::OnReplayStart, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function GameEvent_Soccar_TA.ReplayPlayback.EndState", std::bind(&RemoveFades::OnReplayEnd, this, std::placeholders::_1));

	gameWrapper->HookEventWithCaller<ActorWrapper>("Function ProjectX.Camera_X.SetCameraFade",
		[this](ActorWrapper caller, void* params, std::string eventname) {

			if (*removeFades_DuringReplays)
			{
				if (removeFades)
					*reinterpret_cast<ACamera_X_execSetCameraFade_Params*>(params) = ACamera_X_execSetCameraFade_Params();
			}
		});

	//DEBUG
	/*cvarManager->registerNotifier("score_goal", [&](std::vector<std::string> args) {

		ServerWrapper server = gameWrapper->GetCurrentGameState();
		if (!server) return;

		BallWrapper ball = server.GetBall();
		if (!ball) return;

		ball.SetLocation(Vector(0.f, 5500.f, 50.f));
		}, "", 0);*/
}

void RemoveFades::OnReplayStart(std::string eventName)
{
	//Set timeout to not remove the fade when transitioning to the replay
	gameWrapper->SetTimeout([this](GameWrapper* gw) {
		removeFades = true;
		}, 0.1f);
}

void RemoveFades::OnReplayEnd(std::string eventName)
{
	//Not setting timeout to not remove the fade when transitioning back to the game
	removeFades = false;
}
