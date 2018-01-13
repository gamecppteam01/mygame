#pragma once
#include"../Math/Collision/CollisionMesh.h"
#include"Audience.h"
// フィールドクラス
class Field {
public:
	// コンストラクタ
	Field(int field=-1, int skybox=-1);
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// フィールドのハンドル取得
	int modelHandle();
	CollisionMesh& getMesh();
	bool isInField(const Vector3& position);
	Vector3 CorrectPosition(const Vector3& position);
	float getXWidth()const;
	float getZWidth()const;
	// コピー禁止
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;
private:
	int mField;
	int fieldUp_;
	int fieldSide_;
	int wallUp_;
	int wallSide_;
	int wallCorner_;
	int mSkyBox;
	int audience_;
	CollisionMesh mesh_;
	Audience audience;
};
