#include "TutorialCutIn.h"
#include"../../Graphic/Sprite.h"
#include"../../Define.h"
#include"../../Math/Easing.h"

void TutorialCutIn::draw(SPRITE_ID id, float yPos, float time, float stopTime, float inTime, float outTime)
{

	Vector2 size = Sprite::GetInstance().GetSize(id);
	float xHalf = size.x*0.5f;

	float alpha = 1.0f;
	//����
	if (inTime >= time) {
		alpha = Easing::EaseInCubic(time,0.0f,1.0f, inTime);
	
		//��->�E
		Vector2 sPos{ Easing::EaseInCubic(time,-size.x ,WINDOW_WIDTH*0.5f + xHalf,inTime),yPos };
		Sprite::GetInstance().Draw(id, sPos, alpha);
		//�E->��
		Vector2 ePos{ Easing::EaseInCubic(time,WINDOW_WIDTH , -WINDOW_WIDTH*0.5f - xHalf,inTime),yPos };
		Sprite::GetInstance().Draw(id, ePos, alpha);
	}
	//�I���
	else if(time>=inTime+stopTime){
		alpha = Easing::EaseOutCubic(time - inTime - stopTime, 1.0f, -1.0f, outTime);
	
		//��->�E
		Vector2 sPos{ Easing::EaseInCubic(time - inTime - stopTime,WINDOW_WIDTH*0.5f - xHalf ,WINDOW_WIDTH*0.5f + xHalf,outTime),yPos };
		Sprite::GetInstance().Draw(id, sPos, alpha);
		//�E->��
		Vector2 ePos{ Easing::EaseInCubic(time - inTime - stopTime,WINDOW_WIDTH*0.5f - xHalf , -WINDOW_WIDTH*0.5f - xHalf,outTime),yPos };
		Sprite::GetInstance().Draw(id, ePos, alpha);

	}
	//��~
	else {
		Sprite::GetInstance().Draw(id, Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos }, alpha);
		Sprite::GetInstance().Draw(id, Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos }, alpha);
	}
}
