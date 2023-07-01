#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include <random>
#pragma comment(lib, "pluginsdk.lib")

class RandomPresetPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
public:
	RandomPresetPlugin();
	virtual void onLoad();
	virtual void onUnload();

	void onMatchEnded(std::string name);

private:
	void log(std::string message);
	int getRandomInt(int upperBound);

	std::mt19937 rng;
};