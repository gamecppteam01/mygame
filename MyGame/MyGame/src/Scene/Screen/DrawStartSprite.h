#pragma once

#include"../../Game/ID.h"

enum class DrawStartSprite_FadeType {
	Fade_Scale,
	Fade_Fall,
	Fade_None
};

struct Vector2;
class DrawStartSprite {
private:
	enum State {
		In,
		Stay,
		Out
	};
public:
	DrawStartSprite(SPRITE_ID id, DrawStartSprite_FadeType type);

	void update(float deltaTime);
	void draw(const Vector2& position)const;

	bool isDead()const;

	void in();
	void stay();
	void out();
private:
	SPRITE_ID id_;//�`��X�v���C�g
	DrawStartSprite_FadeType type_;//�t�F�[�h�̎��

	State state_{ State::In };

	float scale_{ 1.0f };
	float alpha_{ 1.0f };

	float easeTimer_{ 0.0f };

	bool isDead_{ false };//�I���ʒm
};