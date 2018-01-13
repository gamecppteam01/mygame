#include "Audience.h"
#include "../Graphic/Sprite.h"
#include"../Graphic/DxlibGraphic.h"
#include"../Graphic/Model.h"
float radian(float degree) {
	return degree / 180.0f*DX_PI_F;
}
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

void Audience::draw(const Vector3& position, const Vector3& rotation, const int& num) const{
	switch (num)
	{
	case 1:
		switch (count)
		{
		case 1:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x - 120 + 40 * i,position.y,position.z }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 2:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x - 120 + 40 * i,position.y,position.z }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 3:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x - 120 + 40 * i,position.y,position.z }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE3), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 4:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x - 120 + 40 * i,position.y,position.z }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE4), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (count)
		{
		case 1:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x ,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 2:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 3:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE3), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 4:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE4), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (count)
		{
		case 1:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x ,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 2:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 3:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE3), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		case 4:
			for (int i = 0; i < 7; i++) {
				DrawSprite3D(Vector3{ position.x,position.y,position.z - 120 + 40 * i }, 40.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE4), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
