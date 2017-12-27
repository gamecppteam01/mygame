#pragma once
#include<functional>
#include<list>
#include<algorithm>

class MethodExecutor {
public:
	MethodExecutor() {

	}
	~MethodExecutor() {
		func_.clear();
	}
	void initialize() {
		func_.clear();
	}
	void set(std::function<bool()> func) {
		func_.emplace_back(func, false);
	}
	void update() {
		std::for_each(func_.begin(), func_.end(), [](auto& f) {f.second = f.first(); });
		func_.remove_if([](auto& f) {return f.second; });
	}

private:
	std::list<std::pair<std::function<bool()>,bool>> func_;
	
};