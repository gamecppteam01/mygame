#pragma once

#include <string>

struct Vector2;

/// <summary>
/// �񎟌����W�N���X
/// </summary>
class Point
{
public:
	int x;
	int y;
public:
	/// <summary>
	/// (0, 0)�ŏ��������ꂽ�񎟌����W��Ԃ��܂�
	/// </summary>
	static Point Zero;
	/// <summary>
	/// (1, 1)�ŏ��������ꂽ�񎟌����W��Ԃ��܂�
	/// </summary>
	static Point One;
	/// <summary>
	/// (-1, 0)�ŏ��������ꂽ�񎟌����W��Ԃ��܂�
	/// </summary>
	static Point Left;
	/// <summary>
	/// (1, 0)�ŏ��������ꂽ�񎟌����W��Ԃ��܂�
	/// </summary>
	static Point Right;
	/// <summary>
	/// (0, -1)�ŏ��������ꂽ�񎟌����W��Ԃ��܂�
	/// </summary>
	static Point Up;
	/// <summary>
	/// (0, 1)�ŏ��������ꂽ�񎟌����W��Ԃ��܂�
	/// </summary>
	static Point Down;
	/// <summary>
	/// ��ʒ����̍��W�ŏ��������ꂽ�񎟌����W��Ԃ��܂�
	/// </summary>
	static Point Center();
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Point();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Point(int x, int y);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Point(const Point& vec);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	explicit Point(int s);
public:
	/// <summary>
	/// ������Ԃ��܂�
	/// </summary>
	float Length() const;
	/// <summary>
	/// �����̓���Ԃ��܂�
	/// </summary>
	float LengthPow2() const;
	/// <summary>
	/// ��_�Ԃ̋�����Ԃ��܂�
	/// </summary>
	float Distance(const Point& other) const;
public:
	/// <summary>
	/// ��_�Ԃ̋�����Ԃ��܂�
	/// </summary>
	static float Distance(const Point& v1, const Point& v2);

public:
	Point& operator = (const Point& v);
	operator Vector2() const;
	operator std::string() const;
};

bool operator == (const Point& v1, const Point& v2);
bool operator != (const Point& v1, const Point& v2);
Point operator + (const Point& v1, const Point& v2);
Point& operator += (Point& v1, const Point& v2);
Point operator - (const Point& v1, const Point& v2);
Point& operator -= (Point& v1, const Point& v2);
Point operator * (const Point& v, const int f);
Point operator * (const int f, const Point& v);
Point& operator *= (Point& v, const int f);
Point& operator *= (const int f, Point& v);
Point operator / (const Point& v, const int f);
Point operator / (const int f, const Point& v);
Point& operator /= (Point& v, const int f);
Point operator - (const Point& v);
