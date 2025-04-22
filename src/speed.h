#pragma once

#include <string>

#include "sdk/inc/natives.h"

float getPedVehicleSpeedMps(const Ped& ped);
std::string formatSpeed(const std::string& format, float mps);
bool validateFormat(const std::string &format);
