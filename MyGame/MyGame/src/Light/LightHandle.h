#pragma once
#include"../Math/Vector3.h"
#include"../Math/Color.h"
#include<map>
#include<string>

class LightHandle {
public:
	//�R���X�g���N�^
	LightHandle();
	//������
	void initialize();
	//���C�e�B���O�v�Z�������g�p���邩�ǂ�����ݒ肷��
	void setUseLighting(bool value);
	//�s�N�Z���V�F�[�_�Ń��C�e�B���O�v�Z�����邩�ǂ����ݒ肷��
	void setUsePixelLighting(bool valeu);
	//�O���[�o���A���r�G���g�J���[��ݒ肷��
	void setGlobalAmbientLight(Color& color);
	//�f���N�V���i���^�C�v�̃��C�g�n���h���̍쐬
	void createDirLightHandle(const std::string& handle,const Vector3& direction);
	//�|�C���g�^�C�v�̃��C�g�n���h���̍쐬
	void createPointLightHandle(const std::string& handle, const Vector3& position, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//�X�|�b�g�^�C�v�̃��C�g�n���h���̍쐬
	void createSpotLightHandle(const std::string& handle, const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//���C�g�n���h�����폜����
	void deleteLightHandle(const std::string& handle);
	//���C�g�n���h����S�č폜����
	void deleteLightHandleAll();
	//���C�g�n���h���̃^�C�v��ύX����
	void changeLightTypeHandle(const std::string& handle, int lightType);
	//���C�g�n���h���̗L���A������ݒ肷��
	void setLightEnableHandle(const std::string& handle, bool value);
	//���C�g�n���h���̃f�B�t���[�Y�J���[��ݒ肷��
	void setLightDiffuseColorHandle(const std::string& handle, Color& color);
	//���C�g�n���h���̃X�y�L�����[�J���[��ݒ肷��
	void setLightSpecuarColorHandle(const std::string& handle, Color& color);
	//���C�g�n���h���̃A���r�G���g�J���[��ݒ肷��
	void setLightAmbientColorHandle(const std::string& handle, Color& color);
	//���C�g�n���h���̕������w�肷��
	void setLightDirectionHandle(const std::string& handle, const Vector3& direction);
	//���C�g�n���h���̈ʒu��ݒ肷��
	void setLightPositionHandle(const std::string& handle, const Vector3& position);
	//���C�g�n���h���̗L�������Ƌ��������p�����[�^��ݒ肷��
	void setLightRangeAttenHandle(const std::string& handle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//���C�g�n���h���̏Ǝˊp�x�p�����[�^��ݒ肷��
	void setLightAngleHandle(const std::string& handle, float cone_outangle, float cone_inangle);
	//���C�g�n���h���̃^�C�v���擾����
	int getLightTypeHandle(const std::string& handle);
	//���C�g�n���h���̗L���A�������擾����
	bool getLightEnableHandle(const std::string& handle);
	//���C�g�n���h���̃f�B�t���[�Y�J���[���擾����
	Color getLightDiffuseColorHandle(const std::string& handle);
	//���C�g�n���h���̃X�y�L�����[�J���[���擾����
	Color getLightSpecuarColorHandle(const std::string& handle);
	//���C�g�n���h���̃A���r�G���g�J���[���擾����
	Color getLightAmbientColorHandle(const std::string& handle);
	//���C�g�n���h���̕������擾����
	Vector3 getLightDirectionHandle(const std::string& handle);
	//���C�g�n���h���̈ʒu���擾����
	Vector3 getLightPositionHandle(const std::string& handle);
	//�L���ɂȂ��Ă��郉�C�g�n���h���̐����擾����
	int getEnableLightHandleNum();
	//�L���ɂȂ��Ă��郉�C�g�n���h�����擾����
	int getEnableLightHandle(int index);
	//�O���[�o���̃A���r�G���g�F���擾
	Color getGlobalAmbientColor();
public:
	static const int DirType;
	static const int PointType;
	static const int SpotType;

private:
	Color color_;
	std::map<std::string, int> lightHandles_;
};
