#include "TutorialCutIn.h"
#include"../../Graphic/Sprite.h"
#include"../../Define.h"
#include"../../Math/Easing.h"
#include"../../UI/CutInText.h"

void TutorialCutIn::draw(SPRITE_ID id, float yPos, float time, float stopTime, float inTime, float outTime)
{

	Vector2 size = Sprite::GetInstance().GetSize(id);
	float xHalf = size.x*0.5f;

	float alpha = 1.0f;
	//入り
	if (inTime >= time) {
		alpha = Easing::EaseInCubic(time, 0.0f, 1.0f, inTime);

		//左->右
		Vector2 sPos{ Easing::EaseInCubic(time,-size.x ,WINDOW_WIDTH*0.5f + xHalf,inTime),yPos };
		//右->左
		Vector2 ePos{ Easing::EaseInCubic(time,WINDOW_WIDTH , -WINDOW_WIDTH*0.5f - xHalf,inTime),yPos };
		if (id == SPRITE_ID::RANK_PLAYER_SPRITE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)MathHelper::Clamp(alpha*255.0f, 0.0f, 255.0f));
			CutInText::Draw(sPos);
			CutInText::Draw(ePos);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			Sprite::GetInstance().Draw(id, sPos, alpha);
			Sprite::GetInstance().Draw(id, ePos, alpha);
		}
	}
	//終わり
	else if(time>=inTime+stopTime){
		alpha = Easing::EaseOutCubic(time - inTime - stopTime, 1.0f, -1.0f, outTime);
	
		//左->右
		Vector2 sPos{ Easing::EaseInCubic(time - inTime - stopTime,WINDOW_WIDTH*0.5f - xHalf ,WINDOW_WIDTH*0.5f + xHalf,outTime),yPos };

		//右->左
		Vector2 ePos{ Easing::EaseInCubic(time - inTime - stopTime,WINDOW_WIDTH*0.5f - xHalf , -WINDOW_WIDTH*0.5f - xHalf,outTime),yPos };
		if (id == SPRITE_ID::RANK_PLAYER_SPRITE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)MathHelper::Clamp(alpha*255.0f, 0.0f, 255.0f));
			CutInText::Draw(sPos);
			CutInText::Draw(ePos);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			Sprite::GetInstance().Draw(id, sPos, alpha);
			Sprite::GetInstance().Draw(id, ePos, alpha);
		}
	}
	//停止
	else {
		if (id == SPRITE_ID::RANK_PLAYER_SPRITE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)MathHelper::Clamp(alpha*255.0f, 0.0f, 255.0f));
			CutInText::Draw(Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos });
			CutInText::Draw(Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos });
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			Sprite::GetInstance().Draw(id, Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos }, alpha);
			Sprite::GetInstance().Draw(id, Vector2{ WINDOW_WIDTH*0.5f - xHalf,yPos }, alpha);
		}
	}
}
