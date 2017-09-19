#include "Enemy.h"
#include"../../Graphic/Model.h"
#include"../../World/IWorld.h"
#include"../../Define.h"
#include"../../Field/Field.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Math/Collision/CollisionMesh.h"
#include"../../Math/Collision/Collision.h"
#include"../../Math/Collision/CollisionFunction.h"
#include"../../Conv/DXConverter.h"
#include"../../Graphic/Anime.h"

Enemy::Enemy(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Actor(world, name, position, body), gravity_(0.0f), animation_(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL))
{
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
}

void Enemy::onMessage(EventMessage message, void * param)
{
}

void Enemy::onUpdate(float deltaTime)
{
	animation_.changeAnim(1, 1.0f);
	animation_.update(deltaTime);

	Vector3 velocity{ 0.0f,0.0f,0.0f };
		position_ += velocity;

	if(field())gravity_=0.0f;

	//float savey = position_.y;
	
	//checkCollideField();
	

	////world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), (VECTOR*)&position_);
	//world_->getField()->getMesh().collide_sphere(position_, body_->radius(), (VECTOR*)&position_);
	//position_.y = savey;
	//Vector3 start = position_+ Vector3{ 0.0f,gravity_+1.0f,0.0f };
	//Vector3 end = position_ - Vector3{ 0.0f,gravity_+6.0f,0.0f };
	//Vector3 intersect;
	//if (world_->getField()->getMesh().collide_line(start, end, (VECTOR*)&intersect)) {
	//	gravity_ = 0.0f;
	//	//if (MathHelper::Abs(position_.y - intersect.y) < 3.0f) {
	//	position_.y = intersect.y + 5.0f;
	//	//}
	//}
}

void Enemy::onDraw() const
{
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_/**Matrix::CreateRotationY(180.0f)*/).Translation(position_));

	body_->draw(position_);
}

void Enemy::onCollide(Actor & other)
{
}

//void Player::field()
//{
//	// 移動前の座標を保存
//	previousPosition_ = currentPosition_;
//	// 移動後の座標を算出
//	currentPosition_ = position_;
//
//	// 衝突したポリゴンを格納（壁）
//	std::vector<MV1_COLL_RESULT_POLY*> walls = std::vector<MV1_COLL_RESULT_POLY*>();
//	// 衝突したポリゴンを格納（床）
//	std::vector<MV1_COLL_RESULT_POLY*> floors = std::vector<MV1_COLL_RESULT_POLY*>();
//
//	// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
//	MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(world_->getField()->modelHandle(), -1, Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(0)), Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(1)), body_->radius());
//
//	hitNum_ = HitDim.HitNum;
//
//	// 検出されたポリゴンが壁ポリゴンか床ポリゴン判断し、それぞれ配列に格納
//	for (int i = 0; i < hitNum_; i++) {
//		// 内積で傾き具合を計算
//		float slope = Vector3::Dot(Vector3::VECTORToVector3(HitDim.Dim[i].Normal), Vector3::Up);
//		//壁の場合
//		if (slope < HIT_SLOPE_LIMIT) {
//		
//			DebugDraw::DebugDrawFormatString(0, 0, GetColor(255, 255, 255), "接触");
//			walls.push_back(&HitDim.Dim[i]);
//		}
//		//床の場合
//		else floors.push_back(&HitDim.Dim[i]);
//	}
//
//	bool isWallHit = false;
//
//	// 衝突した壁ポリゴンがない場合return
//	if (!walls.empty()) isWallHit = wall_hit_check(currentPosition_, walls);
//
//	bool isFloorHit = false;
//	// 床ポリゴンとの当たり判定
//	if (!floors.empty()) isFloorHit = floor_hit_check(currentPosition_, floors);
//
//	if (isFloorHit||isWallHit) {
//		gravity_ = 0.0f;
//		velocity_.y = 0.0f;
//		DebugDraw::DebugDrawFormatString(50, 50, GetColor(255, 255, 255), "接触");
//	}
//	// 検出したプレイヤーの周囲のポリゴン情報を開放する
//	MV1CollResultPolyDimTerminate(HitDim);
//	
//	//rotation_.Up(newNormal);
//
//	// 新しい座標を保存する
//	position_ = currentPosition_;
//
//}

void Enemy::checkCollideField()
{
	//// 移動前の座標を保存
	//previousPosition_ = currentPosition_;
	//// 移動後の座標を算出
	//currentPosition_ = position_;
	//
	//// 衝突したポリゴンを格納（壁）
	//std::vector<MV1_COLL_RESULT_POLY*> walls = std::vector<MV1_COLL_RESULT_POLY*>();
	//
	//// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	//MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(world_->getField()->modelHandle(), -1, Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(0)), Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(1)), body_->radius());
	//
	//hitNum_ = HitDim.HitNum;
	//
	//// 検出されたポリゴンが壁ポリゴンか床ポリゴン判断し、それぞれ配列に格納
	//for (int i = 0; i < hitNum_; i++) {
	//	// 内積で傾き具合を計算
	//	float slope = Vector3::Dot(Vector3::VECTORToVector3(HitDim.Dim[i].Normal), Vector3::Up);
	//	//壁の場合
	//	if (slope < HIT_SLOPE_LIMIT) {
	//
	//		DebugDraw::DebugDrawFormatString(0, 0, GetColor(255, 255, 255), "接触");
	//		walls.push_back(&HitDim.Dim[i]);
	//	}
	//}
	//
	//bool isWallHit = false;
	//
	//// 衝突した壁ポリゴンがない場合return
	//if (!walls.empty()) isWallHit = wall_hit_check(currentPosition_, walls);
	//
	//// 検出したプレイヤーの周囲のポリゴン情報を開放する
	//MV1CollResultPolyDimTerminate(HitDim);
	//
	//// 新しい座標を保存する
	//position_ = currentPosition_;


	// 壁ポリゴン保存ベクター
	std::vector<MV1_COLL_RESULT_POLY> walls = Collision::Model_Capsule(world_->getField()->modelHandle(), currentPosition_ + body_->points(0), currentPosition_ + body_->points(1), body_->radius());

	//周囲に壁ポリゴンがあった時のみ判定
	if (walls.size() > 0) {
		int MAX_CHALLENGE_COUNT = 64;
		// 押し出し処理を行う
		for (int challengeNumber = 0; challengeNumber < MAX_CHALLENGE_COUNT; challengeNumber++)
		{
			unsigned int count;
			for (count = 0; count < walls.size(); count++) {
				Triangle poly(
					DXConverter::GetInstance().ToVector3(walls.at(count).Position[0]),
					DXConverter::GetInstance().ToVector3(walls.at(count).Position[1]),
					DXConverter::GetInstance().ToVector3(walls.at(count).Position[2]));

				Capsule actorHit{ Capsule(body_->points(0), body_->points(1), body_->radius()) };

				if (!Collision::Capsule_Triangle(actorHit, poly))	continue;

				unsigned int k;
				for (k = 0; k < walls.size(); k++)
				{
					// ポリゴン生成
					auto afterPoly = Triangle(
						DXConverter::GetInstance().ToVector3(walls.at(k).Position[0]),
						DXConverter::GetInstance().ToVector3(walls.at(k).Position[1]),
						DXConverter::GetInstance().ToVector3(walls.at(k).Position[2]));
					// 当たっていたらループから抜ける
					if (Collision::Capsule_Triangle(actorHit, afterPoly))break;
				}
				if (k == walls.size()) break;

			}
			if (count != walls.size()) break;

		}

	}
	VECTOR newPosition;
	if (world_->getField()->getMesh().collide_line(position_ + rotation_.Up()*5.0f, position_ + rotation_.Down()*5.0f, &newPosition)) {
		position_.y = newPosition.y;
	}
}
