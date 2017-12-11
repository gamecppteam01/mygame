#include "UIManager.h"
#include"UI.h"
#include<algorithm>

//コンストラクタ
UIManager::UIManager()
{
	initialize();
}

UIManager::~UIManager()
{
	UIs_.clear();
}

void UIManager::pause()
{
	for (auto& u : UIs_) {
		u->pause();
	}
}

void UIManager::restart()
{
	for (auto& u : UIs_) {
		u->restart();
	}
}

//初期化
void UIManager::initialize()
{
	UIs_.clear();
}

//更新
void UIManager::update(float deltaTime)
{
	int size = UIs_.size();
	for (int i = 0; i < size;i++) {
		UIs_.at(i)->update(deltaTime);
	}

	std::vector<UIPtr>::iterator iter = std::remove_if(UIs_.begin(), UIs_.end(), [](UIPtr ui) {return ui->isEnd(); });
	UIs_.erase(iter, UIs_.end());


}

//描画
void UIManager::draw() const
{
	for (auto& ui : UIs_) {
		ui->draw();
	}
}

//検索
UIPtr UIManager::find(const std::string & name)
{
	//名前が一致する要素が存在すればそれをreturn
	for (auto& ui : UIs_) {
		if (ui->getName()==name)return ui;
	}
	//いなかったらnullをreturn
	return nullptr;
}

//追加
void UIManager::add(const UIPtr & uiptr)
{
	UIs_.push_back(uiptr);
	uiptr->initialize();
}
