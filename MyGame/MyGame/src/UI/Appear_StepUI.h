#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../World/IWorld.h"
#include<string>
class Player;
class Appear_StepUI {
private:
	enum StepType {
		None=0,
		Quarter=1,
		Half=2,
		Turn=3,
		Spin=4
	};
public:
	Appear_StepUI() = default;
	Appear_StepUI(IWorld* world,Player* player);
	~Appear_StepUI();
	void SetWorld(IWorld* world);
	void Initialize();
	void Update(float deltaTime);
	void Draw(const Vector3& position)const;

	void Notify(int stepType);
private:
	IWorld* world_{ nullptr };
	//nullptrなので注意する
	Player* player_{ nullptr };

	int stepDrawType_{ -1 };//表示するステップの種類
};