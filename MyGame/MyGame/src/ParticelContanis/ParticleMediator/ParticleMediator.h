#pragma once

#include<string> 

#include"../ParticlePtr/ParticlePtr.h"

class Particle;

//パーティクル仲介者クラス
class ParticleMediator {
public:
	//パーティクルを生成する
	virtual ParticlePtr generate(const std::string& name) = 0;

protected:
	//デストラクタ(インターフェイスのユーザーからデストラクタを禁止)
	~ParticleMediator(){}
};
