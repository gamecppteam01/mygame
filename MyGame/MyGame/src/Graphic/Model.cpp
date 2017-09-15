#include "Model.h"
#include "../game/WorkFolder.h"
#include "../math/Point.h"
#include <Dxlib.h>
#include <sstream>
#include <algorithm>

#define PI 3.14159265358979f

Model::ModelHandle::ModelHandle(int cmp) :
param(cmp), handle(0),
isInit(false), isCol(false), isRef(false)
{

}
Model::ModelHandle::~ModelHandle()
{
	Delete();
}

void Model::Initialize()
{
	MV1InitModel();
	m_models.clear();
	m_sprites.clear();
	currentBlendMode = BLEND_MODE::NoBlend;
}

void Model::ModelHandle::Load(const std::string& filename, bool async, bool collinfo, bool reference, std::function<void(int)> end)
{
	handle = MV1LoadModel((WorkFolder::Name + filename).c_str());
	endcallback = end;

	if (!async)
	{
		if (handle == -1)
			throw std::string(filename + "�̓ǂݍ��݂Ɏ��s���܂���\n");

		MV1SetMaterialDrawAlphaTestAll(handle, TRUE, DX_CMP_GREATER, param);

		if (collinfo)
		{
			DxLib::MV1SetupCollInfo(handle, 0);
		}

		if (reference)
		{
			DxLib::MV1SetupReferenceMesh(handle, 0, FALSE);
		}
	}
	else
	{
		isCol = collinfo;
		isRef = reference;
	}
}
void Model::ModelHandle::Draw()
{
	MV1DrawModel(handle);
}
void Model::ModelHandle::Delete()
{
	if (handle < 1)
	{
		MV1DeleteModel(handle);
		handle = 0;
	}
}
void Model::ModelHandle::Enable()
{
	if (!isInit)
	{
		MV1SetMaterialDrawAlphaTestAll(handle, TRUE, DX_CMP_GREATER, param);

		if (isCol)
		{
			DxLib::MV1SetupCollInfo(handle, 0);
		}
		if (isRef)
		{
			DxLib::MV1SetupReferenceMesh(handle, 0, FALSE);
		}

		if (endcallback != nullptr)
		{
			endcallback(handle);
		}
	}
}
bool Model::ModelHandle::CheckASync()
{
	return CheckHandleASyncLoad(handle) == FALSE;
}

Model::~Model()
{
	m_sprites.clear();
	m_models.clear();
	MV1InitModel();
}

// �R�c���f����ǂݍ��ށi�A�Z�b�g���j
void Model::Load(const std::string& filename, const MODEL_ID& id, bool async, int param, bool colinfo, bool reference, std::function<void(int)> end)
{
	auto model = std::make_shared<ModelHandle>(param);
	model->Load(filename, async, colinfo, reference, end);
	m_models[id] = model;
}

// �Q�c�摜��ǂݍ��ށi�A�Z�b�g���j
void Model::Load2D(const std::string& filename, const MODEL_ID& id)
{
	m_sprites[id].push_back(LoadGraph((WorkFolder::Name + filename).c_str()));
	if (m_sprites[id][0] == -1)
		throw std::string(id + "�̓ǂݍ��݂Ɏ��s���܂���\n");
}

// �����Q�c�摜�̓ǂݍ���(�A�Z�b�g���A�������A���Əc�̕������A1�R�}�̑傫��)
void Model::Load2D(const std::string& filename, const MODEL_ID& id, int allnum, const Point& splitnum, const Point& size)
{
	int* handle = new int[allnum];
	LoadDivGraph((WorkFolder::Name + filename).c_str(), allnum, splitnum.x, splitnum.y, size.x, size.y, handle);
	for (int i = 0; i < allnum; ++i)
	{
		m_sprites[id].emplace_back(handle[i]);
	}
	delete[] handle;
}

void Model::DeleteAll()
{
	std::unordered_map<MODEL_ID, HandlePtr>::iterator mitr = m_models.begin();
	while (mitr != m_models.end()) {
		MV1DeleteModel(mitr->first);
		++mitr;
	}
	m_models.clear();

	std::unordered_map<MODEL_ID, std::vector<int>>::iterator sitr = m_sprites.begin();
	while (sitr != m_sprites.end()) {
		DeleteGraph(sitr->first);
		++sitr;
	}
	m_sprites.clear();
}

void Model::Delete(const MODEL_ID& id)
{
	MV1DeleteModel(m_models.at(id)->GetHangle());
}

void Model::Draw(const MODEL_ID& id, const Vector3& position)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetOpacityRate(handle, alpha);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate, const Vector3& scale)
{
	rotate = rotate * PI / 180.0f;

 	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetScale(handle, VGet(scale.x, scale.y, scale.z));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetOpacityRate(handle, alpha);
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetOpacityRate(handle, alpha);
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetScale(handle, VGet(scale.x, scale.y, scale.z));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, const Color& diffusecolor)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, const Color& diffusecolor, const Color& specularcolor)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	auto specular = specularcolor * 255.0f;
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetSpcColorScale(handle, GetColorF(specular.r, specular.g, specular.b, specular.a));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale, const Color& diffusecolor, const Color& specularcolor)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();	
	auto diffuse = diffusecolor * 255.0f;
	auto specular = specularcolor * 255.0f;

	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetOpacityRate(handle, alpha);
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetScale(handle, VGet(scale.x, scale.y, scale.z));
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetSpcColorScale(handle, GetColorF(specular.r, specular.g, specular.b, specular.a));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetOpacityRate(handle, alpha);
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate, bool trans)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, Vector3 rotate, const Vector3& scale, bool trans)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetScale(handle, VGet(scale.x, scale.y, scale.z));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, bool trans)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetOpacityRate(handle, alpha);
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale, bool trans)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetOpacityRate(handle, alpha);
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetScale(handle, VGet(scale.x, scale.y, scale.z));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, const Color& diffusecolor, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, const Color& diffusecolor, const Color& specularcolor, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	auto specular = specularcolor * 255.0f;

	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetSpcColorScale(handle, GetColorF(specular.r, specular.g, specular.b, specular.a));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Vector3& position, float alpha, Vector3 rotate, const Vector3& scale, const Color& diffusecolor, const Color& specularcolor, bool trans)
{
	rotate = rotate * PI / 180.0f;

	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	auto specular = specularcolor * 255.0f;
	
	MV1SetPosition(handle, VGet(position.x, position.y, position.z));
	MV1SetRotationXYZ(handle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetScale(handle, VGet(scale.x, scale.y, scale.z));
	MV1SetOpacityRate(handle, alpha);
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetSpcColorScale(handle, GetColorF(specular.r, specular.g, specular.b, specular.a));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat, float alpha, const Color& diffusecolor, const Color& specularcolor, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	auto specular = specularcolor * 255.0f;

	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1SetOpacityRate(handle, alpha);
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetSpcColorScale(handle, GetColorF(specular.r, specular.g, specular.b, specular.a));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat, float alpha, const Color& diffusecolor, const Color& specularcolor)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	auto specular = specularcolor * 255.0f;
	
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1SetOpacityRate(handle, alpha);
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetSpcColorScale(handle, GetColorF(specular.r, specular.g, specular.b, specular.a));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat, float alpha, const Color& diffusecolor, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1SetOpacityRate(handle, alpha);
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat, float alpha, const Color& diffusecolor)
{
	auto handle = m_models.at(id)->GetHangle();
	auto diffuse = diffusecolor * 255.0f;
	
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1SetOpacityRate(handle, alpha);
	MV1SetDifColorScale(handle, GetColorF(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat, float alpha, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1SetOpacityRate(handle, alpha);
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat, float alpha)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1SetOpacityRate(handle, alpha);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat, bool trans)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1SetVisible(handle, trans);
	MV1DrawModel(handle);
}

void Model::Draw(const MODEL_ID& id, const Matrix& mat)
{
	auto handle = m_models.at(id)->GetHangle();
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1DrawModel(handle);
}

void Model::Draw(const int& handle, const Matrix& mat)
{
	MV1SetMatrix(handle, DXConverter::GetInstance().ToMATRIX(mat));
	MV1DrawModel(handle);
}

// �R�c��ԂɂQ�c�摜��`�悷��i�A�Z�b�g���A���W�A�\���R�}�ԍ��A���̃T�C�Y�j
void Model::Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), 0.5f, 0.5f, size, 0.0f, m_sprites[id][frame], true);
}

// �R�c��ԂɂQ�c�摜��`�悷��i�A�Z�b�g���A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�j
void Model::Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, 0.0f, m_sprites[id][frame], true);
}

// �R�c��ԂɂQ�c�摜��`�悷��i�A�Z�b�g���A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁj
void Model::Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], true);
}

// �R�c��ԂɂQ�c�摜��`�悷��i�A�Z�b�g���A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁA���ߓx�j
void Model::Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, float alpha)
{
	AlphaBlend(alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], true);
	DefaultBlend();
}

// �R�c��ԂɂQ�c�摜��`�悷��i�A�Z�b�g���A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁA���ߓx�A�`��t���O�j
void Model::Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, float alpha, bool trans)
{
	AlphaBlend(alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], trans);
	DefaultBlend();
}

// �R�c��ԂɂQ�c�摜��`�悷��i�A�Z�b�g���A���W�A�\���R�}�ԍ��A���̃T�C�Y�A���S���W�A��]�ʁA���ߓx�A�`��t���O�A���]�j
void Model::Draw2D(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, float alpha, bool trans, bool turn)
{
	AlphaBlend(alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], trans, turn);
	DefaultBlend();
}

void Model::Draw2DBlend(const MODEL_ID& id, const Vector3& position, float size, int blend_mode, int alpha)
{
	SetDrawBlendMode(blend_mode, alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), 0.5f, 0.5f, size, 0.0f, m_sprites[id][0], true);
	SetDrawBlendMode(BLEND_MODE::NoBlend, 0);
}

void Model::Draw2DBlend(const MODEL_ID& id, const Vector3& position, int frame, float size, int blend_mode, int alpha)
{
	SetDrawBlendMode(blend_mode, alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), 0.5f, 0.5f, size, 0.0f, m_sprites[id][frame], true);
	SetDrawBlendMode(BLEND_MODE::NoBlend, 0);
}

void Model::Draw2DBlend(const MODEL_ID& id, const Vector3& position, float size, const Vector2& origin, float angle, int blend_mode, int alpha)
{
	SetDrawBlendMode(blend_mode, alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][0], true);
	SetDrawBlendMode(BLEND_MODE::NoBlend, 0);
}
void Model::Draw2DBlend(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, int blend_mode, int alpha)
{
	SetDrawBlendMode(blend_mode, alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], true);
	SetDrawBlendMode(BLEND_MODE::NoBlend, 0);
}
void Model::Draw2DBlend(const MODEL_ID& id, const Vector3& position, float size, const Vector2& origin, float angle, bool turn, int blend_mode, int alpha)
{
	SetDrawBlendMode(blend_mode, alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][0], true, turn);
	SetDrawBlendMode(BLEND_MODE::NoBlend, 0);
}
void Model::Draw2DBlend(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, bool turn, int blend_mode, int alpha)
{
	SetDrawBlendMode(blend_mode, alpha);
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], true, turn);
	SetDrawBlendMode(BLEND_MODE::NoBlend, 0);
}


void Model::Draw2DBlendNoChange(const MODEL_ID& id, const Vector3& position, float size, int alpha)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), 0.5f, 0.5f, size, 0.0f, m_sprites[id][0], true);
}

void Model::Draw2DBlendNoChange(const MODEL_ID& id, const Vector3& position, int frame, float size, int alpha)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), 0.5f, 0.5f, size, 0.0f, m_sprites[id][frame], true);
}

void Model::Draw2DBlendNoChange(const MODEL_ID& id, const Vector3& position, float size, const Vector2& origin, float angle, int alpha)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][0], true);
}
void Model::Draw2DBlendNoChange(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, int alpha)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], true);
}
void Model::Draw2DBlendNoChange(const MODEL_ID& id, const Vector3& position, float size, const Vector2& origin, float angle, bool turn, int alpha)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][0], true, turn);
}
void Model::Draw2DBlendNoChange(const MODEL_ID& id, const Vector3& position, int frame, float size, const Vector2& origin, float angle, bool turn, int alpha)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id][frame], true, turn);
}


// ���f���n���h�����󂯎��
int Model::GetHandle(const MODEL_ID& id)
{
	return m_models.at(id)->GetHangle();
}

// �R�c���f���̕������Z���[�h���Z�b�g����
void Model::SetPhysics(int mode)
{
	MV1SetLoadModelUsePhysicsMode(mode);
}

// �t�@�C������'.'��������菜��
std::string Model::Split(std::string filename)
{
	std::string name;
	std::getline(
		std::stringstream(filename),
		name,
		'.'
		);
	return name;
}

// �摜�ɃA���t�@�u�����h�������{��
void Model::AlphaBlend(float alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0f * alpha));
}

// �摜�̃u�����h�������f�t�H���g�ɂ���
void Model::DefaultBlend()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool Model::CollisionLine(const MODEL_ID& id, const Vector3& start, const Vector3& end, Vector3* normal, Vector3* position)
{
	auto handle = m_models.at(id)->GetHangle();
	auto info = DxLib::MV1CollCheck_Line(handle, 0, VGet(start.x, start.y, start.z), VGet(end.x, end.y, end.z));

	if (info.HitFlag == TRUE)
	{
		if (normal != nullptr)
		{
			normal->x = info.Normal.x;
			normal->y = info.Normal.y;
			normal->z = info.Normal.z;
		}

		if (position != nullptr)
		{
			position->x = info.HitPosition.x;
			position->y = info.HitPosition.y;
			position->z = info.HitPosition.z;
		}
	}

	return info.HitFlag == TRUE;
}
bool Model::CollisionSphere(const MODEL_ID& id, const Vector3& center, float radius, Vector3* position, Vector3* normal)
{
	auto V = VGet(center.x, center.y, center.z);
	auto handle = m_models.at(id)->GetHangle();
	auto info = DxLib::MV1CollCheck_Sphere(handle, 0, V, radius);

	auto collide = info.HitNum > 0;

	if (collide)
	{
		if (info.HitNum == 1)
		{
			const auto& Dim = info.Dim[0];
			if (position != nullptr)
			{
				position->x = Dim.HitPosition.x;
				position->y = Dim.HitPosition.y;
				position->z = Dim.HitPosition.z;
			}
			if (normal != nullptr)
			{
				normal->x = Dim.Normal.x;
				normal->y = Dim.Normal.y;
				normal->z = Dim.Normal.z;
			}
		}
		else
		{
			for (auto i = 0; i < info.HitNum; ++i)
			{
				const auto& Dim = info.Dim[i];
				/* ���S�ʒu�A���Ԗ@�������߂� */
				if (i > 0)
				{
					if (position != nullptr)
					{
						*position += DXConverter::GetInstance().ToVector3(Dim.HitPosition);
						*position *= 0.5f;
					}
					if (normal != nullptr)
					{
						*normal += DXConverter::GetInstance().ToVector3(Dim.Normal);
						normal->Normalize();
					}
				}
				/* ������� */
				else
				{
					if (position != nullptr)
					{
						position->x = Dim.HitPosition.x;
						position->y = Dim.HitPosition.y;
						position->z = Dim.HitPosition.z;
					}
					if (normal != nullptr)
					{
						normal->x = Dim.Normal.x;
						normal->y = Dim.Normal.y;
						normal->z = Dim.Normal.z;
					}
				}
			}
		}
	}

	/* �j�� */
	DxLib::MV1CollResultPolyDimTerminate(info);

	return collide;
}
bool Model::RefreshInfo(const MODEL_ID& id, const Vector3& p, const Vector3& s)
{
	/* ���b�V���̏����X�V����i�����蔻��Ώۂ��ƁA��]�͂Ȃ��j */
	auto handle = m_models.at(id)->GetHangle();
	DxLib::MV1SetPosition(handle, VGet(p.x, p.y, p.z));
	DxLib::MV1SetScale(handle, VGet(s.x, s.y, s.z));
	/* �Փˏ��̍X�V */
	return DxLib::MV1RefreshCollInfo(handle, 0) == 0;
}

bool Model::CheckASyncModel()
{
	/* ���f�� */
	return std::all_of(m_models.begin(), m_models.end(),
		[] (const HandlePair& m)
	{
		/* �n���h���̔񓯊��ǂݍ��݂��������Ă��邩 */
		if (m.second->CheckASync())
		{
			/* �ǂݍ��݂��������Ă�����}�e���A���̃��e�X�g��L���ɂ��� */
			m.second->Enable();
			m.second->End();
			return true;
		}
		return false;
	});
}

bool Model::CheckASyncBillboard()
{
	/* �r���{�[�h */
	return std::all_of(m_sprites.begin(), m_sprites.end(),
		[] (const std::pair<MODEL_ID, std::vector<int>>& s)
	{
		return std::all_of(s.second.begin(), s.second.end(),
			[] (int handle)
		{
			return CheckHandleASyncLoad(handle) == FALSE;
		});
	});
}

bool Model::IsASyncLoad(const MODEL_ID& id)
{
	return m_models.at(id)->CheckASync();
}

int Model::GetCount()
{
	return static_cast<int>(m_models.size());
}

VECTOR Model::GetMin(const MODEL_ID& id, int index)
{
	return MV1GetMeshMinPosition(m_models.at(id)->GetHangle(), index);
}

VECTOR Model::GetMax(const MODEL_ID& id, int index)
{
	return MV1GetMeshMaxPosition(m_models.at(id)->GetHangle(), index);
}