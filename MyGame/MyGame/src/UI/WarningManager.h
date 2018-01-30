#pragma once
#include "UI.h"
#include "WarningParamter.h"
#include"../World/IWorld.h"
#include <map>


class Player;

 enum class warningState {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	None,

};

class WarningManager : public UI {
public:
	//�R���X�g���N�^
	explicit WarningManager(IWorld* world);
	//������
	virtual void initialize() override;
	virtual void pause() override;
	virtual void restart() override;
	//�X�V
	virtual void update(float deltaTime) override;
	//�`��
	virtual void draw() const override;

	float warningCount()const;

	void stateChange(const Vector3& v2);
	void stateChange(const Vector2& v2);

	void stateChange(float angle);

private:
	std::map<warningState, WarningParamter> parameters_;
	warningState state_;
	Vector2 pos;
	float sincount;
	int count;
	IWorld* world_;
	std::weak_ptr<Player> player_;

	bool pause_;
};