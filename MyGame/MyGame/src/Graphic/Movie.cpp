#include "Movie.h"
#include <DxLib.h>
#include <sstream>
#include "../Define.h"

// �����ǂݍ���
void Movie::Load(const std::string& filename)
{
	std::string name = filename;
	int handle = OpenMovieToGraph(name.c_str());

	if (handle == -1)
		throw std::string(filename + "�Ƃ�������t�@�C���͑��݂��܂���");
	
	m_movies[Split(filename)] = handle;
}

// ������Đ�����
void Movie::Play(const std::string& handle)
{
	IsGlow(handle);

	PlayMovieToGraph(m_movies.at(handle));
}

// ������ꎞ��~����
void Movie::Stop(const std::string& handle)
{
	IsGlow(handle);

	PauseMovieToGraph(m_movies.at(handle));
}

// ����̍Đ��ʒu��ύX����(/�b)
void Movie::Seek(const std::string& handle, float time)
{
	IsGlow(handle);

	SeekMovieToGraph(m_movies.at(handle), static_cast<int>(time * 1000));
}

// ����̌��݂̍Đ��ʒu���󂯎��(/�b)
float Movie::IsTime(const std::string& handle) const
{
	IsGlow(handle);

	return TellMovieToGraph(m_movies.at(handle)) / 1000.0f;
}

// ���悪�Đ�����Ă��邩�ۂ��󂯎��
bool Movie::IsPlay(const std::string& handle) const
{
	IsGlow(handle);

	return GetMovieStateToGraph(m_movies.at(handle)) == 1;
}

// �Đ���Ԃ̓����\������
void Movie::Draw() const
{
	for (const auto& movie : m_movies)
	{
		if (IsPlay(movie.first))
		{
			DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, movie.second, FALSE);
		}
	}
}

// �t�@�C������'.'��������菜��
std::string Movie::Split(std::string filename)
{
	std::string assetname;
	std::getline(
		std::stringstream(filename),
		assetname,
		'.'
		);
	return assetname;
}

// �w�肵���n���h�����Z�b�g����Ă��Ȃ���΁A�X���[����
void Movie::IsGlow(const std::string& handle) const
{
	if (m_movies.find(handle) == m_movies.end())
		throw std::string(handle + "�Ƃ�������n���h���͓ǂݍ��܂�Ă��܂���");
}
void Movie::Delete()
{
	for (const auto& movie : m_movies)
	{
		DeleteGraph(movie.second);
	}
}