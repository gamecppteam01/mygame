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
