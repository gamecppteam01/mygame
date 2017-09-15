#pragma once

#include <string>
#include "../../ActorPtr.h"
#include "../../../Math/Math.h"

struct HitInfo
{
public:
	ActorPtr actor;
	std::string name;
	Vector3 intersect;
	Vector3 normal;

public:
	HitInfo() : actor(), name("none"), intersect(Vector3::Zero), normal(Vector3::Zero) {}
};