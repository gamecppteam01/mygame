#pragma once

#include "DxLib.h"
#include "Time.h"
#include "../Input/InputChecker.h"
#include "../Math/Math.h"
#include"../Camera/Camera.h"
#include"../Input/DualShock4Manager.h"
#include"../Graphic/EffekseerManager.h"

class Game {
protected:
	// �R���X�g���N�^
	Game(const Vector2& screen_size = Vector2(800, 600), float rate = 1.0f, int window = TRUE, float fps = 60.0f) :
		mWidth(static_cast<int>(screen_size.x)), mHeight(static_cast<int>(screen_size.y)), mRate(rate), mWindow(window), mFps(fps) {
	}

public:
	// ���s
	int run() {
		// �T�C�Y�w��
		SetGraphMode(mWidth, mHeight, 32);
		// �`��{��
		SetWindowSizeExtendRate(mRate);
		// �E�C���h�E���[�h�ɂ��邩�ǂ���
		ChangeWindowMode(mWindow);
		SetUseDirect3DVersion(DX_DIRECT3D_9);
		//DXLib����������
		if (DxLib_Init() == -1)return -1;//�G���[���N������I��
		SetDrawScreen(DX_SCREEN_BACK);
		EffekseerManager::GetInstance().Initialize();
		start();

		// �L�[���������܂Ń��[�v���܂�
		while (isRunning()) {
			etceteraUpdate();

			update();
			draw();

			frameEnd();
			//Time::GetInstance().draw_fps();
			// ����ʂ̓��e��\��ʂɔ��f������
			ScreenFlip();
		}

		end();

		//DXLib�g�p�I������
		DxLib_End();

		return 0;	//�\�t�g�I��
	}

private:
	// �J�n
	virtual void start() {}
	// �X�V
	virtual void update() {}
	// �`��
	virtual void draw() {}
	//�t���[���I��������
	virtual void frameEnd() {}
	// �I��
	virtual void end() {}
	// ���s����
	virtual bool isRunning() { return (ProcessMessage() == 0 && ClearDrawScreen() == 0 && Keyboard::GetInstance().KeyStateUp(KEYCODE::ESC)); }

	void etceteraUpdate() {
		//deltaTime�̍X�V
		Time::GetInstance().update();
		//���͂̍X�V
		InputChecker::GetInstance().Update();
		//DualShock4��p�̓��͍X�V
		DualShock4Manager::GetInstance().Update();

		EffekseerManager::GetInstance().Update();
	}
private:
	// �R�s�[�֎~
	Game(const Game& other) = delete;
	Game& operator = (const Game& other) = delete;

private:
	// �E�B���h�E�̕�
	int mWidth;
	// �E�B���h�E�̍���
	int mHeight;
	// �E�C���h�E�̕`��䗦
	float mRate;
	// �E�C���h�E���[�h���H
	int mWindow;
	// FPS
	float mFps;
};