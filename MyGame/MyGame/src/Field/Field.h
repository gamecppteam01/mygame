#pragma once
#include"../Math/Collision/CollisionMesh.h"

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
	// コピー禁止
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;
private:
	int mField;
	int mSkyBox;
	CollisionMesh mesh_;
};
