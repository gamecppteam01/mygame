#pragma once
#include"Math\Math.h"
#include<string>

///�X�N���[���̃T�C�Y
static const Vector2	SCREEN_SIZE = Vector2(1280.0f, 720.0f);
static const int WINDOW_WIDTH = (int)SCREEN_SIZE.x;
static const int WINDOW_HEIGHT = (int)SCREEN_SIZE.y;
///�E�C���h�E�̕\���{��
static const float		WINDOW_RATE = 1.0f;
///�E�C���h�E���[�h�ɂ��邩���Ȃ���(TRUE : FALSE)
static const int		WINDOW_MODE = TRUE;

// �t�B�[���h�n���p�����[�^
///�t�B�[���h�̍��W
static const Vector3	FIELD_POS = Vector3::Zero;
///�t�B�[���h�̃T�C�Y(�X�J�C�{�b�N�X�\��t����ʒu)
static const float		FIELD_SIZE = 10.0f;
///�t�B�[���h�̊g�嗦
static const float		FIELD_SCALE = 1.0f;

// �J�����n���p�����[�^
///�J�����̏����p�x
static const Vector3	CAMERA_INIT_ANGLE = Vector3::Zero;
///�J�����̓��͑��x
static const float		CAMERA_INPUT_SPEED = 3.0f;
///�J�����̍ő��]�p�x���E
static const float		CAMERA_ANGLE_MAX = 20.0f;
///�J�����̍ŏ���]�p�x���E
static const float		CAMERA_ANGLE_MIN = -20.0f;
///�J�����̍ő�`��͈�
static const float		CAMERA_NEAR = 0.1f;
///�J�����̍ŏ��`��͈�
static const float		CAMERA_FAR = 1000;

static const float BGMVOLUME = 1.0f;
static const float SEVOLUME = 1.0f;

static const float		HALF = 0.5f;

// �A�N�^�[�n���p�����[�^
///�A�N�^�[�̏d��
static const float		GRAVITY = 9.8f;
///�l�^�̍���
static const float		PERSON_HEIGHT = 17.0f;
///�l�^�̒��S�̍���(�����̔���)
static const float		PERSON_CENTER_HEIGHT = PERSON_HEIGHT * HALF;
///�l�^�̔��a(���S�̍����̔���)
static const float		PERSON_RADIUS = PERSON_CENTER_HEIGHT * HALF;
///���グ�邱�Ƃ̂ł���Ζʂ̌��E
static const float		HIT_SLOPE_LIMIT = 0.5f;
