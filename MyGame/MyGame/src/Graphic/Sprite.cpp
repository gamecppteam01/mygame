#include "Sprite.h"
#include "../game/WorkFolder.h"
#include <Dxlib.h>
#include <sstream>
#include <string>
#include <iomanip>

#define PI 3.14159265358979

Sprite::~Sprite()
{
	InitGraph();
}

// ����������
void Sprite::Initialize()
{
	InitGraph();
	m_sprites.clear();
	m_splitsprites.clear();
	m_splitsizes_.clear();
}

// �ʏ�摜�̓ǂݍ���
void Sprite::Load(const std::string& filename, const SPRITE_ID& id)
{
	m_sprites[id] = LoadGraph((WorkFolder::Name + filename).c_str());
}

// �����摜�̓ǂݍ���
void Sprite::Load(const std::string& filename, const SPRITE_ID& id, int allnum, const Point& splitnum, const Point& size)
{
	m_splitsizes_[id] = size;
	int* handle = new int[allnum];
	LoadDivGraph((WorkFolder::Name + filename).c_str(), allnum, splitnum.x, splitnum.y, size.x, size.y, handle);
	for (int i = 0; i < allnum; ++i)
	{
		m_splitsprites[id].emplace_back(handle[i]);
	}
	delete[] handle;
}

void Sprite::DeleteAll()
{
	std::unordered_map<SPRITE_ID, int>::iterator spritr = m_sprites.begin();
	while (spritr != m_sprites.end()) {
		DeleteGraph(spritr->first);
		++spritr;
	}
	m_sprites.clear();
	m_splitsprites.clear();
	m_splitsizes_.clear();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W)
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position)
{
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0f, 1.0f, 0.0, m_sprites[id], true, false);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l)
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, float alpha = 1.0f)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0f, 1.0f, 0.0, m_sprites[id], true, false);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦)
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[id], true, false);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦)
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[id], true, false);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_sprites[id], true, false);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_sprites[id], true, false);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���߁A���]) 
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, bool trans = true, bool turn = false)
{
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_sprites[id], trans, turn);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l�A���߁A���])
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, float alpha = 1.0f, bool trans = true, bool turn = false)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_sprites[id], trans, turn);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A���߁A���])
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[id], trans, turn);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[id], trans, turn);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]���A���߁A���])
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_sprites[id], trans, turn);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_sprites[id], trans, turn);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const Point& size, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	int handle = DerivationGraph(0, 0, size.x, size.y, m_sprites[id]);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, handle, trans, turn);
	DeleteGraph(handle);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::Draw(const SPRITE_ID& id, const Vector2& position, const RECT& rect, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	int handle = DerivationGraph(rect.left, rect.top, rect.right - rect.left, rect.bottom, m_sprites[id]);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, handle, trans, turn);
	DeleteGraph(handle);
	DefaultBlend();
}

void Sprite::DrawBlend(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle, const int& blendmode)
{
	SetDrawBlendMode(blendmode, 255);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_sprites[id], true, false);
	SetDrawBlendMode(BLEND_MODE::NoBlend, 255);
}

// �����摜�̕`��(�A�Z�b�g���A���W)
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame)
{
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[id][frame], true, false);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l)
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, float alpha = 1.0f)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[id][frame], true, false);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦)
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[id][frame], true, false);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦)
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[id][frame], true, false);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_splitsprites[id][frame], true, false);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_splitsprites[id][frame], true, false);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���߁A���]) 
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, bool trans = true, bool turn = false)
{
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[id][frame], trans, turn);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l�A���߁A���])
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, float alpha = 1.0f, bool trans = true, bool turn = false)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[id][frame], trans, turn);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A���߁A���])
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[id][frame], trans, turn);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[id][frame], trans, turn);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]���A���߁A���])
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_splitsprites[id][frame], trans, turn);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_splitsprites[id][frame], trans, turn);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Point& size, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	/*Point graphsize;
	GetGraphSize(m_splitsprites[id][frame], &graphsize.x, &graphsize.y);*/
	int handle = DerivationGraph(0, 0, size.x, size.y, m_splitsprites[id][frame]);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, handle, trans, turn);
	DeleteGraph(handle);
	DefaultBlend();
}

// �w��̌��Ԗڂ̕\���R�}�ԍ����擾����i�����A�~�������Ԗڂ̕\���R�}�ԍ��A�ő包���j
int Sprite::NumberFrame(int number, int digit, int maxdigit)
{
	// �T���ɑ�����string�^�ɕϊ�
	std::ostringstream ost;
	ost << std::setfill('0') << std::setw(maxdigit) << number;
	const std::string& str = ost.str();

	std::vector<char> score;
	score.clear();

	// �P��������vector�Ɋi�[
	for (auto& s : str)
	{
		score.push_back(s);
	}

	// �ݒ肳�ꂽ���Ԗڂɂ���X�R�A���Z�b�g����
	return score[maxdigit - digit] - '0';
}

int Sprite::GetHandle(const SPRITE_ID & id) const
{
	return m_sprites.at(id);
}

int Sprite::GetHandle(const SPRITE_ID & id, int frame) const
{
	return m_splitsprites.at(id).at(frame);
}

// �t�@�C������'.'��������菜��
std::string Sprite::Split(std::string filename)
{
	std::string id;
	std::getline(
		std::stringstream(filename),
		id,
		'.'
	);
	return id;
}

// �摜�ɃA���t�@�u�����h�������{��
void Sprite::AlphaBlend(float alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0f * alpha));
}

// �摜�̃u�����h�������f�t�H���g�ɂ���
void Sprite::DefaultBlend()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool Sprite::IsASyncLoad(const SPRITE_ID& id)
{
	return CheckHandleASyncLoad(m_sprites[id]) == FALSE;
}