#pragma once
#include"../../Graphic/Movie.h"
#include<map>
class TutorialMovie {
public:
	TutorialMovie() = default;
	~TutorialMovie();
	//���������ɃN�H�[�^�̓�������Ă�
	void initialize();
	void update(float deltaTime);
	//����̕\��
	void draw(const Vector2 position) const;
	//�o��Movie�̎w��
	void Change_Movie(MOVIE_ID ID);
	//Movie�̍Đ�
	void PlayMovie();
	//Movie�̒�~
	void StopMovie();
	//Movie�̕\��
	void Display_Movie();
	//Movie�̔�\��
	void Hidden_Movie();
private:
	std::vector<MOVIE_ID> Movie_ID;
	bool play_movie;
	float scale;
	Vector2 move;
	Vector2 movie_half_size;
};