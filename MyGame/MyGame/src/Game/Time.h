#pragma once

// ���ԊǗ��N���X
class Time {
public:
	// �R���X�g���N�^
	Time();
	// �C���X�^���X
	static Time &GetInstance();
	// �X�V����
	void update();
	// �f���^�^�C����Ԃ�
	float deltaTime();
	// fps�̕\��
	void draw_fps();
private:
	float m_LastFrame;
	float m_LastTime;
	float m_RealtimeSinceStartup;
	float m_FrameCount;
	float m_DeltaTime;
private:
	int mCounter;
	int mFpsTime[2];
	int mFpsTime_i;
	float mFps;
};