#pragma once

#include<DxLib.h>
#include<math.h>
#include"../Math/Vector3.h"
#include"../Math/Matrix.h"

static void DrawCircleGauge3D(const Vector3& pos,const Vector3& upVector,unsigned char R, unsigned char G, unsigned char B, unsigned char A,float size, float percent, const int handle= DX_NONE_GRAPH,float startangle=0.0f) {
	//100%��0�`4�͈̔͂ɕϊ�����
	float useparam = fabs(percent) / 25.0f;

	//�������擾
	int SX, SY;
	GetGraphSize(handle, &SX, &SY);

	for (int i = 0; i < 4; ++i) {
		//25%��(0�`1�͈�)���o��
		float ang = useparam;
		if (ang>1.0f)ang = 1.0f;

		//���o�����������匳���猸�炷
		useparam -= ang;

		VERTEX_3D vec[3];

		Vector3 rotVector = Vector3::Cross(upVector, Vector3::Left)*size;
		rotVector = rotVector*Matrix::CreateFromAxisAngle(upVector, startangle);
		//90�����̉�]�s����쐬
		Matrix rotMatrix = Matrix::CreateFromAxisAngle(upVector, ang*90.0f + 90.0f*i);
		//�ʒu���w��
		vec[0].pos = pos+ rotVector*Matrix::CreateFromAxisAngle(upVector, 90.0f*i);

		vec[1].pos = pos+rotVector*rotMatrix;

		vec[2].pos = pos;


		//�F�͎b��
		for (int j = 0; j < 3; ++j) {
			vec[j].a = A;
			vec[j].r = R;
			vec[j].g = G;
			vec[j].b = B;
		}

		//�e�N�X�`�����W
		vec[0].u = sinf((i + 0)*0.5f*DX_PI_F)*1.0f+0.5f;
		vec[0].v = cosf((i + 0)*0.5f*DX_PI_F)*1.0f+0.5f;

		vec[1].u = sinf((i + ang)*0.5f*DX_PI_F)*1.0f+0.5f;
		vec[1].v = cosf((i + ang)*0.5f*DX_PI_F)*1.0f+0.5f;

		vec[2].u = 0.5f;
		vec[2].v = 0.5f;

		/*
		vec[0].pos = Vector3{ 0.0f,10.0f,10.0f };
		vec[1].pos = Vector3{ 10.0f,10.0f,0.0f };
		vec[2].pos = Vector3{ 0.0f,10.0f,0.0f };
		*/
		//�`��
		DrawPolygon3DBase(vec, 3, DX_PRIMTYPE_TRIANGLESTRIP, handle, TRUE);
		//DrawPolygon3DBase(vec, 3, DX_PRIMTYPE_TRIANGLESTRIP, DX_NONE_GRAPH, TRUE);
		//DrawGraph(10, 10, handle, TRUE);
		//�p�x����������Ă��璆�f
		if (useparam <= 0.0f)break;
	}
}
void DrawSprite3D(const Vector3& position,float size,int handle, float startangle = 0.0f) {
	//�Q�[�W�g�̕`��������
	VERTEX_3D vec[4];
	vec[0].pos = position + Vector3{ -size,0.0f,size }*Matrix::CreateRotationY(startangle);
	vec[1].pos = position + Vector3{ size,0.0f,size }*Matrix::CreateRotationY(startangle);
	vec[2].pos = position + Vector3{ -size,0.0f,-size }*Matrix::CreateRotationY(startangle);
	vec[3].pos = position + Vector3{ size,0.0f,-size }*Matrix::CreateRotationY(startangle);
	vec[0].r = 255;
	vec[1].r = 255;
	vec[2].r = 255;
	vec[3].r = 255;
	vec[0].g = 255;
	vec[1].g = 255;
	vec[2].g = 255;
	vec[3].g = 255;
	vec[0].b = 255;
	vec[1].b = 255;
	vec[2].b = 255;
	vec[3].b = 255;
	vec[0].a = 255;
	vec[1].a = 255;
	vec[2].a = 255;
	vec[3].a = 255;
	vec[0].u = 0.0f;
	vec[0].v = 0.0f;
	vec[1].u = 1.0f;
	vec[1].v = 0.0f;
	vec[2].u = 0.0f;
	vec[2].v = 1.0f;
	vec[3].u = 1.0f;
	vec[3].v = 1.0f;

	DrawPolygon3DBase(vec, 4, DX_PRIMTYPE_TRIANGLESTRIP, handle, TRUE);
}