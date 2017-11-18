#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../World/IWorld.h"

class MusicScoreManager{
public:
	MusicScoreManager() = default;
	MusicScoreManager(IWorld* world);
	~MusicScoreManager();
	void SetWorld(IWorld* world);
	void SetSize(const Vector2& size);
	void SetMeasure(const float size);
	void Initialize();
	void Update(float deltaTime);
	void Draw(const Vector2& position)const;
	void Draw(const Vector3& position)const;
private:
	Vector2 scoreSize_{ Vector2::Zero };
	IWorld* world_{ nullptr };
	float currentBeat_{ 0.0f };
	float currentMeasure_{ 0.0f };

	float measureSize_{ 1.0f };
};
