//#include "CollisionFunction.h"
//#include "Collision.h"
//#include "CollisionDX.h"
//#include "CollisionParameter.h"
//#include "../dxlib/DXConverter.h"
//#include "../graphic/Model.h"
//#include "../actor/Actor.h"
//#include "../actor/Stage.h"
//
////#include "../util/collision/Line.h"
////#include "../util/collision/Ray.h"
//#include "../../Actor/Body/BoundingSphere.h"
//#include "../util/collision/BoundingBox.h"
//#include "../util/collision/OrientedBoundingBox.h"
//
//CollisionFunction::CollisionFunction(IWorld * world) :
//world_(world)
//{
//}
//
//CollisionFunction::~CollisionFunction()
//{
//}
//
//CollisionParameter CollisionFunction::Actor_vs_Wall(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//	colpara.colID = COL_ID::ACTOR_WALL_COL;
//
//	/* �p�����[�^�擾 */
//	// �ړ��x�N�g��
//	auto moveVec = one.GetVelocity();
//	// ���̃p�����[�^
//	auto nowParam = one.GetParameter();
//
//	// �����蔻��p�J�v�Z���f�[�^
//	Capsule actor(nowParam);
//	// �����蔻��p�X�e�[�W�f�[�^
//	ModelData stage(Model::GetInstance().GetHandle(static_cast<Stage*>(const_cast<Actor*>(&other))->GetColModelID()));
//
//	// �ǃ|���S���ۑ��x�N�^�[
//	static std::vector<MV1_COLL_RESULT_POLY> walls;
//	walls.clear();
//
//	// ���͂̃|���S���f�[�^�����
//	colpara = CollisionDX::Model_vs_Capsule(colpara, walls, stage, actor, ModelCollType::Wall);
//
//	// ���͂ɕǃ|���S�����Ȃ���ΏI��
//	if (walls.size() == 0)
//	{
//		walls.clear();
//		colpara.colFrag = false;
//		return colpara;
//	}
//
//	// �ړ��ʍ팸����
//	for (auto& wall : walls)
//	{
//		// �ړ����Ă��Ȃ���Ώȗ�
//		if (moveVec.Length() <= 0.1f) break;
//
//		// ���s��
//		int count = 0;
//		// �|���S������
//		Triangle poly(
//			DXConverter::GetInstance().ToVector3(wall.Position[0]),
//			DXConverter::GetInstance().ToVector3(wall.Position[1]),
//			DXConverter::GetInstance().ToVector3(wall.Position[2]));
//
//		// �J�v�Z���ƃ|���S�����������Ă��Ȃ���Ώȗ�
//		if (!CollisionDX::Capsule_vs_Triangle(actor, poly))	continue;
//		// �ړ��x�N�g���ƃ|���S���̖@���̂Ȃ��p���s�p�Ȃ�ȗ�
//		if (Vector3::Dot(moveVec.Normalize(), DXConverter::GetInstance().ToVector3(wall.Normal)) > 0.0f) continue;
//
//		// �ړ��ʃx�N�g��
//		Vector3 slideVec;
//		// �ړ��ʂ���ǂɂ��W�Q�������폜
//		slideVec = Vector3::Cross(moveVec, DXConverter::GetInstance().ToVector3(wall.Normal));
//		slideVec = Vector3::Cross(DXConverter::GetInstance().ToVector3(wall.Normal), slideVec);
//
//		/* �����o����̏��𔽉f */
//		// ���̍��W
//		auto pos = nowParam.mat.Translation() + slideVec * 0.025f;
//		nowParam.mat.Translation(pos);
//		actor = Capsule(nowParam);
//
//		// �V�����ʒu�ł̓����蔻��
//		for (auto& w : walls)
//		{
//			// �|���S������
//			Triangle ppoly(
//				DXConverter::GetInstance().ToVector3(w.Position[0]),
//				DXConverter::GetInstance().ToVector3(w.Position[1]),
//				DXConverter::GetInstance().ToVector3(w.Position[2]));
//			// �������Ă����烋�[�v���甲����
//			if (CollisionDX::Capsule_vs_Triangle(actor, ppoly))	break;
//			count++;
//		}
//		// ���s���ƕǃ|���S���̐����ꏏ�Ȃ烋�[�v���甲����
//		if (count == walls.size())	break;
//	}
//
//	// �����o���ő咧���
//	static const int MAX_CHALLENGE_COUNT = 64;
//	// �����o���������s��
//	for (int challengeNumber = 0; challengeNumber < MAX_CHALLENGE_COUNT; challengeNumber++)
//	{
//		// ���s��
//		unsigned int count;
//		for (count = 0; count < walls.size(); count++)
//		{
//			// �|���S������
//			Triangle currentPoly(
//				DXConverter::GetInstance().ToVector3(walls.at(count).Position[0]),
//				DXConverter::GetInstance().ToVector3(walls.at(count).Position[1]),
//				DXConverter::GetInstance().ToVector3(walls.at(count).Position[2]));
//
//			// �J�v�Z���ƃ|���S�����������Ă��Ȃ���Ώȗ�
//			if (!CollisionDX::Capsule_vs_Triangle(actor, currentPoly))	continue;
//			// �ړ��x�N�g���ƃ|���S���̖@���̂Ȃ��p���s�p�Ȃ�ȗ�
//			if (Vector3::Dot(moveVec.Normalize(), DXConverter::GetInstance().ToVector3(walls.at(count).Normal)) > 0.0f &&
//				moveVec.Length() <= 0.1f) continue;
//
//			// �ǃ|���S���̖@���~�K��ʈړ�������
//			auto pos = nowParam.mat.Translation() + DXConverter::GetInstance().ToVector3(walls.at(count).Normal) * 0.02f;
//			nowParam.mat.Translation(pos);
//			actor = Capsule(nowParam);
//
//			unsigned int k;
//			for (k = 0; k < walls.size(); k++)
//			{
//				// �|���S������
//				auto afterPoly = Triangle(
//					DXConverter::GetInstance().ToVector3(walls.at(k).Position[0]),
//					DXConverter::GetInstance().ToVector3(walls.at(k).Position[1]),
//					DXConverter::GetInstance().ToVector3(walls.at(k).Position[2]));
//				// �������Ă����烋�[�v���甲����
//				if (CollisionDX::Capsule_vs_Triangle(actor, afterPoly))	break;
//			}
//			// �S�Ẵ|���S���Ɠ������Ă��Ȃ������烋�[�v�E�o
//			if (k == walls.size()) break;
//		}
//		// ���s���ƕǃ|���S���̐�������Ă�����|���S���Ɠ������Ă��Ȃ����߃��[�v�E�o
//		if (count != walls.size()) break;
//	}
//
//	// ���X�V
//	colpara.colFrag = true;
//	colpara.colPos = nowParam.mat.Translation();
//	walls.clear();
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Actor_vs_Floor(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//	colpara.colID = COL_ID::ACTOR_STAGE_COL;
//
//	/* �����蔻��p�f�[�^�쐬 */
//	// �����蔻��p�X�e�[�W
//	ModelData stage(Model::GetInstance().GetHandle(static_cast<Stage*>(const_cast<Actor*>(&other))->GetColModelID()));
//	// �����蔻��p����
//	Line actor(one.GetParameter().mat.Translation() + Vector3(0.0f, 50.0f, 0.0f), one.GetParameter().mat.Translation() + Vector3(0.0f, -50.0f, 0.0f));
//
//	colpara = CollisionDX::Model_vs_Line(colpara, stage, actor);
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Player_vs_EnemySymboll(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//
//	colpara.colID = COL_ID::PLAYER_ENEMYSYMBOL_COL;
//	colpara = CollisionDX::Capsule_vs_Capsule(colpara, Capsule(one.GetParameter()), Capsule(other.GetParameter()));
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Player_vs_Portal(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//
//	colpara.colID = COL_ID::PLAYER_PORTAL_COL;
//
//	// �v���C���[����|�[�^���܂ł̋���
//	Vector3 p = one.GetParameter().mat.Translation() * Vector3(1.0f, 0.0f, 1.0f);
//	Vector3 o = other.GetParameter().mat.Translation() * Vector3(1.0f, 0.0f, 1.0f);
//	float distance = Vector3::Distance(p, o);
//	// �v���C���[�̔��a�ƃ|�[�^���̔��a
//	float r = one.GetParameter().radius + other.GetParameter().radius;
//	// ��苗���ȏ㗣��Ă���ꍇ�Փ˂��Ă��Ȃ�
//	if (distance >= r)	return colpara;
//
//	// Sphere
//	BoundingSphere sphere(one.GetParameter().mat.Translation(), one.GetParameter().radius);
//	// OBB
//	OrientedBoundingBox box(other.GetParameter().mat.Translation(), other.GetParameter().size,
//		other.GetParameter().mat.Right(), other.GetParameter().mat.Up(), other.GetParameter().mat.Backward());
//	
//	colpara.colFrag = box.Intersects(sphere, &colpara.colPos);
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Camera_vs_Wall(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//	colpara.colID = COL_ID::CAMERA_WALL_COL;
//
//	/* �����蔻��p�f�[�^�쐬 */
//	// �����蔻��p�X�e�[�W
//	ModelData stage(Model::GetInstance().GetHandle(static_cast<Stage*>(const_cast<Actor*>(&other))->GetColModelID()));
//	/* �����蔻��p���� */
//	// �v���C���[���W
//	Vector3 playerPos;
//	world_->EachActor(ACTOR_ID::PLAYER_ACTOR, [&](Actor& other)
//	{
//		playerPos = other.GetParameter().mat.Translation() + Vector3(0.0f, other.GetParameter().size.y, 0.0f);
//	});
//	// �v���C���[����J�����ւ̐���
//	Vector3 currentPos = one.GetParameter().mat.Translation();
//	Line line(playerPos, currentPos);
//	colpara = CollisionDX::Model_vs_Line(colpara, stage, line);
//	// �J�����̈ʒu���Z�o
//	float distance = Vector3::Distance(playerPos, currentPos);
//	float len = Vector3::Distance(playerPos, colpara.colPos);
//	float height = (distance - len) * 0.5f;
//	colpara.colPos += Vector3(0.0f, height, 0.0f);
//
//	return colpara;
//}
