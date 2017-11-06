#pragma once
#include<string>
#include"../Math/Math.h"

struct LightColor {
	LightColor(Color amb, Color diff, Color spec) :ambient(amb), diffuse(diff), specular(spec) {

	}
	Color ambient;
	Color diffuse;
	Color specular;
};
struct DirectionalLight {
	std::string handlename;
	Vector3 vector;
	LightColor color;
	DirectionalLight(const std::string& name, const Vector3& vector, LightColor col) :handlename(name), vector(vector),color(col) {}
};
struct SpotLight {
	std::string handlename;
	Vector3 position;
	Vector3 vector;
	float cone_outangle;
	float cone_inangle;
	float range;
	LightColor color;
	SpotLight(const std::string& name, const Vector3& position, const Vector3& vector, float outangle, float inangle, float range,LightColor col) :
		handlename(name),position(position),vector(vector),cone_outangle(outangle),cone_inangle(inangle),range(range),color(col){}
};
struct PointLight {
	std::string handlename;
	Vector3 position;
	float range;
	LightColor color;
	PointLight(const std::string& name, const Vector3& position, float range, LightColor col) :
		handlename(name),position(position),range(range),color(col){}
};
