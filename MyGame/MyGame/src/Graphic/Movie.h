#pragma once

#include <unordered_map>
#include <string>

class Movie
{
public:
	Movie() = default;
	~Movie() = default;

	///<summary>
	/// �����ǂݍ���
	///</summary>
	void Load(const std::string& filename);

	///<summary>
	/// ������Đ�����
	///</summary>
	void Play(const std::string& handle);

	///<summary>
	/// ������ꎞ��~����
	///</summary>
	void Stop(const std::string& handle);

	///<summary>
	/// ����̍Đ��ʒu��ύX����(/�b)
	///</summary>
	void Seek(const std::string& handle, float time);
	


	void Delete();
	///<summary>
	/// ����̌��݂̍Đ��ʒu���󂯎��(/�b)
	///</summary>
	float IsTime(const std::string& handle) const;

	///<summary>
	/// ���悪�Đ�����Ă��邩�ۂ��󂯎��
	///</summary>
	bool IsPlay(const std::string& handle) const;

	///<summary>
	/// �Đ���Ԃ̓����\������
	///</summary>
	void Draw() const;

private:
	///<summary>
	/// �t�@�C������'.'��������菜��
	///</summary>
	std::string Split(std::string filename);

	///<summary>
	/// �w�肵���n���h�����Z�b�g����Ă��Ȃ���΁A�X���[����
	///</summary>
	void IsGlow(const std::string& handle) const;

	std::unordered_map<std::string, int> m_movies;

};