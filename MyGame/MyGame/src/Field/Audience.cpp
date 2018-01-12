#include "Audience.h"
#include "../Graphic/Sprite.h"
#include"../Graphic/DxlibGraphic.h"
Audience::Audience(){
}

void Audience::initialize(){
	timer = 0.0f;
	count = 1;
}

void Audience::update(float deltaTime){
	timer += deltaTime;
	if (timer > 1.0f) {
		timer = 0.0f;
		count++;
	}
	if (count >= 4) {
		count = 1;
	}
	
}

void Audience::draw(const Vector3& position, const Vector3& rotation) const{
	switch (count)
	{
	case 1:
		DrawSprite3D(Vector3{ position.x - 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		DrawSprite3D(Vector3{ position.x + 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		break;
	case 2:
		DrawSprite3D(Vector3{ position.x - 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		DrawSprite3D(Vector3{ position.x + 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		break;
	case 3:
		DrawSprite3D(Vector3{ position.x - 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE3), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		DrawSprite3D(Vector3{ position.x + 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE3), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		break;
	case 4:
		DrawSprite3D(Vector3{ position.x - 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE4), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		DrawSprite3D(Vector3{ position.x + 100,position.y,position.z }, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE4), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
		break;
	default:
		break;
	}
}
