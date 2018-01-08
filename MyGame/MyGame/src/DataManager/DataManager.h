#pragma once
#include<list>
#include<map>
#include"../ScoreManager/ScoreData.h"
#include"../ShadowMap/ShadowMap_Data.h"
#include"../Game/ID.h"

class DataManager {
private:
	DataManager();
	~DataManager();

public:
	static DataManager& GetInstance() {
		static DataManager d;
		return d;
	}

	void setData(std::list<ScoreData*> list);
	std::list<ScoreData> getData() const;

	void setStage(int stage);
	int getStage()const;

	void setShadowData(const MODEL_ID& id,ShadowMap_Data& data);
	ShadowMap_Data getShadowData(const MODEL_ID& id);

	void setIsTutorial(bool flag);
	bool getIsTutorial() const;

private:
	std::list<ScoreData> datas_;
	std::map<MODEL_ID, ShadowMap_Data> shdowData_;

	//ステージ番号
	int chooseStage_{ 1 };

	//チュートリアルをしているか？
	bool is_Tutorial_{ true };
};