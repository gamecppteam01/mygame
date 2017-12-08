#include "ShadowMap.h"

//�𑜓x
const Point ShadowMap::RESOLUTION_512 = Point(512, 512);
const Point ShadowMap::RESOLUTION_1024 = Point(1024, 1024);
const Point ShadowMap::RESOLUTION_2048 = Point(2048, 2048);
const Point ShadowMap::RESOLUTION_4096 = Point(4096, 4096);
const Point ShadowMap::RESOLUTION_8192 = Point(8192, 8192);
const Point ShadowMap::RESOLUTION_16384 = Point(16384, 16384);


//�f�X�g���N�^
ShadowMap::~ShadowMap(){

}

//������
void ShadowMap::initialize() {
	m_ShadowMaps_.clear();
}

//�V���h�E�}�b�v�̐���
void ShadowMap::makeShadowMap(const SHADOW_MAP_ID& id, const Point& size) {
	AlreadyGrow(id);
	m_ShadowMaps_[id] = MakeShadowMap(size.x, size.y);
}

//�V���h�E�}�b�v�̐���(���C�g�̕����܂�)
void ShadowMap::makeShadowMap(const SHADOW_MAP_ID& id, const Point& size, const Vector3& direction) {
	AlreadyGrow(id);
	m_ShadowMaps_[id] = MakeShadowMap(size.x, size.y);
	SetLightDirection(id, direction);
}

//�w�肵���V���h�E�}�b�v�̍폜
void ShadowMap::DeletionShadowMap(const SHADOW_MAP_ID& id) {
	DeleteShadowMap(m_ShadowMaps_[id]);
	m_ShadowMaps_.erase(id);
}

//�S�ẴV���h�E�}�b�v�̍폜
void ShadowMap::AllDeletionShadowMap() {
	for (auto shadowmap : m_ShadowMaps_) {
		DeleteShadowMap(shadowmap.second);
	}
	m_ShadowMaps_.clear();
}

//�w�肵���V���h�E�}�b�v�̃��C�g�̕����̐ݒ�
void ShadowMap::SetLightDirection(const SHADOW_MAP_ID& id, const Vector3& direction) const {
	SetShadowMapLightDirection(m_ShadowMaps_.at(id), direction);
}

//�S�ẴV���h�E�}�b�v�̃��C�g�̕����̐ݒ�
void ShadowMap::AllSetLightDirection(const Vector3& direction) const {
	for (auto shadowmap : m_ShadowMaps_) {
		SetShadowMapLightDirection(shadowmap.second, direction);
	}
}

//�w�肵���V���h�E�}�b�v�̌��ʔ͈͂̐ݒ�
void ShadowMap::SetRange(const SHADOW_MAP_ID& id, Vector3& minPos, Vector3& maxPos) const {
	SetShadowMapDrawArea(m_ShadowMaps_.at(id), minPos, maxPos);
}

//�S�ẴV���h�E�}�b�v�̌��ʔ͈͂̐ݒ�
void ShadowMap::AllSetRange(Vector3& minPos, Vector3& maxPos) const {
	for (auto shadowmap : m_ShadowMaps_) {
		SetShadowMapDrawArea(shadowmap.second, minPos, maxPos);
	}
}

// �w�肵���V���h�E�}�b�v�ɕ`�悷��ۂ͈̔͂�ݒ肷��( ���̊֐��ŕ`��͈͂�ݒ肵�Ȃ��ꍇ�͎�������g�債���͈͂��`��͈͂ƂȂ� )
void ShadowMap::SetAdjustDepth(const SHADOW_MAP_ID& id, float depth) const {
	SetShadowMapAdjustDepth(m_ShadowMaps_.at(id), depth);
}

// �S�ẴV���h�E�}�b�v�ɕ`�悷��ۂ͈̔͂�ݒ肷��( ���̊֐��ŕ`��͈͂�ݒ肵�Ȃ��ꍇ�͎�������g�債���͈͂��`��͈͂ƂȂ� )
void ShadowMap::AllSetAdjustDepth(float depth) const{
	for (auto shadowmap : m_ShadowMaps_) {
		SetShadowMapAdjustDepth(shadowmap.second, depth);
	}
}

//�w�肵���V���h�E�}�b�v�ւ̕`�揀��
void ShadowMap::SetUp_ShadowMapDraw(const SHADOW_MAP_ID& id) const {
	ShadowMap_DrawSetup(m_ShadowMaps_.at(id));
}

//�S�ẴV���h�E�}�b�v�̕`�揀��
void ShadowMap::AllSetUp_ShadowMapDraw() const {
	for (auto shadowmap : m_ShadowMaps_) {
		ShadowMap_DrawSetup(shadowmap.second);
	}
}

//�V���h�E�}�b�v�ւ̕`����I������
void ShadowMap::DrawEnd_ShadowMap() const {
	ShadowMap_DrawEnd();
}

//�g�p����V���h�E�}�b�v�̐ݒ�(slot0�`2�܂ŁA�����ɕ`��ł���V���h�E�}�b�v���͍ő�R�ڂ�)
void ShadowMap::SetUse_ShadowMap(const SHADOW_MAP_ID& id, int slot) const {
	SetUseShadowMap(slot, m_ShadowMaps_.at(id));
}

//�g�p���Ă���V���h�E�}�b�v�̉���
void ShadowMap::ReleaseShadowMap(int slot) const {
	SetUseShadowMap(slot, -1);
}

//�V���h�E�}�b�v�̕`��e�X�g
void ShadowMap::Draw_Test(const SHADOW_MAP_ID& id, Vector2& minpos, Vector2& maxpos) const {
	TestDrawShadowMap(m_ShadowMaps_.at(id), minpos.x, minpos.y, maxpos.x, maxpos.y);
}

// ���Ɏw��̃V���h�E�}�b�v�����݂��Ă�����A�X���[����
void ShadowMap::AlreadyGrow(const SHADOW_MAP_ID& id) const
{
	if (m_ShadowMaps_.find(id) != m_ShadowMaps_.end())
	{
		throw std::string(id + "�V���h�E�}�b�v�������ЂƂ������悤�Ƃ��܂���");
	}
}
