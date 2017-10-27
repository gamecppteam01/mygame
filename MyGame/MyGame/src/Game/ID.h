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

	TITLE_SCREEN,

	GAUGE_UI,
	BUTTON_A,
	BUTTON_B,
	BUTTON_C,
	BUTTON_D,
	ENEMY,
	PLAYER,
	MINIMAP,
	WARNING,

	COUNT_SPRITE//�S���\�[�X���m�F�p�L�[(���̃L�[�Ƀ��\�[�X��ݒ肵�Ȃ�����)
};

enum EFFECT_ID {

	SAMPLE_EFFECT,
	EFFECT_TEST,

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
	EFFECT_LIGHT_MODEL,

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

enum class EventMessage {

};


/*�L�q���[��
�ECall_��K�����ɂ��鎖
*/
enum class Notification {
	Call_CreateJustEffect,//�W���X�g�G�t�F�N�g�̐����ʒm
	Call_JustStep,//�W���X�g�G�t�F�N�g�̐����ʒm
};