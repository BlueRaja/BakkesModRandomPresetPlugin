#include "pch.h"
#include "RandomPresetPlugin.h"


BAKKESMOD_PLUGIN(RandomPresetPlugin, "Random Preset Plugin", "1.0", PERMISSION_ALL);

RandomPresetPlugin::RandomPresetPlugin()
{
	std::random_device dev;
	rng.seed(dev());
}

void RandomPresetPlugin::onLoad()
{
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", std::bind(&RandomPresetPlugin::onMatchEnded, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GFxShell_TA.LeaveMatch", std::bind(&RandomPresetPlugin::onMatchEnded, this, std::placeholders::_1));
}

void RandomPresetPlugin::onUnload()
{
}

void RandomPresetPlugin::onMatchEnded(std::string name)
{
	auto userLoadoutSave = gameWrapper->GetUserLoadoutSave();
	auto presets = userLoadoutSave.GetPresets();
	if (presets.Count() > 1)
	{
		auto equippedLoadout = userLoadoutSave.GetEquippedLoadout();
		auto nextPreset = equippedLoadout;
		while (nextPreset.memory_address == equippedLoadout.memory_address)
		{
			nextPreset = presets.Get(getRandomInt(presets.Count()));
		}
		userLoadoutSave.EquipPreset(nextPreset);
		cvarManager->log("Updating preset to " + nextPreset.GetName());
	}
}

int RandomPresetPlugin::getRandomInt(int upperBound)
{
	std::uniform_int_distribution<std::mt19937::result_type> distribution(0, upperBound - 1);
	return distribution(rng);
}