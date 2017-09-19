#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../World/IWorld.h"
#include"../../Input/InputChecker.h"
#include"../../Define.h"
#include"../../Field/Field.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Math/Collision/CollisionMesh.h"
#include"../../Math/Collision/Collision.h"
#include"../../Math/Collision/CollisionFunction.h"
#include"../../Conv/DXConverter.h"
#include"../../Graphic/Anime.h"
#include"../../Graphic/Sprite.h"

Player::Player(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body) :
	Actor(world, name, position, body), gravity_(0.0f),animation_(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL))
{
	modelHandle_ = MODEL_ID::PLAYER_MODEL;

}

void Player::onMessage(EventMessage message, void * param)
{
}

void Player::onUpdate(float deltaTime)
{
	animation_.changeAnim(1,1.0f);
	animation_.update(deltaTime);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Right)) {
		framevelocity.x += 0.5f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Left)) {
		framevelocity.x -= 0.5f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Up)) {
		framevelocity.z += 0.5f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Down)) {
		framevelocity.z -= 0.5f;
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		framevelocity.y -= 0.5f;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Y)) {
		if(gravity_==0.0f)velocity_.y = 9.8f;
	}
	velocity_ -= velocity_*0.5f;
	framevelocity += velocity_;
	gravity_ -= 0.1f;
	framevelocity.y += gravity_;
	position_ += framevelocity;

	Vector3 hitcenter;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_+ body_->points(1), body_->radius(), (VECTOR*)&hitcenter))
	{
		gravity_ = 0.0f;
		position_ = hitcenter;// +rotation_.Up()*body_->length()*0.5f;
		OutputDebugString("��������");
		OutputDebugString("\n");
	}
	else {
		OutputDebugString("�������ĂȂ�");
		OutputDebugString("\n");
	}
			//	OutputDebugString(" x:");
			//	OutputDebugString(std::to_string(position_.x).c_str());
			//	OutputDebugString(" y:");
			//	OutputDebugString(std::to_string(position_.y).c_str());
			//	OutputDebugString(" z:");
			//	OutputDebugString(std::to_string(position_.z).c_str());
			//	OutputDebugString("\n");

	return; 

	float savey = position_.y;
	position_.y = savey;
	Vector3 start = position_ + Vector3{ 0.0f,2.0f,0.0f };
	Vector3 end = position_ - Vector3{ 0.0f,7.0f,0.0f };
	Vector3 intersect;
	if (world_->getField()->getMesh().collide_line(start, end, (VECTOR*)&intersect)) {
		gravity_ = 0.0f;
		//if (MathHelper::Abs(position_.y - intersect.y) < 3.0f) {
		position_.y = intersect.y + 5.0f;
		//}
	}

	field();
	//world_->getField()->getMesh().collide_sphere(position_, body_->radius(), (VECTOR*)&position_);
	//world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), (VECTOR*)&position_);



	return;
	//if(field())gravity_=0.0f;

	//float savey = position_.y;
	
	//checkCollideField();
	

	//world_->getField()->getMesh().collide_sphere(position_, body_->radius(), (VECTOR*)&position_);
	//position_.y = savey;
	//Vector3 start = position_+ Vector3{ 0.0f,2.0f,0.0f };
	//Vector3 end = position_ - Vector3{ 0.0f,7.0f,0.0f };
	//Vector3 intersect;
	//if (world_->getField()->getMesh().collide_line(start, end, (VECTOR*)&intersect)) {
	//	gravity_ = 0.0f;
	//	//if (MathHelper::Abs(position_.y - intersect.y) < 3.0f) {
	//	position_.y = intersect.y + 5.0f;
	//	//}
	//}
	//float savey = position_.y;

	//world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), (VECTOR*)&position_);

	//position_.y = savey;
}

void Player::onDraw() const
{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_*Matrix::CreateRotationY(180.0f)).Translation(drawPosition));

	body_->draw(position_);
}

void Player::onCollide(Actor & other)
{
}

//void Player::field()
//{
//	// �ړ��O�̍��W��ۑ�
//	previousPosition_ = currentPosition_;
//	// �ړ���̍��W���Z�o
//	currentPosition_ = position_;
//
//	// �Փ˂����|���S�����i�[�i�ǁj
//	std::vector<MV1_COLL_RESULT_POLY*> walls = std::vector<MV1_COLL_RESULT_POLY*>();
//	// �Փ˂����|���S�����i�[�i���j
//	std::vector<MV1_COLL_RESULT_POLY*> floors = std::vector<MV1_COLL_RESULT_POLY*>();
//
//	// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
//	MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(world_->getField()->modelHandle(), -1, Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(0)), Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(1)), body_->radius());
//
//	hitNum_ = HitDim.HitNum;
//
//	// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����f���A���ꂼ��z��Ɋi�[
//	for (int i = 0; i < hitNum_; i++) {
//		// ���ςŌX������v�Z
//		float slope = Vector3::Dot(Vector3::VECTORToVector3(HitDim.Dim[i].Normal), Vector3::Up);
//		//�ǂ̏ꍇ
//		if (slope < HIT_SLOPE_LIMIT) {
//		
//			DebugDraw::DebugDrawFormatString(0, 0, GetColor(255, 255, 255), "�ڐG");
//			walls.push_back(&HitDim.Dim[i]);
//		}
//		//���̏ꍇ
//		else floors.push_back(&HitDim.Dim[i]);
//	}
//
//	bool isWallHit = false;
//
//	// �Փ˂����ǃ|���S�����Ȃ��ꍇreturn
//	if (!walls.empty()) isWallHit = wall_hit_check(currentPosition_, walls);
//
//	bool isFloorHit = false;
//	// ���|���S���Ƃ̓����蔻��
//	if (!floors.empty()) isFloorHit = floor_hit_check(currentPosition_, floors);
//
//	if (isFloorHit||isWallHit) {
//		gravity_ = 0.0f;
//		velocity_.y = 0.0f;
//		DebugDraw::DebugDrawFormatString(50, 50, GetColor(255, 255, 255), "�ڐG");
//	}
//	// ���o�����v���C���[�̎��͂̃|���S�������J������
//	MV1CollResultPolyDimTerminate(HitDim);
//	
//	//rotation_.Up(newNormal);
//
//	// �V�������W��ۑ�����
//	position_ = currentPosition_;
//
//}

bool Player::field()
{
	//Capsule capsule(position_ + body_->points[0],
	//	position_ + body_->points[1],
	//	body_->radius());
	//
	//std::vector<MV1_COLL_RESULT_POLY> walls;
	//walls = Collision::Model_Capsule(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL),capsule.startPos,capsule.endPos,capsule.radius);
	//if (walls.size() == 0)
	//{
	//	walls.clear();
	//	return false;
	//}

	//for (auto wall : walls) {
	//
	//	Triangle poly{
	//		DXConverter::GetInstance().ToVector3(wall.Position[0]),
	//		DXConverter::GetInstance().ToVector3(wall.Position[1]),
	//		DXConverter::GetInstance().ToVector3(wall.Position[2])
	//	};
	//	Collision::Capsule_Triangle(
	//		capsule,
	//		poly
	//	);
	//
	//}

	// �ړ��O�̍��W��ۑ�
	previousPosition_ = currentPosition_;
	// �ړ���̍��W���Z�o
	currentPosition_ = position_;

	// �Փ˂����|���S�����i�[�i�ǁj
	std::vector<MV1_COLL_RESULT_POLY*> walls = std::vector<MV1_COLL_RESULT_POLY*>();
	// �Փ˂����|���S�����i�[�i���j
	std::vector<MV1_COLL_RESULT_POLY*> floors = std::vector<MV1_COLL_RESULT_POLY*>();

	// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(world_->getField()->modelHandle(), -1, Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(0)), Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(1)), body_->radius());

	hitNum_ = HitDim.HitNum;

	// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����f���A���ꂼ��z��Ɋi�[
	for (int i = 0; i < hitNum_; i++) {
		// ���ςŌX������v�Z
		float slope = Vector3::Dot(Vector3::VECTORToVector3(HitDim.Dim[i].Normal), Vector3::Up);

		//�ǂ̏ꍇ
		if (slope < HIT_SLOPE_LIMIT) walls.push_back(&HitDim.Dim[i]);
		//���̏ꍇ
		else floors.push_back(&HitDim.Dim[i]);
	}

	// �Փ˂����ǃ|���S�����Ȃ��ꍇreturn
	if (!walls.empty()) wall_hit_check(currentPosition_, walls);

	// ���|���S���Ƃ̓����蔻��
	if (!floors.empty()) {
		//float savey = position_.y;

		//world_->getField()->getMesh().collide_sphere(position_, body_->radius(), (VECTOR*)&position_);
		//position_.y = savey;
		Vector3 start = position_ + Vector3{ 0.0f, 1.0f,0.0f };
		Vector3 end = position_ - Vector3{ 0.0f, 6.0f,0.0f };
		Vector3 intersect;
		if (world_->getField()->getMesh().collide_line(start, end, (VECTOR*)&intersect)) {
			//if (MathHelper::Abs(position_.y - intersect.y) < 3.0f) {
			position_.y = intersect.y + 5.0f;
			//}
			return true;
		}
		return false;

		//floor_hit_check(currentPosition_, floors);
	}
	// ���o�����v���C���[�̎��͂̃|���S�������J������
	MV1CollResultPolyDimTerminate(HitDim);

	//world_->getField()->getMesh().collide_sphere(position_, body_->radius(), (VECTOR*)&position_);

	// �V�������W��ۑ�����
	position_ = currentPosition_;


	return true;
}

void Player::checkCollideField()
{
	//// �ړ��O�̍��W��ۑ�
	//previousPosition_ = currentPosition_;
	//// �ړ���̍��W���Z�o
	//currentPosition_ = position_;
	//
	//// �Փ˂����|���S�����i�[�i�ǁj
	//std::vector<MV1_COLL_RESULT_POLY*> walls = std::vector<MV1_COLL_RESULT_POLY*>();
	//
	//// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	//MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(world_->getField()->modelHandle(), -1, Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(0)), Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(1)), body_->radius());
	//
	//hitNum_ = HitDim.HitNum;
	//
	//// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����f���A���ꂼ��z��Ɋi�[
	//for (int i = 0; i < hitNum_; i++) {
	//	// ���ςŌX������v�Z
	//	float slope = Vector3::Dot(Vector3::VECTORToVector3(HitDim.Dim[i].Normal), Vector3::Up);
	//	//�ǂ̏ꍇ
	//	if (slope < HIT_SLOPE_LIMIT) {
	//
	//		DebugDraw::DebugDrawFormatString(0, 0, GetColor(255, 255, 255), "�ڐG");
	//		walls.push_back(&HitDim.Dim[i]);
	//	}
	//}
	//
	//bool isWallHit = false;
	//
	//// �Փ˂����ǃ|���S�����Ȃ��ꍇreturn
	//if (!walls.empty()) isWallHit = wall_hit_check(currentPosition_, walls);
	//
	//// ���o�����v���C���[�̎��͂̃|���S�������J������
	//MV1CollResultPolyDimTerminate(HitDim);
	//
	//// �V�������W��ۑ�����
	//position_ = currentPosition_;


	// �ǃ|���S���ۑ��x�N�^�[
	std::vector<MV1_COLL_RESULT_POLY> walls = Collision::Model_Capsule(world_->getField()->modelHandle(), currentPosition_ + body_->points(0), currentPosition_ + body_->points(1), body_->radius());

		//���͂ɕǃ|���S�������������̂ݔ���
	if (walls.size() > 0) {
		int MAX_CHALLENGE_COUNT = 64;
		// �����o���������s��
		for (int challengeNumber = 0; challengeNumber < MAX_CHALLENGE_COUNT; challengeNumber++)
		{
			unsigned int count;
			for (count = 0; count < walls.size(); count++){
				Triangle poly(
					DXConverter::GetInstance().ToVector3(walls.at(count).Position[0]),
					DXConverter::GetInstance().ToVector3(walls.at(count).Position[1]),
					DXConverter::GetInstance().ToVector3(walls.at(count).Position[2]));

				Capsule actorHit{ Capsule(body_->points(0), body_->points(1), body_->radius()) };

				if (!Collision::Capsule_Triangle(actorHit, poly))	continue;

				unsigned int k;
				for (k = 0; k < walls.size(); k++)
				{
					// �|���S������
					auto afterPoly = Triangle(
						DXConverter::GetInstance().ToVector3(walls.at(k).Position[0]),
						DXConverter::GetInstance().ToVector3(walls.at(k).Position[1]),
						DXConverter::GetInstance().ToVector3(walls.at(k).Position[2]));
					// �������Ă����烋�[�v���甲����
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
