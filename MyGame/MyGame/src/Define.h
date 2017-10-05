#pragma once
#include"Math\Math.h"
#include<string>

///スクリーンのサイズ
static const Vector2	SCREEN_SIZE = Vector2(1280.0f, 720.0f);
static const int WINDOW_WIDTH = (int)SCREEN_SIZE.x;
static const int WINDOW_HEIGHT = (int)SCREEN_SIZE.y;
///ウインドウの表示倍率
static const float		WINDOW_RATE = 1.0f;
///ウインドウモードにするかしないか(TRUE : FALSE)
static const int		WINDOW_MODE = TRUE;

// フィールド系統パラメータ
///フィールドの座標
static const Vector3	FIELD_POS = Vector3::Zero;
///フィールドのサイズ(スカイボックス貼り付け基準位置)
static const float		FIELD_SIZE = 10.0f;
///フィールドの拡大率
static const float		FIELD_SCALE = 1.0f;

// カメラ系統パラメータ
///カメラの初期角度
static const Vector3	CAMERA_INIT_ANGLE = Vector3::Zero;
///カメラの入力速度
static const float		CAMERA_INPUT_SPEED = 3.0f;
///カメラの最大回転角度限界
static const float		CAMERA_ANGLE_MAX = 20.0f;
///カメラの最小回転角度限界
static const float		CAMERA_ANGLE_MIN = -20.0f;
///カメラの最大描画範囲
static const float		CAMERA_NEAR = 0.1f;
///カメラの最小描画範囲
static const float		CAMERA_FAR = 1000;

static const float BGMVOLUME = 1.0f;
static const float SEVOLUME = 1.0f;

static const float		HALF = 0.5f;

// アクター系統パラメータ
///アクターの重力
static const float		GRAVITY = 9.8f;
///人型の高さ
static const float		PERSON_HEIGHT = 17.0f;
///人型の中心の高さ(高さの半分)
static const float		PERSON_CENTER_HEIGHT = PERSON_HEIGHT * HALF;
///人型の半径(中心の高さの半分)
static const float		PERSON_RADIUS = PERSON_CENTER_HEIGHT * HALF;
///乗り上げることのできる斜面の限界
static const float		HIT_SLOPE_LIMIT = 0.5f;
