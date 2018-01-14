#include "Audience.h"
#include "../Graphic/Sprite.h"
#include"../Graphic/DxlibGraphic.h"
#include"../Graphic/Model.h"
#include"../Math/Random.h"
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
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 200 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 42 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x + 110 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		break;
	case 2:
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 0  - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		break;
	case 3:
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 0 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		break;
	default:
		break;
	}
}

