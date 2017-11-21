#include "LightHandle.h"
#include<DxLib.h>

//���C�g�^�C�v
const int LightHandle::DirType = DX_LIGHTTYPE_DIRECTIONAL;
const int LightHandle::PointType = DX_LIGHTTYPE_POINT;
const int LightHandle::SpotType = DX_LIGHTTYPE_SPOT;

//�R���X�g���N�^
LightHandle::LightHandle(){
	initialize();
}

//������
void LightHandle::initialize(){
	setUseLighting(true);
	lightHandles_.clear();
}

//���C�e�B���O�v�Z�������g�p���邩�ǂ�����ݒ肷��
void LightHandle::setUseLighting(bool value) {
	SetUseLighting(value);
}

//�O���[�o���A���r�G���g�J���[��ݒ肷��
void LightHandle::setGlobalAmbientLight(Color& color) {
	SetGlobalAmbientLight(GetColorF(color.r, color.g, color.b, color.a));
}

//�f���N�V���i���^�C�v�̃��C�g�n���h���̍쐬
void LightHandle::createDirLightHandle(const std::string& handle, const Vector3& direction) {
	lightHandles_[handle] = CreateDirLightHandle(VGet(direction.x, direction.y, direction.z));
}

//�|�C���g�^�C�v�̃��C�g�n���h���̍쐬
void LightHandle::createPointLightHandle(const std::string& handle, const Vector3& position, float range, float atten0, float atten1, float atten2) {
	lightHandles_[handle] = CreatePointLightHandle(VGet(position.x, position.y, position.z), range, atten0, atten1, atten2);
}

//�X�|�b�g�^�C�v�̃��C�g�n���h���̍쐬
void LightHandle::createSpotLightHandle(const std::string& handle, const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0, float atten1, float atten2) {
	lightHandles_[handle] = CreateSpotLightHandle(VGet(position.x, position.y, position.z), VGet(direction.x, direction.y, direction.z), cone_outangle, cone_inangle, range, atten0, atten1, atten2);
}

//���C�g�n���h�����폜����
void LightHandle::deleteLightHandle(const std::string& handle) {
	DeleteLightHandle(lightHandles_[handle]);
	lightHandles_.erase(handle);
}

//���C�g�n���h����S�č폜����
void LightHandle::deleteLightHandleAll() {
	DeleteLightHandleAll();
	lightHandles_.clear();
}

//���C�g�n���h���̃^�C�v��ύX����
void LightHandle::changeLightTypeHandle(const std::string& handle, int lightType) {
	SetLightTypeHandle(lightHandles_[handle], lightType);
}

//���C�g�n���h���̗L���A������ݒ肷��
void LightHandle::setLightEnableHandle(const std::string& handle, bool value) {
	SetLightEnableHandle(lightHandles_[handle], value);
}

//���C�g�n���h���̃f�B�t���[�Y�J���[��ݒ肷��
void LightHandle::setLightDiffuseColorHandle(const std::string& handle, Color& color) {
	SetLightDifColorHandle(lightHandles_[handle], GetColorF(color.r, color.g, color.b, color.a));
}

//���C�g�n���h���̃X�y�L�����[�J���[��ݒ肷��
void LightHandle::setLightSpecuarColorHandle(const std::string& handle, Color& color) {
	SetLightSpcColorHandle(lightHandles_[handle], GetColorF(color.r, color.g, color.b, color.a));
}

//���C�g�n���h���̃A���r�G���g�J���[��ݒ肷��
void LightHandle::setLightAmbientColorHandle(const std::string& handle, Color& color) {
	SetLightAmbColorHandle(lightHandles_[handle], GetColorF(color.r, color.g, color.b, color.a));
}

//���C�g�n���h���̕������w�肷��
void LightHandle::setLightDirectionHandle(const std::string& handle, const Vector3& direction) {
	SetLightPositionHandle(lightHandles_[handle], VGet(direction.x, direction.y, direction.z));
}

//���C�g�n���h���̈ʒu��ݒ肷��
void LightHandle::setLightPositionHandle(const std::string& handle, const Vector3& position) {
	SetLightPositionHandle(lightHandles_[handle], VGet(position.x, position.y, position.z));
}

//���C�g�n���h���̗L�������Ƌ��������p�����[�^��ݒ肷��
void LightHandle::setLightRangeAttenHandle(const std::string& handle, float range, float atten0, float atten1, float atten2) {
	SetLightRangeAttenHandle(lightHandles_[handle], range, atten0, atten1, atten2);
}

//���C�g�n���h���̏Ǝˊp�x�p�����[�^��ݒ肷��
void LightHandle::setLightAngleHandle(const std::string& handle, float cone_outangle, float cone_inangle) {
	SetLightAngleHandle(lightHandles_[handle], cone_outangle, cone_inangle);
}

//���C�g�n���h���̃^�C�v���擾����
int LightHandle::getLightTypeHandle(const std::string& handle) {
	return GetLightTypeHandle(lightHandles_[handle]);
}

//���C�g�n���h���̗L���A�������擾����
bool LightHandle::getLightEnableHandle(const std::string& handle) {
	return GetLightEnableHandle(lightHandles_[handle]);
}

//���C�g�n���h���̃f�B�t���[�Y�J���[���擾����
Color LightHandle::getLightDiffuseColorHandle(const std::string& handle) {
	return Color(
		GetLightDifColorHandle(lightHandles_[handle]).r,
		GetLightDifColorHandle(lightHandles_[handle]).g,
		GetLightDifColorHandle(lightHandles_[handle]).b, 
		GetLightDifColorHandle(lightHandles_[handle]).a);
}

//���C�g�n���h���̃X�y�L�����[�J���[���擾����
Color LightHandle::getLightSpecuarColorHandle(const std::string& handle) {
	return Color(
		GetLightSpcColorHandle(lightHandles_[handle]).r,
		GetLightSpcColorHandle(lightHandles_[handle]).g,
		GetLightSpcColorHandle(lightHandles_[handle]).b,
		GetLightSpcColorHandle(lightHandles_[handle]).a);
}

//���C�g�n���h���̃A���r�G���g�J���[���擾����
Color LightHandle::getLightAmbientColorHandle(const std::string& handle) {
	return Color(
		GetLightAmbColorHandle(lightHandles_[handle]).r,
		GetLightAmbColorHandle(lightHandles_[handle]).g,
		GetLightAmbColorHandle(lightHandles_[handle]).b,
		GetLightAmbColorHandle(lightHandles_[handle]).a);
}

//���C�g�n���h���̕������擾����
Vector3 LightHandle::getLightDirectionHandle(const std::string& handle) {
	return Vector3(
		GetLightDirectionHandle(lightHandles_[handle]).x,
		GetLightDirectionHandle(lightHandles_[handle]).y,
		GetLightDirectionHandle(lightHandles_[handle]).z);
}

//���C�g�n���h���̈ʒu���擾����
Vector3 LightHandle::getLightPositionHandle(const std::string& handle) {
	return Vector3(
		GetLightPositionHandle(lightHandles_[handle]).x,
		GetLightPositionHandle(lightHandles_[handle]).y,
		GetLightPositionHandle(lightHandles_[handle]).z);
}

//�L���ɂȂ��Ă��郉�C�g�n���h���̐����擾����
int LightHandle::getEnableLightHandleNum() {
	return GetEnableLightHandleNum();
}

//�L���ɂȂ��Ă��郉�C�g�n���h�����擾����
int LightHandle::getEnableLightHandle(int index) {
	return GetEnableLightHandle(index);
}