#include "Keyboard.h"

// �R���X�g���N�^
Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		m_onkey[i]  = 0;
		m_offkey[i] = 0;
	}
}

// �L�[�����������̃g���K�[����
bool Keyboard::KeyTriggerDown(UINT keycode)
{
	if (m_onkey[keycode] == 1)	return true;
	return false;
}

// �L�[�����������̃X�e�[�g����
bool Keyboard::KeyStateDown(UINT keycode)
{
	if (m_keycode[keycode] == 1)	return true;
	return false;
}

// �L�[�𗣂������̃g���K�[����
bool Keyboard::KeyTriggerUp(UINT keycode)
{
	if (m_offkey[keycode] == 1)	return true;
	return false;
}

// �L�[�𗣂������̃X�e�[�g����
bool Keyboard::KeyStateUp(UINT keycode)
{
	if (m_keycode[keycode] == 0)	return true;
	return false;
}

// �����ꂩ�̃L�[�����͂��ꂽ���u�Ԃ𒲂ׂ�
bool Keyboard::AnyTriggerDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_onkey[i] == 1)return true;
	}
	return false;
}

// �����ꂩ�̃L�[�����͂���Ă��邩���ׂ�
bool Keyboard::AnyStateDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 1)return true;
	}
	return false;
}

// �����ꂩ�̃L�[�����ꂽ���u�Ԃ𒲂ׂ�
bool Keyboard::AnyTriggerUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_offkey[i] == 1)	return true;
	}
	return false;
}

// �����ꂩ�̃L�[������Ă��邩���ׂ�
bool Keyboard::AnyStateUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 0)	return true;
	}
	return false;
}

// �X�V����
void Keyboard::Update()
{
	GetHitKeyStateAll(m_keycode);

	for (int i = 0; i < 256; i++)
	{
		UpdateKey(m_keycode[i], i);
	}
}

void Keyboard::UpdateKey(char key, int num)
{
	// ������Ă����
	if (key != 0)
	{
		m_offkey[num] = 0;
		m_onkey[num]++;
	}
	// ������Ă��Ȃ����
	else
	{
		m_onkey[num] = 0;
		m_offkey[num]++;
	}
}
