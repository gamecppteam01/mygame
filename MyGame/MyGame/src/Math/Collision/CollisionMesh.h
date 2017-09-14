#pragma once
#include<DxLib.h>
#include"../Vector3.h"
#include"../Matrix.h"
#include"CollisionTriangle.h"
#include<cmath>
#include"../../Graphic/DebugDraw.h"


class CollisionMesh {
public:
	CollisionMesh(int model) :model_{ model } {
	}
	//���b�V���Ɛ����̓����蔻��
	bool collide_line(const VECTOR& start, const VECTOR& end, VECTOR* point = nullptr, VECTOR* normal = nullptr)const {
		//�������Ă��邩�𒲂ׂāA��_�Ɩ@����Ԃ�
		const auto coll_poly = MV1CollCheck_Line(model_, 0, start, end);
		//��_�Ɩ@���f�[�^������
		if (coll_poly.HitFlag == TRUE) {
			if (point != nullptr) {
				*point = coll_poly.HitPosition;
			}
			if (normal != nullptr) {
				*normal = coll_poly.Normal;
			}
		}
		return coll_poly.HitFlag == TRUE;
	}
	//���b�V���Ƌ��̂̓����蔻��
	bool collide_sphere(const VECTOR& center, float radius, VECTOR* result = nullptr)const {
		//���f���Ƌ��̂̓����蔻��֐��A����������������
		const auto coll_poly = MV1CollCheck_Sphere(model_, 0, center, radius);
		if (coll_poly.HitNum == 0) {
			//�Փ˔���f�[�^�̍폜�Acoll_poly�̓������m�ۂ𓮓I�ɍs���Ă��邽�߁APoly�p��delete����̊֐����ĂԕK�v������
			MV1CollResultPolyDimTerminate(coll_poly);
			return false;
		}
		auto result_center = center;
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			//���ʂƓ_�̏Փˊ֌W���̓��ꕨ
			PLANE_POINT_RESULT plane_point_result;
			//�������ʂƓ_�̓����蔻����s���A���ʏ�Ɉ�ԋ߂��_�𒲂ׂ��肵�Ă����
			Plane_Point_Analyse(
				&coll_poly.Dim[i].Position[0],//���ʂ̂����D���ȓ_�A���ʏ�ł����position[0]�łȂ��Ă��ǂ�
				&coll_poly.Dim[i].Normal,
				&result_center,
				&plane_point_result//����ɖ������ʂƁA���g�̓_�̍ł��߂��_�̏�񓙂�����
				);

			//�O�p�`�̒��ɁA�������ʂ̂�����ԋ߂��_�������Ă��邩�𒲂ׂ�=�O�p�`�̒��ɒ��S�_�������Ă��邩�𒲂ׂ�
			if (CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//�ʂɓ������Ă���A�ʂ̖@�������ɉ����o���A�傫����offset�A�߂荞�ݕ����������o��
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//�@�������ɉ����o���x�N�g���̌v�Z
				const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
				result_center = VAdd(result_center, offset);
			}
		}
		//�|���S���ƕӂ̔���
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).collide_edge_and_sphere(result_center, radius, &result_center);
		}
		if (result != nullptr) {
			*result = result_center;
		}
		MV1CollResultPolyDimTerminate(coll_poly);
		return true;
	}
	//�J�v�Z���Ƃ̔���(start=��,end=��)
	bool collide_capsule(const VECTOR& start,const VECTOR& end,float radius, VECTOR* result=nullptr) {
		
		// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
		MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(model_, -1, start, end, radius);

		if (HitDim.HitNum == 0) {
			// ���o�����v���C���[�̎��͂̃|���S�������J������
			MV1CollResultPolyDimTerminate(HitDim);
			return false;
		}

		auto result_end = end;
		for (int i = 0; i < HitDim.HitNum; ++i) {
			//���ʂƓ_�̏Փˊ֌W���̓��ꕨ
			PLANE_POINT_RESULT plane_point_result;
			//�������ʂƓ_�̓����蔻����s���A���ʏ�Ɉ�ԋ߂��_�𒲂ׂ��肵�Ă����
			Plane_Point_Analyse(
				&HitDim.Dim[i].Position[0],//���ʂ̂����D���ȓ_�A���ʏ�ł����position[0]�łȂ��Ă��ǂ�
				&HitDim.Dim[i].Normal,
				&result_end,
				&plane_point_result//����ɖ������ʂƁA���g�̓_�̍ł��߂��_�̏�񓙂�����
			);

			//�O�p�`�̒��ɁA�������ʂ̂�����ԋ߂��_�������Ă��邩�𒲂ׂ�=�O�p�`�̒��ɒ��S�_�������Ă��邩�𒲂ׂ�
			if (CollisionTriangle(
				HitDim.Dim[i].Position[0],
				HitDim.Dim[i].Position[1],
				HitDim.Dim[i].Position[2]
			).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//�ʂɓ������Ă���A�ʂ̖@�������ɉ����o���A�傫����offset�A�߂荞�ݕ����������o��
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//�@�������ɉ����o���x�N�g���̌v�Z
				const auto offset = VScale(HitDim.Dim[i].Normal, radius - distance);
				result_end = VAdd(result_end, offset);
			}
		}
		//�|���S���ƕӂ̔���
		for (int i = 0; i < HitDim.HitNum; ++i) {
			CollisionTriangle(
				HitDim.Dim[i].Position[0],
				HitDim.Dim[i].Position[1],
				HitDim.Dim[i].Position[2]
			).collide_edge_and_capsule(start,result_end, radius, &result_end);
		}
		if (result != nullptr) {
			*result = result_end;
		}
		MV1CollResultPolyDimTerminate(HitDim);
		return true;



//		// �ړ��O�̍��W��ۑ�
//		previousPosition_ = currentPosition_;
//		// �ړ���̍��W���Z�o
//		currentPosition_ = position_;
//
//		// �Փ˂����|���S�����i�[�i�ǁj
//		std::vector<MV1_COLL_RESULT_POLY*> walls = std::vector<MV1_COLL_RESULT_POLY*>();
//
//		// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
//		MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(world_->getField()->modelHandle(), -1, Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(0)), Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(1)), body_->radius());
//
//		hitNum_ = HitDim.HitNum;
//
//		// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����f���A���ꂼ��z��Ɋi�[
//		for (int i = 0; i < hitNum_; i++) {
//			// ���ςŌX������v�Z
//			float slope = Vector3::Dot(Vector3::VECTORToVector3(HitDim.Dim[i].Normal), Vector3::Up);
//
//			//�ǂ̏ꍇ
//			if (slope < HIT_SLOPE_LIMIT) walls.push_back(&HitDim.Dim[i]);
//		}
//
//		// �Փ˂����ǃ|���S�����Ȃ��ꍇreturn
//		if (!walls.empty()) wall_hit_check(currentPosition_, walls);
//
//		// ���o�����v���C���[�̎��͂̃|���S�������J������
//		MV1CollResultPolyDimTerminate(HitDim);
//
//		// �V�������W��ۑ�����
//		position_ = currentPosition_;


	}

private:
	int model_;
};
