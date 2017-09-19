//#pragma once
//#include "../world/IWorld.h"
//
//class Actor;
//struct CollisionParameter;
//
//class CollisionFunction
//{
//public:
//	// �R���X�g���N�^
//	explicit CollisionFunction(IWorld* world);
//	// �f�X�g���N�^
//	~CollisionFunction();
//
//	// �A�N�^�[vs��
//	CollisionParameter Actor_vs_Wall(const Actor& one, const Field& other) const;
//	// �A�N�^�[vs��
//	CollisionParameter Actor_vs_Floor(const Actor& one, const Actor& other) const;
//	// �v���C���[vs�G�l�~�[�V���{��
//	CollisionParameter Player_vs_EnemySymboll(const Actor& one, const Actor& other) const;
//	// �v���C���[vs�G�l�~�[�V���{��
//	CollisionParameter Player_vs_Portal(const Actor& one, const Actor& other) const;
//	// �J����vs��
//	CollisionParameter Camera_vs_Wall(const Actor& one, const Actor& other) const;
//
//private:
//	// ���[���h�|�C���^
//	IWorld*		world_;
//};