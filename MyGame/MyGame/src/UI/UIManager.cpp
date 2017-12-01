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

//初期化
void UIManager::initialize()
{
	UIs_.clear();
}

//更新
void UIManager::update(float deltaTime)
{
	for (auto& ui : UIs_) {
		ui->update(deltaTime);
	}


	std::vector <UIPtr>::iterator iter = UIs_.begin();
	while (iter != UIs_.end()) {
		if (iter->get()->isEnd()) {
			iter = UIs_.erase(iter);
		}
		else {
			++iter;
		}
	}
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
