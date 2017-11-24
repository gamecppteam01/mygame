#include "StandardLight.h"
#include<DxLib.h>

//�R���X�g���N�^
StandardLight::StandardLight(){
	initialize();
}

//������
void StandardLight::initialize() {
	setUseLighting(true);
	setLightEnable(true);
}

//���C�e�B���O�v�Z�������g�p���邩�ǂ�����ݒ肷��
void StandardLight::setUseLighting(bool value) {
	SetUseLighting(value);
}

//�s�N�Z���V�F�[�_�Ń��C�e�B���O�v�Z�����邩�ǂ����ݒ肷��
void StandardLight::setUsePixelLighting(bool valeu) {
	SetUsePixelLighting(valeu);
}


//�O���[�o���A���r�G���g�J���[��ݒ肷��
void StandardLight::setGlobalAmbientLight(Color& color) {
	SetGlobalAmbientLight(GetColorF(color.r, color.g, color.b, color.a));
}

//�W�����C�g�̃^�C�v���f�B���N�V���i�����C�g�ɂ���(����)
void StandardLight::changeLightTypeDir(const Vector3& direction) {
	ChangeLightTypeDir(VGet(direction.x, direction.y, direction.z));
}

//�W�����C�g�̃^�C�v���|�C���g���C�g�ɂ���(���W�A���C�g�̗L�������A�����p�����[�^0�A�����p�����[�^1�A�����p�����[�^2)
void StandardLight::changeLightTypePoint(const Vector3& position, float range, float atten0, float atten1, float atten2){
	ChangeLightTypePoint(VGet(position.x, position.y, position.z), range, atten0, atten1, atten2);
}

//�W�����C�g�̃^�C�v���X�|�b�g���C�g�ɂ���(���W�A�����A�R�[���̊O�p�x�A�R�[���̓��p�x�A���C�g�̗L�������A�����p�����[�^0�A�����p�����[�^1�A�����p�����[�^2)
void StandardLight::changeLightTypeSpot(const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0, float atten1, float atten2) {
	ChangeLightTypeSpot(VGet(position.x, position.y, position.z), VGet(direction.x, direction.y, direction.z), cone_outangle, cone_inangle, range, atten0, atten1, atten2);
}

//�W�����C�g�̗L���A�������Z�b�g����
void StandardLight::setLightEnable(bool value) {
	SetLightEnable(value);
}

//�W�����C�g�̃f�B�t�[�Y�J���[��ݒ肷��
void StandardLight::setLightDiffuseColor(Color& color) {
	SetLightDifColor(GetColorF(color.r, color.g, color.b, color.a));
}

//�W�����C�g�̃X�y�L�����J���[��ݒ肷��
void StandardLight::setLghtSpecurColor(Color& color) {
	SetLightSpcColor(GetColorF(color.r, color.g, color.b, color.a));
}

//�W�����C�g�̃A���r�G���g�J���[��ݒ肷��
void StandardLight::setLightAmbientColor(Color& color) {
	SetLightAmbColor(GetColorF(color.r, color.g, color.b, color.a));
}

//�W�����C�g�̕�����ݒ肷��
void StandardLight::setLightDirection(Vector3& direction) {
	SetLightDirection(VGet(direction.x, direction.y, direction.z));
}

//�W�����C�g�̈ʒu��ݒ肷��
void StandardLight::setLightPosition(Vector3& position) {
	SetLightPosition(VGet(position.x, position.y, position.z));
}

//�W�����C�g�̗L�������Ƌ��������p�����[�^��ݒ肷��
void StandardLight::setLightRangeAtten(float range, float atten0, float atten1, float atten2) {
	SetLightRangeAtten(range, atten0, atten1, atten2);
}

//�W�����C�g�̏Ǝˊp�x�p�����[�^��ݒ肷��
void StandardLight::setLightAngle(float outangle, float inangle) {
	SetLightAngle(outangle, inangle);
}

//�W�����C�g�̃^�C�v���擾����
int StandardLight::getLightType() {
	return GetLightType();
}

//�W�����C�g�̗L���A�������擾����
bool StandardLight::getLightEnable() {
	return GetLightEnable();
}

//�W�����C�g�̃f�B�t�[�Y�J���[���擾����
Color StandardLight::getLightDiffuseColor() {
	return Color(GetLightDifColor().r, GetLightDifColor().g, GetLightDifColor().b, GetLightDifColor().a);
}

//�W�����C�g�̃X�y�L�����J���[���擾����
Color StandardLight::getLighSpecurColor() {
	return Color(GetLightSpcColor().r, GetLightSpcColor().g, GetLightSpcColor().b, GetLightSpcColor().a);
}

//�W�����C�g�̃A���r�G���g�J���[���擾����
Color StandardLight::getLightAmbientColor() {
	return Color(GetLightAmbColor().r, GetLightAmbColor().g, GetLightAmbColor().b, GetLightAmbColor().a);
}

//�W�����C�g�̕������擾����
Vector3 StandardLight::getLightDirection() {
	return Vector3(GetLightDirection().x, GetLightDirection().y, GetLightDirection().z);
}

//�W�����C�g�̈ʒu���擾����
Vector3 StandardLight::getLightPosition() {
	return Vector3(GetLightPosition().x, GetLightPosition().y, GetLightPosition().z);
}
