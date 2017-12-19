#pragma once
#include<string>
#include"../Math/Math.h"

struct Directional_Data{
	Directional_Data() = default;
	Directional_Data(const std::string& handle, const Vector3& position, const Vector3& direction)
	:handle_(handle), position_(position), direction_(direction){}
	std::string handle_;	//���C�g�̖��O
	Vector3 position_;		//���W
	Vector3 direction_;		//����
};

struct Spot_Data{
	Spot_Data() = default;
	Spot_Data(const std::string& handle, const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f,Color ambient = Color(0.2f,0.2f,0.2f,0.2f), Color diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f), Color specular = Color(1.0f, 1.0f, 1.0f, 1.0f))
	:handle_(handle),position_(position),direction_(direction),cone_outangle_ (cone_outangle),cone_inangle_(cone_inangle),range_(range),atten0_(atten0), atten1_(atten1) , atten2_(atten2),ambient_(ambient),diffuse_(diffuse),specular_(specular) {}
	std::string handle_;	//���C�g�̖��O
	Vector3 position_;		//���W
	Vector3 direction_;		//����
	float cone_outangle_;	//�O�p�x
	float cone_inangle_;	//���p�x
	float range_;			//�L������
	float atten0_;			//�����p�����[�^�@
	float atten1_;			//�����p�����[�^�A
	float atten2_;			//�����p�����[�^�B
	Color ambient_;			//�A���r�G���g�J���[
	Color diffuse_;			//�f�B�t�[�Y�J���[
	Color specular_;		//�X�y�L�����[�J���[
};

struct Point_Data{
	Point_Data() = default;
	Point_Data(const std::string& handle, const Vector3& position, const Vector3& direction, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f)
		:handle_(handle), position_(position), direction_(direction), range_(range), atten0_(atten0), atten1_(atten1), atten2_(atten2) {}
	std::string handle_;	//���C�g�̖��O
	Vector3 position_;		//���W
	Vector3 direction_;		//����
	float range_;			//�L������
	float atten0_;			//�����p�����[�^�@
	float atten1_;			//�����p�����[�^�A
	float atten2_;			//�����p�����[�^�B
};