#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include "../UI/UI.h"

class ButtonUI : public UI {
public:
	//�R���X�g���N�^
	ButtonUI( const SPRITE_ID& id, const Vector2& position);
	//�J�n
	void start();
	//�`��
	void draw() const;

private:
	//�{�^���̍��W
	Vector2 m_Position;
	//�{�^����ID
	SPRITE_ID m_ID;
};