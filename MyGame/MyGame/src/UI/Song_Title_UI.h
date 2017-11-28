#pragma once

#include"UI.h"
#include<map>
#include<string>

class Song_Title_UI : public UI {
public:
	//コンストラクタ
	Song_Title_UI(int soundhandle);
	//初期化
	virtual void initialize() override;
	//更新
	virtual void update(float deltaTime) override;
	//描画
	virtual void draw() const override;

private:
	void createSongList();

private:
	//曲名リスト
	std::map<int, std::string> songMap_;
	//曲ハンドル
	int soundhandle_;
};
