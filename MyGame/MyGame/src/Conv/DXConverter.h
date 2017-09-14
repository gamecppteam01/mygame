#pragma once
#include "DxLib.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"
#include "../Math/Matrix.h"

class DXConverter
{
private:
	DXConverter() = default;
	~DXConverter() = default;

public:
	static DXConverter &GetInstance()
	{
		static DXConverter d;
		return d;
	}

	// Vector3��VECTOR�ɕϊ����ĕԂ�
	VECTOR ToVECTOR(const Vector3& v) const;
	// VECTOR��Vector3�ɕϊ����ĕԂ�
	Vector3 ToVector3(const VECTOR& v) const;

	// Vector3��Color�ɕϊ����ĕԂ�
	int ToColor(const Vector3& v) const;

	// Matrix��MATRIX�ɕϊ����ĕԂ�
	MATRIX ToMATRIX(const Matrix& m) const;
	// MATRIX��Matrix�ɕϊ����ĕԂ�
	Matrix ToMatrix(const MATRIX& m) const;
};