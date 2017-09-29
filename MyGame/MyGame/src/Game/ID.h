#pragma once


// �X�v���C�gID
enum SPRITE_ID
{
	START_SPRITE,
	WHITE_SCREEN_SPRITE,
	BLACK_SCREEN_SPRITE,

	TITLE_START,
	TITLE_END,
	TITLE_SELECT,

	GAUGE_UI,
	BUTTON_A,
	BUTTON_B,
	BUTTON_C,
	BUTTON_D,


	COUNT_SPRITE//�S���\�[�X���m�F�p�L�[(���̃L�[�Ƀ��\�[�X��ݒ肵�Ȃ�����)
};

// ���f��ID
enum MODEL_ID
{
	//3D���f����
	DUMMY_MODEL,
	PLAYER_MODEL,
	ENEMY_MODEL,
	SKYBOX_MODEL,
	STAGE_MODEL,

	//�G�t�F�N�g��
	EFFECT_CIRCLE_MODEL,

	COUNT_MODEL//�S���\�[�X���m�F�p�L�[(���̃L�[�Ƀ��\�[�X��ݒ肵�Ȃ�����)

};

// SE_ID
enum SE_ID
{
	CHECK_SE,

	COUNT_CHECK//�S���\�[�X���m�F�p�L�[(���̃L�[�Ƀ��\�[�X��ݒ肵�Ȃ�����)
};

// BGM_ID
enum BGM_ID
{
	TITLE_BGM,
	
	COUNT_BGM//�S���\�[�X���m�F�p�L�[(���̃L�[�Ƀ��\�[�X��ݒ肵�Ȃ�����)

};

enum FONT_ID {
	JAPANESE_FONT,
	
	COUNT_FONT//�S���\�[�X���m�F�p�L�[(���̃L�[�Ƀ��\�[�X��ݒ肵�Ȃ�����)

};

