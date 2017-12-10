#pragma once
#include"Player.h"

class TutorialScene;
class TutorialPlayer :public Player {
public:
	TutorialPlayer(IWorld* world, const std::string& name, const Vector3& position,TutorialScene* tutorial);

	~TutorialPlayer();

	void onUpdate(float deltaTime)override;

	void hitPoint();
private:
	virtual bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blend = 1.0f);

	virtual void to_MoveMode()override;
	virtual void end_StepSuccessMode()override;
private:
	TutorialScene* tutorial_;

	int hitCount_;
};