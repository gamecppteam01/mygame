#pragma once
#include <vector>
#include "UI.h"
#include "UIPtr.h"

class UIManager {
public:
	//コンストラクタ
	UIManager();
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//描画
	void draw() const;
	//検索
	void find(const std::string& name);
	//追加
	void add(const UIPtr& uiptr);

private:
	
	std::vector<UIPtr> UIs_;
};