#include "TutorialMovie.h"
#include "../../Math/Math.h"
TutorialMovie::~TutorialMovie(){
	Movie::GetInstance().Clear();
}

void TutorialMovie::initialize(){
	Movie_ID.push_back(MOVIE_ID::QUARTER);
	play_movie = false;
	pause = false;
	scale = 0.0f;
	alpha = 0.0f;
	move = Vector2::Zero;
	movie_half_size = Vector2::Zero;
}

void TutorialMovie::update(float deltaTime){
	if (!Movie::GetInstance().IsPlay(Movie_ID.front())&&!pause) {
		Movie::GetInstance().Seek(Movie_ID.front(), 0.0f);
		Movie::GetInstance().Play(Movie_ID.front());
	}
	if (play_movie) {
			scale += 0.02;
			if (scale >= 0.5f) {
				scale = 0.5f;
			}
	}
	else{
		scale -= 0.02;
		if (scale <= 0.0f) {
			scale = 0.0f;
		}
	}
}
void TutorialMovie::draw(const Vector2 position) const{
	//if (play_movie) {
	Movie::GetInstance().Draw(Movie_ID.front(), Vector2(position.x, position.y), scale,0.0);
	Sprite::GetInstance().Draw(SPRITE_ID::MOVIE_FRAME, Vector2(position.x,position.y),Sprite::GetInstance().GetSize(SPRITE_ID::MOVIE_FRAME)/2,1.0f,Vector2(scale,scale),0.0f);
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

void TutorialMovie::Pause()
{
	pause = true;
	StopMovie();
}

void TutorialMovie::Start()
{
	PlayMovie();
	pause = false;
}
