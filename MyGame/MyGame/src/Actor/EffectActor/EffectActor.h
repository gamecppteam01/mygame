#pragma once
#include"../Actor.h"

class Effect;

class EffectActor :public Actor {
public:
	//Actor�ɕK�v�Ȉ�����Ⴄ
	EffectActor(IWorld* world, const std::string& name, const Vector3& position, std::shared_ptr<Effect> effect);
	virtual ~EffectActor(){}
protected:
	// �X�V����
	virtual void onUpdate(float deltaTime);
	// �`�揈��
	virtual void onDraw() const;

private:
	//�K�v�ɉ����Ĉ�����ǉ�
	std::shared_ptr<Effect> effect_;
};