#include "pch.h"
#include "RemoveFades.h"


void RemoveFades::RenderSettings()
{
	if (ImGui::Checkbox("Remove Fades During Replays", removeFades_DuringReplays.get()))
	{
		cvarManager->getCvar("removefades_during_replays").setValue(*removeFades_DuringReplays);
	}
}