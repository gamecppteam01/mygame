#pragma once

#include <string>
#include <unordered_map>
#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../Game/ID.h"

class ShadowMap {
public:
	//�R���X�g���N�^
	ShadowMap() = default;
	//�f�X�g���N�^
	~ShadowMap();
	//������
	void initialize();
	//�V���h�E�}�b�v�̐���
	void makeShadowMap(const SHADOW_MAP_ID& id, const Point& size);
	//�V���h�E�}�b�v�̐���(���C�g�̕����܂�)
	void makeShadowMap(const SHADOW_MAP_ID& id, const Point& size,const Vector3& direction);
	//�w�肵���V���h�E�}�b�v�̍폜
	void DeletionShadowMap(const SHADOW_MAP_ID& id);
	//�S�ẴV���h�E�}�b�v�̍폜
	void AllDeletionShadowMap();
	//�w�肵���V���h�E�}�b�v�̃��C�g�̕����̐ݒ�
	void SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& direction) const;
	//�S�ẴV���h�E�}�b�v�̃��C�g�̕����̐ݒ�
	void AllSetLightDirection(const Vector3& direction) const;
	//�w�肵���V���h�E�}�b�v�̌��ʔ͈͂̐ݒ�
	void SetRange(const SHADOW_MAP_ID& id, Vector3& minPos, Vector3& maxPos) const;
	//�S�ẴV���h�E�}�b�v�̌��ʔ͈͂̐ݒ�
	void AllSetRange(Vector3& minPos, Vector3& maxPos) const;
	// �w�肵���V���h�E�}�b�v�ɕ`�悷��ۂ͈̔͂�ݒ肷��( ���̊֐��ŕ`��͈͂�ݒ肵�Ȃ��ꍇ�͎�������g�債���͈͂��`��͈͂ƂȂ� )
	void SetAdjustDepth(const SHADOW_MAP_ID& id, float depth) const;
	// �S�ẴV���h�E�}�b�v�ɕ`�悷��ۂ͈̔͂�ݒ肷��( ���̊֐��ŕ`��͈͂�ݒ肵�Ȃ��ꍇ�͎�������g�債���͈͂��`��͈͂ƂȂ� )
	void AllSetAdjustDepth(float depth) const;
	//�w�肵���V���h�E�}�b�v�ւ̕`�揀��
	void SetUp_ShadowMapDraw(const SHADOW_MAP_ID& id) const;
	//�S�ẴV���h�E�}�b�v�̕`�揀��
	void AllSetUp_ShadowMapDraw() const;
	//�V���h�E�}�b�v�ւ̕`����I������
	void DrawEnd_ShadowMap() const;
	//�g�p����V���h�E�}�b�v�̐ݒ�(slot0�`2�܂ŁA�����ɕ`��ł���V���h�E�}�b�v���͍ő�R�ڂ�)
	void SetUse_ShadowMap(const SHADOW_MAP_ID& id, int slot) const;
	//�g�p���Ă���V���h�E�}�b�v�̉���
	void ReleaseShadowMap(int slot) const;
	//�V���h�E�}�b�v�̕`��e�X�g
	void Draw_Test(const SHADOW_MAP_ID& id, Vector2& minpos, Vector2& maxpos) const;

private:
	
	// ���Ɏw��̃V���h�E�}�b�v�����݂��Ă�����A�X���[����
	void AlreadyGrow(const SHADOW_MAP_ID& id) const;

private:
	std::unordered_map<SHADOW_MAP_ID, int> m_ShadowMaps_;

public:
	//�𑜓x
	static const Point RESOLUTION_512;
	static const Point RESOLUTION_1024;
	static const Point RESOLUTION_2048;
	static const Point RESOLUTION_4096;
	static const Point RESOLUTION_8192;
	static const Point RESOLUTION_16384;
};