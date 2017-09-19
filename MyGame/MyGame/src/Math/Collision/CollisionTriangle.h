#pragma once
#include<DxLib.h>
#include"../Vector3.h"
#include"../Matrix.h"
#include<cmath>
#include"../../Graphic/DebugDraw.h"

class CollisionTriangle {
public:

	CollisionTriangle(const VECTOR& p1, const VECTOR& p2, const VECTOR& p3) :
		points_{ p1,p2,p3 } {
	}
	//�O�p�`���ɓ_�������Ă��邩�𒲂ׂ�A�ʂƓ������Ă��邩�𒲂ׂ�
	bool is_inside(const VECTOR& point)const {
		//�E�F�C�g�l�A����炷�ׂĂ�0�`1�̊ԂȂ�Β��ɂ���
		float w1, w2, w3;

		TriangleBarycenter(points_[0], points_[1], points_[2], point, &w1, &w2, &w3);
		//�d�S���W�̊e���ʒl���A0�`1�𒴂��Ă��Ȃ���΁A�O�p�`�̒��ɓ_������
		return (0.0f <= w1&&w1 <= 1.0f) && (0.0f <= w2&&w2 <= 1.0f) && (0.0f <= w3&&w3 <= 1.0f);
	}
	//�O�p�`�̊e�ӂƉ~���������Ă��邩�Aresult�͉����o����̉~�̒��S���W
	bool collide_edge_and_sphere(const VECTOR& center, float radius, VECTOR* result = nullptr) {
		auto is_collided = false;
		auto result_center = center;
		//�����̎n�_�A�I�_���X�g
		const VECTOR edges[4]{ points_[0],points_[1],points_[2],points_[0] };
		for (int i = 0; i < 3; ++i) {
			SEGMENT_POINT_RESULT segment_point_result;//�����̏Փˏ�������
			//�������Ă��邩�𒲂ׂ�(�~����̋����𒲂ׁAdistance���Z�o���鎖�ɂ�蔻�肵�Ă���)
			Segment_Point_Analyse(&edges[i], &edges[i + 1], &result_center, &segment_point_result);
			const auto distance = std::sqrt(segment_point_result.Seg_Point_MinDist_Square);
			if (distance <= radius) {
				//VSub���S����ŋ�Hit�_�������Ă�AVNorm�͐��K���AVScale�̓x�N�g���̑傫�����g�傷��Aradius - distance�͂߂荞�ݗʁAoffset�͉����o����
				VECTOR offset = VScale(VNorm(VSub(result_center, segment_point_result.Seg_MinDist_Pos)), radius - distance);
				result_center = VAdd(result_center, offset);
				is_collided = true;
			}
		}
		if (is_collided && (result != nullptr)) {
			*result = result_center;
		}
		return is_collided;
	}
	//�O�p�`�̊e�ӂƉ~���������Ă��邩�Aresult�͉����o����̉~�̒��S���W
	bool collide_edge_and_capsule_test(const VECTOR& start,const VECTOR& end, float radius, VECTOR* result = nullptr) {
		auto is_collided = false;
		auto result_start = start;
		auto result_end = end;
		//�����̎n�_�A�I�_���X�g
		const VECTOR edges[4]{ points_[0],points_[1],points_[2],points_[0] };
		for (int i = 0; i < 3; ++i) {
			SEGMENT_SEGMENT_RESULT segment_segment_result;//�����̏Փˏ�������
													  //�������Ă��邩�𒲂ׂ�(�~����̋����𒲂ׁAdistance���Z�o���鎖�ɂ�蔻�肵�Ă���)
			Segment_Segment_Analyse(&edges[i], &edges[i + 1], &result_start, &result_end, &segment_segment_result);
			//Segment_Point_Analyse(&edges[i], &edges[i + 1], &result_center, &segment_point_result);
			//�������m�����a�ȓ��ɂ�����
			const auto distance = std::sqrt(segment_segment_result.SegA_SegB_MinDist_Square);
			if (distance <= radius) {
				//VSub���S����ŋ�Hit�_�������Ă�AVNorm�͐��K���AVScale�̓x�N�g���̑傫�����g�傷��Aradius - distance�͂߂荞�ݗʁAoffset�͉����o����
				VECTOR offset = VScale(VNorm(VSub(segment_segment_result.SegB_MinDist_Pos, segment_segment_result.SegA_MinDist_Pos)), radius - distance);
				result_end = VAdd(result_end, offset);
				is_collided = true;
			}
		}
		if (is_collided && (result != nullptr)) {
			*result = result_end;
		}
		return is_collided;
	}
	//�O�p�`�̊e�ӂƉ~���������Ă��邩�Aresult�͉����o����̉~�̒��S���W
	bool collide_edge_and_capsule(const VECTOR& start, const VECTOR& end, float radius, VECTOR* result = nullptr) {
		bool is_collided = false;
		//if (collide_edge_and_sphere(start, radius, result))is_collided = true;
		Vector3 startResult;
		if (collide_edge_and_sphere(start, radius, (VECTOR*)&startResult))is_collided = true;
		if (collide_edge_and_sphere(end, radius, result))is_collided = true;



		auto result_start = start;
		auto result_end = end;
		//�����̎n�_�A�I�_���X�g
		const VECTOR edges[4]{ points_[0],points_[1],points_[2],points_[0] };
		for (int i = 0; i < 3; ++i) {
			SEGMENT_SEGMENT_RESULT segment_segment_result;//�����̏Փˏ�������
														  //�������Ă��邩�𒲂ׂ�(�~����̋����𒲂ׁAdistance���Z�o���鎖�ɂ�蔻�肵�Ă���)
			Segment_Segment_Analyse(&edges[i], &edges[i + 1], &result_start, &result_end, &segment_segment_result);
			//Segment_Point_Analyse(&edges[i], &edges[i + 1], &result_center, &segment_point_result);
			const auto distance = std::sqrt(segment_segment_result.SegA_SegB_MinDist_Square);
			if (distance <= radius) {
				//VSub���S����ŋ�Hit�_�������Ă�AVNorm�͐��K���AVScale�̓x�N�g���̑傫�����g�傷��Aradius - distance�͂߂荞�ݗʁAoffset�͉����o����
				VECTOR offset = VScale(VNorm(VSub(segment_segment_result.SegB_MinDist_Pos, segment_segment_result.SegA_MinDist_Pos)), radius - distance);
				result_end = VAdd(result_end, offset);
				is_collided = true;
			}
		}


		return is_collided;

	}
private:
	VECTOR points_[3];
};

