#pragma once
#include<list>
#include<map>
#include"../ScoreManager/ScoreData.h"
#include"../ShadowMap/ShadowMap_Data.h"
#include"../Game/ID.h"

struct Player_Name
{
	Player_Name() {

	}
	std::string men_name{""};
	std::string women_name{""};
	int menSize{ 0 };
	int womenSize{ 0 };
};
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

	void setCount(int count);
	int getCount() const;

	void setMenName(const std::string& men_name, int size);
	void setWoMenName(const std::string& women_name,int size);

	void ResetName();

	Player_Name getName()const;
private:
	std::list<ScoreData> datas_;
	std::map<MODEL_ID, ShadowMap_Data> shdowData_;

	//ステージ番号
	int chooseStage_{ 1 };

	//チュートリアルをしているか？
	bool is_Tutorial_{ true };

	//スポットライト内にいる数
	int count_;

	Player_Name player_name{ };

};