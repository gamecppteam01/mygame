#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../World/IWorld.h"

class MusicScoreManager{
public:
	MusicScoreManager() = default;
	explicit MusicScoreManager(IWorld* world);
	~MusicScoreManager();
	void SetWorld(IWorld* world);
	void SetSize(const Vector2& size);
	void SetMeasure(const float size);
	void Initialize();
	void Update(float deltaTime);
	void Draw(const Vector2& position)const;
	float Draw(const Vector3& position, const Vector3& upVector)const;

	bool getNotice()const;
	void setNotice(bool notice);

	bool isJust()const;
private:
	Vector2 scoreSize_{ Vector2::Zero };
	IWorld* world_{ nullptr };
	float currentBeat_{ 0.0f };
	float currentMeasure_{ 0.0f };//数小節間での現在の位置

	int handle_;//エフェクトハンドル
	float scaleTimer_;

	bool isNotice_;
	float measureSize_{ 1.0f };
};
