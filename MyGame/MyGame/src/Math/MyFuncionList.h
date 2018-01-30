#pragma once
#include"../math/Vector2.h"
#include"../math/Matrix.h"
#include"../math/Vector3.h"
#include"../math/MathHelper.h"
#include<vector>

template<typename _Tp> inline int sign(_Tp val) {
	return 1 - (val <= 0) - (val < 0);
}

//rollVect=��]����(1�ŉE���)
inline float MathAngle(const Vector2& targetVect,const Vector2& baseVect=Vector2::Up,int rollVect=1) {
	Vector2 nTVect = targetVect;
	Vector2 nBVect = baseVect;

	float angle = Vector2::Dot(nTVect, nBVect) / (nTVect.Length()*nBVect.Length());
	angle = MathHelper::ToDegrees(acos(angle));
	if (sign(nTVect.x) > 0) {
		angle = 360 - angle;

	}
	return angle;
}
//�w�莲�Ƃ̂Ȃ��p�̊p�x��Ԃ�
inline float MathFormedAngle(const Vector2& targetVect, const Vector2& baseVect = Vector2::Up) {
	Vector2 nTVect = targetVect;
	Vector2 nBVect = baseVect;
	
	float angle = Vector2::Dot(nTVect, nBVect) / (nTVect.Length()*nBVect.Length());
	angle = MathHelper::ToDegrees(acos(angle));

	return angle;
}

//�`��J�n�_�ƁA�`������A�����A�c������A�`��͈͂�\��4�_��Ԃ� �`��ʒudirN=����
//inline DrawPos MathDrawPoint(const Vector2& basePos,const Vector2& dir, int width,int height) {
//	DrawPos p;
//
//	//������̂ւ̃x�N�g��(���K��)
//	Vector2 pHtoBVec2 = Vector2::Normalize(dir);
//	Vector3 pHtoBVec3 = pHtoBVec2;
//
//	//HtoB�x�N�g����90�x��]
//	Vector3 pHtBRotateVec = pHtoBVec3*Matrix::CreateRotationZ(90);
//	//Vec2�ɕϊ�
//	Vector2 pHtBNVerticalVec(pHtBRotateVec.x, pHtBRotateVec.y);
//	pHtBNVerticalVec = pHtBNVerticalVec.Normalize();
//
//	Vector2 drawBasePos = basePos;
//
//	p.p0 = drawBasePos - (pHtBNVerticalVec*(float)width);
//	p.p1 = drawBasePos + (pHtBNVerticalVec*(float)width);
//
//	drawBasePos += pHtoBVec2*(float)height;
//
//	p.p2 = drawBasePos + (pHtBNVerticalVec*(float)width);
//	p.p3 = drawBasePos - (pHtBNVerticalVec*(float)width);
//
//	return p;
//}
//inline NeckPiecePoint MathNeckPiecePoint(const Vector2& fulcrum, const Vector2& tipPos, float width) {
//	NeckPiecePoint p;
//
//	//������̂ւ̃x�N�g��(���K��)
//	Vector2 pHtoBVec2 = Vector2::Normalize(tipPos - fulcrum);
//	Vector3 pHtoBVec3 = pHtoBVec2;
//
//	//HtoB�x�N�g����90�x��]
//	Vector3 pHtBRotateVec = pHtoBVec3*Matrix::CreateRotationZ(90);
//	//Vec2�ɕϊ�
//	Vector2 pHtBNVerticalVec(pHtBRotateVec.x, pHtBRotateVec.y);
//	pHtBNVerticalVec = pHtBNVerticalVec.Normalize();
//
//	Vector2 drawBasePos = fulcrum;
//
//	p.fulcrumLeft = drawBasePos - (pHtBNVerticalVec*width);
//	p.fulcrumRight = drawBasePos + (pHtBNVerticalVec*width);
//
//	float height = Vector2::Distance(fulcrum, tipPos)*1.2f;
//	drawBasePos += pHtoBVec2*height;
//
//	p.tipPosLeft = drawBasePos + (pHtBNVerticalVec*width);
//	p.tipPosRight = drawBasePos - (pHtBNVerticalVec*width);
//
//	return p;
//}

inline int DigitLength(int num) {
	if (num == 0) {
		return 1;
	}

	int count = 0;
	while (num) {
		num = num / 10;
		++count;
	}
	return count;
}

inline std::vector<int> SligeDigit(int num) {
	std::vector<int> result;

	if (num == 0) {
		result.push_back(0);
		return result;
	}

	int i = 0;
	while (num >= 1) {
		int mod = 0;
		mod = num % 10;
		num = num / 10;
		result.push_back(mod);
	}
	return result;

}