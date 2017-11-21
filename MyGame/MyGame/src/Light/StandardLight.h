#pragma once
#include"../Math/Vector3.h"
#include"../Math/Color.h"

//�W�����C�g�N���X
class StandardLight {
public:
	//�R���X�g���N�^
	StandardLight();
	//������
	void initialize();
	//���C�e�B���O�v�Z�������g�p���邩�ǂ�����ݒ肷��
	void setUseLighting(bool value);
	//�O���[�o���A���r�G���g�J���[��ݒ肷��
	void setGlobalAmbientLight(Color& color);
	//�W�����C�g�̃^�C�v���f�B���N�V���i�����C�g�ɂ���(����)
	void changeLightTypeDir(const Vector3& direction);
	//�W�����C�g�̃^�C�v���|�C���g���C�g�ɂ���(���W�A���C�g�̗L�������A�����p�����[�^0�A�����p�����[�^1�A�����p�����[�^2)
	void changeLightTypePoint(const Vector3& position, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//�W�����C�g�̃^�C�v���X�|�b�g���C�g�ɂ���(���W�A�����A�R�[���̊O�p�x�A�R�[���̓��p�x�A���C�g�̗L�������A�����p�����[�^0�A�����p�����[�^1�A�����p�����[�^2)
	void changeLightTypeSpot(const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//�W�����C�g�̗L���A�������Z�b�g����
	void setLightEnable(bool value);
	//�W�����C�g�̃f�B�t�[�Y�J���[��ݒ肷��
	void setLightDiffuseColor(Color& color);
	//�W�����C�g�̃X�y�L�����J���[��ݒ肷��
	void setLghtSpecurColor(Color& color);
	//�W�����C�g�̃A���r�G���g�J���[��ݒ肷��
	void setLightAmbientColor(Color& color);
	//�W�����C�g�̕�����ݒ肷��
	void setLightDirection(Vector3& direction);
	//�W�����C�g�̈ʒu��ݒ肷��
	void setLightPosition(Vector3& position);
	//�W�����C�g�̗L�������Ƌ��������p�����[�^��ݒ肷��
	void setLightRangeAtten(float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//�W�����C�g�̏Ǝˊp�x�p�����[�^��ݒ肷��
	void setLightAngle(float outangle, float inangle);
	//�W�����C�g�̃^�C�v���擾����
	int getLightType();
	//�W�����C�g�̗L���A�������擾����
	bool getLightEnable();
	//�W�����C�g�̃f�B�t�[�Y�J���[���擾����
	Color getLightDiffuseColor();
	//�W�����C�g�̃X�y�L�����J���[���擾����
	Color getLighSpecurColor();
	//�W�����C�g�̃A���r�G���g�J���[���擾����
	Color getLightAmbientColor();
	//�W�����C�g�̕������擾����
	Vector3 getLightDirection();
	//�W�����C�g�̈ʒu���擾����
	Vector3 getLightPosition();
};