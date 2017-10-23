#pragma once
#include"../EffectActor.h"

class TrackingEffectActor :public EffectActor {
public:
	//Actor�ɕK�v�Ȉ�����Ⴄ
	TrackingEffectActor(IWorld* world, const std::string& name, const Vector3& position, std::shared_ptr<Effect> effect,const ActorPtr& target);

private:
	// �X�V����
	virtual void onUpdate(float deltaTime)override;

	//�ǐՊ֐�
	void Tracking();
private:
	ActorPtr target_;
};