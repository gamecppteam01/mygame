#include "TutorialMovie.h"
#include "../../Math/Math.h"
TutorialMovie::~TutorialMovie(){
	Movie::GetInstance().Clear();
}

void TutorialMovie::initialize(){
	Movie_ID.push_back(MOVIE_ID::QUARTER);
	play_movie = false;
	scale = 0.0f;
	move = Vector2::Zero;
	movie_half_size = Vector2::Zero;
}

void TutorialMovie::update(float deltaTime){
	if (!Movie::GetInstance().IsPlay(Movie_ID.front())) {
		Movie::GetInstance().Seek(Movie_ID.front(), 0.0f);
		Movie::GetInstance().Play(Movie_ID.front());
	}
	if (play_movie) {
		scale += 0.02;
		if (scale >= 0.5f) {
			scale = 0.5f;
		}
		move.x += 4;
		move.y += 3;
		movie_half_size = Movie::GetInstance().GetMovieSize(Movie_ID.front()) * 0.5;
		if (move.x >= movie_half_size.x / MathHelper::Pi) {
			move.x = movie_half_size.x / MathHelper::Pi;
		}
		if (move.y >= movie_half_size.y / MathHelper::Pi) {
			move.y = movie_half_size.y / MathHelper::Pi;
		}
	}
	else{
		scale -= 0.02;
		if (scale <= 0.0f) {
			scale = 0.0f;
		}
		move.x -= 4;
		move.y -= 3;
		if (scale <= 0.0f) {
			move.x = 0.0;
		}
		if (scale <= 0.0f) {
			move.y = 0.0;
		}
	}
}
void TutorialMovie::draw(const Vector2 position) const{
	//if (play_movie) {
	Movie::GetInstance().Draw(Movie_ID.front(), Vector2(position.x - move.x, position.y - move.y), scale);
	//}
}

void TutorialMovie::Change_Movie(MOVIE_ID ID){
	Movie_ID.clear();
	Movie_ID.push_back(ID);
}

void TutorialMovie::PlayMovie(){
	Movie::GetInstance().Play(Movie_ID.front());
}

void TutorialMovie::StopMovie(){
	Movie::GetInstance().Stop(Movie_ID.front());
}

void TutorialMovie::Display_Movie(){
	PlayMovie();
	play_movie = true;	
}

void TutorialMovie::Hidden_Movie(){
	play_movie = false;
	StopMovie();
}
