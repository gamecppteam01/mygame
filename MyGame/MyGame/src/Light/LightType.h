#pragma once
#include<string>
#include"../Math/Math.h"

struct DirectionalLight {
	std::string handlename;
	Vector3 vector;
	DirectionalLight(const std::string& name,const Vector3& vector):handlename(name),vector(vector){}
};
struct SpotLight {
	std::string handlename;
	Vector3 position;
	Vector3 vector;
	float cone_outangle;
	float cone_inangle;
	float range;
	SpotLight(const std::string& name, const Vector3& position,const Vector3& vector,float outangle,float inangle,float range):
		handlename(name),position(position),vector(vector),cone_outangle(outangle),cone_inangle(inangle),range(range){}
};
struct PointLight {
	std::string handlename;
	Vector3 position;
	float range;
	PointLight(const std::string& name, const Vector3& position, float range):
		handlename(name),position(position),range(range){}
};
