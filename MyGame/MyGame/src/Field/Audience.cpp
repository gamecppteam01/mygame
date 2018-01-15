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
			num_[i][j] = Random::GetInstance().Range(0, 2);
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
				switch (num_[i][j])
				{
				case 0:
					DrawSprite3D(Vector3{ position.x - 200 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 1:
					DrawSprite3D(Vector3{ position.x - 200 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 2:
					DrawSprite3D(Vector3{ position.x - 200 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				default:
					break;
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				switch (num_[i+1][j+1])
				{
				case 0:
					DrawSprite3D(Vector3{ position.x - 42 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 1:
					DrawSprite3D(Vector3{ position.x - 42 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 2:
					DrawSprite3D(Vector3{ position.x - 42 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				default:
					break;
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				switch (num_[i+2][j+2])
				{
				case 0:
					DrawSprite3D(Vector3{ position.x + 110 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 1:
					DrawSprite3D(Vector3{ position.x + 110 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 2:
					DrawSprite3D(Vector3{ position.x + 110 + 50 * i,position.y + 7 * j,position.z + 25 * j }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				default:
					break;
				}
			}
		}
		break;
	case 2:
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				switch (num_[i+3][j+3])
				{
				case 0:
					DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 1:
					DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 2:
					DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				default:
					break;
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				switch (num_[i][j])
				{
				case 0:
					DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 1:
					DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 2:
					DrawSprite3D(Vector3{ position.x - 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				default:
					break;
				}
			}
		}
		break;
	case 3:
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				switch (num_[i][j])
				{
				case 0:
					DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 1:
					DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 2:
					DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 50 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				default:
					break;
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				switch (num_[i+4][j+4])
				{
				case 0:
					DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 1:
					DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_MEN2), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				case 2:
					DrawSprite3D(Vector3{ position.x + 22 * j,position.y + 7 * j,position.z + 200 - 50 * i }, 10.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::AUDIENCE_WOMEN1), 255, 255, 255, 255, rotation.y, rotation.x, rotation.z);
					break;
				default:
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

