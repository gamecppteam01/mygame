#pragma once
#include"../../Graphic/Movie.h"
#include<map>
class TutorialMovie {
public:
	TutorialMovie() = default;
	~TutorialMovie();
	//初期化時にクォータの動画を入れてる
	void initialize();
	void update(float deltaTime);
	//動画の表示
	void draw(const Vector2 position) const;
	//出すMovieの指定
	void Change_Movie(MOVIE_ID ID);
	//Movieの再生
	void PlayMovie();
	//Movieの停止
	void StopMovie();
	//Movieの表示
	void Display_Movie();
	//Movieの非表示
	void Hidden_Movie();
private:
	std::vector<MOVIE_ID> Movie_ID;
	bool play_movie;
	float scale;
	Vector2 move;
	Vector2 movie_half_size;
};