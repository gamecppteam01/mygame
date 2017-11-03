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
