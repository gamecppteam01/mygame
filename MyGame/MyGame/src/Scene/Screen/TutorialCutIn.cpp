#include "TutorialCutIn.h"
#include"../../Graphic/Sprite.h"
#include"../../Define.h"
#include"../../Math/Easing.h"

void TutorialCutIn::draw(SPRITE_ID id, float yPos, float time, float stopTime, float inTime, float outTime)
{

	Vector2 size = Sprite::GetInstance().GetSize(id);
	float xHalf = size.x*0.5f;

	float alpha = 1.0f;
	//入り
	if (inTime >= time) {
		alpha = Easing::EaseInCubic(time,0.0f,1.0f, inTime);
	
		//左->右
		Vector2 sPos{ Easing::EaseInCubic(time,-size.x ,WINDOW_WIDTH*0.5f + xHalf,inTime),yPos };
		Sprite::GetInstance().Draw(id, sPos, alpha);
		//右->左
		Vector2 ePos{ Easing::EaseInCubic(time,WINDOW_WIDTH , -WINDOW_WIDTH*0.5f - xHalf,inTime),yPos };
		Sprite::GetInstance().Draw(id, ePos, alpha);
	}
	//終わり
	else if(time>=inTime+stopTime){
		alpha = Easing::EaseOutCubic(time - inTime - stopTime, 1.0f, -1.0f, outTime);
	
		//左->右
		Vector2 sPos{ Easing::EaseInCubic(time - inTime - stopTime,WINDOW_WIDTH*0.5f - xHalf ,WINDOW_WIDTH*0.5f + xHalf,outTime),yPos };
		Sprite::GetInstance().Draw(id, sPos, alpha);
		//右->左
		Vector2 ePos{ Easing::EaseInCubic(time - inTime - stopTime,WINDOW_WIDTH*0.5f - xHalf , -WINDOW_WIDTH*0.5f - xHalf,outTime),yPos };
		Sprite::GetInstance().Draw(id, ePos, alpha);

	}
	//停止
	else {
		Sprite::GetInstance().Draw(id, Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos }, alpha);
		Sprite::GetInstance().Draw(id, Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos }, alpha);
	}
}
