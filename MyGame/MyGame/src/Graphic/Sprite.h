#pragma once

#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../game/ID.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "BlendMode.h"


class Sprite
{
private:
	Sprite() = default;
	~Sprite();
public:
	static Sprite &GetInstance(){
		static Sprite s;
		return s;
	}

	///<summary>
	/// ����������
	///</summary>
	void Initialize();

	///<summary>
	/// �ʏ�摜�̓ǂݍ���(�A�Z�b�g���AID�̎w��)
	///</summary>
	void Load(const std::string& filename, const SPRITE_ID& id);
	///<summary>
	/// �����摜�̓ǂݍ���(�A�Z�b�g���AID�̎w��A�������A���Əc�̕������A1�R�}�̑傫��)
	///</summary>
	void Load(const std::string& filename, const SPRITE_ID& id, int allnum, const Point& splitnum, const Point& size);
	///<summary>
	/// �ǂݍ��񂾉摜�����ׂč폜����
	///</summary>
	void DeleteAll();
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W)
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l)
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, float alpha);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦)
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, const Vector2& scale);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦)
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]��)
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l�A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, float alpha, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const Point& size, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void Draw(const SPRITE_ID& id, const Vector2& position, const RECT& rect, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>

	///<summary>
	/// �u�����h�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]���A�u�����h���[�h)
	///</summary>
	void DrawBlend(const SPRITE_ID& id, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle, const int& blendmode);

	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ�)
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�A���t�@�l)
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, float alpha);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦)
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦)
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦�A��]��)
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, float angle);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦�A��]��)
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, float angle);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���߁A���])
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�A���t�@�l�A���߁A���])
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, float alpha, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦�A���߁A���])
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void SplitDraw(const SPRITE_ID& id, const Vector2& position, int frame, const Point& size, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);

	///<summary>
	/// �w��̌��Ԗڂ̕\���R�}�ԍ����擾����i�����A�~�������Ԗڂ̕\���R�}�ԍ��A�ő包���j
	///</summary>
	static int NumberFrame(int number, int digit, int maxdigit);

	bool IsASyncLoad(const SPRITE_ID& id);

	int GetCount()
	{
		return static_cast<int>(m_sprites.size());
	}

	///<summary>
	/// �摜�̃T�C�Y���擾����
	///</summary>
	Point GetSize(const SPRITE_ID& id) const
	{
		Point size;
		GetGraphSize(m_sprites.at(id), &size.x, &size.y);
		return size;
	}
	Point GetSplitPieceSize(const SPRITE_ID& id) const
	{
		return m_splitsizes_.at(id);
	}
	int GetSliptFrameSize(const SPRITE_ID& id)const {
		if (m_splitsprites.find(id) == m_splitsprites.end())return 0;
		return m_splitsprites.at(id).size();
	}
	int GetHandle(const SPRITE_ID& id) const;
	int GetHandle(const SPRITE_ID& id,int frame) const;

private:
	///<summary>
	/// �t�@�C������'.'��������菜��
	///</summary>
	std::string Split(std::string filename);
	///<summary>
	/// �摜�ɃA���t�@�u�����h�������{��
	///</summary>
	void AlphaBlend(float alpha);
	///<summary>
	/// �摜�̃u�����h�������f�t�H���g�ɂ���
	///</summary>
	void DefaultBlend();

private:
	// �ʏ�摜
	std::unordered_map<SPRITE_ID, int> m_sprites;
	// �����摜
	std::unordered_map<SPRITE_ID, std::vector<int>> m_splitsprites;
	std::unordered_map<SPRITE_ID, Point> m_splitsizes_;
};