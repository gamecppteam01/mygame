#include "DataManager.h"

DataManager::DataManager()
{
	setShadowData(MODEL_ID::DUMMY_MODEL, ShadowMap_Data(SHADOW_MAP_ID::SHADOW_MAP_DAMY, Point(0,0), Vector3(0,0,0), Vector3(0,0,0), Vector3(0,0,0), 0));
}

DataManager::~DataManager(){
	datas_.clear();
}

void DataManager::setData(std::list<ScoreData*> list){
	datas_.clear();
	for (auto& d:list)
	{
		datas_.push_back(*d);
	}
}

std::list<ScoreData> DataManager::getData() const
{
	return datas_;
}

void DataManager::setStage(int stage)
{
	chooseStage_ = stage;
}

int DataManager::getStage() const
{
	return chooseStage_;
}

void DataManager::setShadowData(const MODEL_ID& id,ShadowMap_Data & data){
	shdowData_[id] = data;
}

ShadowMap_Data DataManager::getShadowData(const MODEL_ID& id)
{
	return shdowData_[id];
}

void DataManager::setIsTutorial(bool flag){
	is_Tutorial_ = flag;
}

bool DataManager::getIsTutorial() const{
	return is_Tutorial_;
}

void DataManager::setCount(int count)
{
	count_ = count;
}

int DataManager::getCount() const
{
	return count_;
}

void DataManager::setMenName(const std::string & men_name, int size)
{
	player_name.menSize = size;
	player_name.men_name = men_name;
}

void DataManager::setWoMenName(const std::string & women_name, int size)
{
	player_name.womenSize = size;
	player_name.women_name = women_name;

}

void DataManager::ResetName()
{
	player_name.menSize = 0;
	player_name.womenSize = 0;
	player_name.men_name = "";
	player_name.women_name = "";
}

Player_Name DataManager::getName() const
{
	return player_name;
}
