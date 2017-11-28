#include "DataManager.h"

DataManager::~DataManager(){
	datas_.clear();
}

void DataManager::setData(std::list<ScoreData>& list){
	datas_.clear();
	datas_ = list;
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
