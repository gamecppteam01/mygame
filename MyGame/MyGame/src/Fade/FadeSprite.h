#pragma once
#include<functional>

class FadeSprite {
private:
	enum State {
		In,
		Out,
		Stop
	};
public:
	FadeSprite();
	~FadeSprite();

	void start();
	void update(float deltaTime);
	void draw()const;
	bool isActive()const;
	
	void addCallBack(std::function<void()> func);

	void in(float deltaTime);
	void stop(float deltaTime);
	void out(float deltaTime);
private:
	float timer_;
	int state_;
	float fadeTimer_;
	bool isActive_;
	std::function<void()> function_;
};