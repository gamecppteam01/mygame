#pragma once
#include"Scene.h"
#include"Screen/SoftwareKeyboard.h"
#include"../Input/DualShock4Manager.h"
#include"../Math/Math.h"
#include<vector>
#include<array>
#include<memory>
#include"../UI/Model_Animation_UI/Animation_UI.h"
#include"../Graphic/AnimationDx.h"

class NamingScene :public Scene {
public:
	
	enum NamingState {
		name,
		select
	};

	NamingScene();
	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	SoftwareKeyboard key_{};

	std::unique_ptr<Animation_UI> anim_UI_;
	
	Vector3 cameraPos_{ Vector3::Zero };
	Vector3 cameraTarget_{ Vector3::Zero };

	Vector3 manPos_{ Vector3::Zero };
	
	Vector2 cursorPos_{ Vector2::Zero };

	NamingState nameState_;

	int cursor_{ 0 };

	float timer_;
	int sinCount_;
	float alpha_;
	float Xpos_{ 0 };

	//カーソルの位置及びボタンの位置リスト
	const std::vector<std::pair<Vector2, SceneType>> cursorPoses{
		{ Vector2{ 690.0f, 555.0f },SceneType::SCENE_STAGESELECT },
		{ Vector2{ 990.0f, 555.0f },SceneType::SCENE_NAMING }
	};
};