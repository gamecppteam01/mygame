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
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 7; i++) {
			switch (Random::GetInstance().Range(1,6))
			{
			case 1:
				num_[i][j] = Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1);
				break;
			case 2:
				num_[i][j] = Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2);
				break;
			case 3:
				num_[i][j] = Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN3);
				break;
			case 4:
				num_[i][j] = Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1);
				break;
			case 5:
				num_[i][j] = Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN2);
				break;
			case 6:
				num_[i][j] = Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN3);
				break;
			default:
				break;
			}

		}
	}
}

void Audience::update(float deltaTime){
	timer += deltaTime;
	if (timer > 1.0f) {
		count++;
	}
}

void Audience::draw(const Vector3& position, const Vector3& rotation, const int& num) const{
	switch (num)
	{
	case 1:
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 200 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, num_[i+1][j+3], 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 42 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, num_[i+1][j+2], 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x + 110 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, num_[i+3][j], 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		break;
	case 2:
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, num_[i][j], 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, num_[i+2][j+2], 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		break;
	case 3:
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, num_[i+1][j+3], 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, num_[i+2][j+3], 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
			}
		}
		break;
	default:
		break;
	}
}

