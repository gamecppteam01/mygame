//#pragma once
//#include "Collision.h"
//#include "CollisionParameter.h"
//#include <vector>
//
//enum ModelCollType
//{
//	All,
//	Wall,
//	Floor
//};
//
//// ���f��
//struct ModelData
//{
//	int		modelHandle;
//	int		modelFrameIndex = -1;
//
//	ModelData(int handle = 0, int frameIndex = -1) :
//		modelHandle(handle), modelFrameIndex(frameIndex)
//	{}
//};
//
//struct CollisionDX
//{
//	// �J�v�Z���ƃJ�v�Z���̓����蔻��
//	static bool Capsule_vs_Capsule(const Capsule& c1, const Capsule& c2);
//	// �J�v�Z���ƃJ�v�Z���̓����蔻��
//	static CollisionParameter Capsule_vs_Capsule(CollisionParameter& colpara, const Capsule& c1, const Capsule& c2);
//	// �J�v�Z���ƃ|���S���̓����蔻��
//	static bool Capsule_vs_Triangle(const Capsule& capsule, const Triangle& poly);
//	// �J�v�Z���ƃ|���S���̓����蔻��
//	static CollisionParameter Capsule_vs_Triangle(CollisionParameter& colpara, const Capsule& capsule, const Triangle& poly);
//
//	// ���f���Ɛ����̏Փ˔���
//	static CollisionParameter Model_vs_Line(CollisionParameter& colpara, const ModelData& model, const Line& line);
//	// ���f���Ƌ��̏Փ˔���
//	static CollisionParameter Model_vs_Sphere(CollisionParameter& colpara, const ModelData& model, const Sphere& sphere);
//	// ���f���ƃJ�v�Z���̏Փ˔���
//	static CollisionParameter Model_vs_Capsule(CollisionParameter& colpara, std::vector<MV1_COLL_RESULT_POLY>& colpoly, const ModelData& model, const Capsule& capsule, ModelCollType type = ModelCollType::All);
//};