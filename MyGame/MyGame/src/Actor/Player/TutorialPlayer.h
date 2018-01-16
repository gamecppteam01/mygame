#pragma once
#include"Player.h"

class TutorialScene;
class TutorialPlayer :public Player {
public:
	TutorialPlayer(IWorld* world, const std::string& name, const Vector3& position,TutorialScene* tutorial);
	void onUpdate(float deltaTime)override;

	void hitPoint();
	//テキスト描画が終了したら呼ばれる
	void textEnd(int lessonNum);

	void resetCombo();

	void setCheckType(ComboChecker::ComboType type);
private:
	virtual bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blend = 1.0f);

	virtual void idle_Update(float deltaTime)override;
	virtual void to_MoveMode()override;
	virtual void end_StepSuccessMode()override;
	virtual void end_AttackMode()override;
	virtual void end_ShootMode()override;
private:
	TutorialScene* tutorial_;

	int hitCount_;

	bool isAlreadyInLight_;//ライトの中に入ったことがあるか
};