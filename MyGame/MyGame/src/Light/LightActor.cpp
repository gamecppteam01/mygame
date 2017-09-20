#include "LightActor.h"
#include "../Graphic/Light.h"

LightActor::LightActor(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body)
:Actor(world,name,position,body){
	
	Light::GetInstance().SetDirectionalLight("Light", position_);
	Light::GetInstance().SetPosition("Light", position_);
}

void LightActor::onMessage(EventMessage message, void * param)
{
}

void LightActor::onUpdate(float deltaTime){
}

void LightActor::onDraw() const{
	//Light::GetInstance().SetAmbientColor("Light", Color(0.2f, 0.2f, 0.2f, 1.0f));
	Light::GetInstance().SetDiffuseColor("Light", Color(0.5f, 0.5f, 0.5f, 1.0f));
	//Light::GetInstance().SetSpecularColor("Light", Color(0.5f, 0.5f, 0.5f, 1.0f));
	Light::GetInstance().LightEnable("Light", true);
	Light::GetInstance().UseLighting(true); 
	Light::GetInstance().UseStandardLight(true);
}

void LightActor::onCollide(Actor & other){
}
