#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../World/IWorld.h"
#include<string>
class Player;
class Appear_StepUI {
public:
	Appear_StepUI() = default;
	Appear_StepUI(IWorld* world,Player* player);
	~Appear_StepUI();
	void SetWorld(IWorld* world);
	void Initialize();
	void Update(float deltaTime);
	void Draw(const Vector3& position)const;
private:
	IWorld* world_{ nullptr };
	//nullptrÇ»ÇÃÇ≈íçà”Ç∑ÇÈ
	Player* player_{ nullptr };
};