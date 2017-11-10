#include "ActorManager.h"
#include"ActorGroup.h"
// コンストラクタ
ActorManager::ActorManager() {
	initialize();
}

// 初期化
void ActorManager::initialize() {
	// アクターグループの登録
	actors_[ActorGroup::NPC] = std::make_shared<Actor>();
	actors_[ActorGroup::PLAYER] = std::make_shared<Actor>();
	actors_[ActorGroup::PLAYER_BULLET] = std::make_shared<Actor>();
	actors_[ActorGroup::ENEMY] = std::make_shared<Actor>();
	actors_[ActorGroup::ENEMY_BULLET] = std::make_shared<Actor>();
	actors_[ActorGroup::EFFECT] = std::make_shared<Actor>();
	actors_[ActorGroup::DUMMYACTOR] = std::make_shared<Actor>();
	root_.clearChildren();
	root_.addChild(actors_[ActorGroup::NPC]);
	root_.addChild(actors_[ActorGroup::PLAYER]);
	root_.addChild(actors_[ActorGroup::PLAYER_BULLET]);
	root_.addChild(actors_[ActorGroup::ENEMY]);
	root_.addChild(actors_[ActorGroup::ENEMY_BULLET]);
	root_.addChild(actors_[ActorGroup::EFFECT]);
	root_.addChild(actors_[ActorGroup::DUMMYACTOR]);

	countList_ = 0;
}

// 更新
void ActorManager::update(float deltaTime) {
	root_.update(deltaTime);
	collide();
	root_.collideResult();
	root_.removeChildren();
}

// 描画
void ActorManager::draw() const {
	root_.draw();
}

// アクターの追加
void ActorManager::addActor(ActorGroup group, const ActorPtr& actor) {
	actor->setCharacterNumber(countList_);
	countList_++;
	actors_[group]->addChild(actor);
}

// アクターの検索
ActorPtr ActorManager::findActor(const std::string& name) {
	return root_.findCildren(name);
}

void ActorManager::findActor(const std::string & name, std::list<ActorPtr>& actorList)
{
	for (auto& act : actors_) {
		act.second->findCildren(name, actorList);
	}
}
void ActorManager::findActor(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	for (auto& act : actors_) {
		act.second->findCildren(name, actorList);
	}
}

// メッセージ処理
void ActorManager::handleMessage(EventMessage message, void* param) {
	root_.handleMessage(message, param);
}

// 衝突判定
void ActorManager::collide() {
	// 衝突するグループの指定
	//actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy]);
	actors_[ActorGroup::PLAYER]->collideChildren(*actors_[ActorGroup::ENEMY]);
	actors_[ActorGroup::PLAYER_BULLET]->collideChildren(*actors_[ActorGroup::ENEMY]);
	actors_[ActorGroup::PLAYER]->collideChildren(*actors_[ActorGroup::ENEMY_BULLET]);
	actors_[ActorGroup::PLAYER_BULLET]->collideChildren(*actors_[ActorGroup::ENEMY_BULLET]);
	actors_[ActorGroup::PLAYER]->collideChildren(*actors_[ActorGroup::PLAYER_BULLET]);
	actors_[ActorGroup::ENEMY]->collideChildren(*actors_[ActorGroup::ENEMY]);
	actors_[ActorGroup::ENEMY]->collideChildren(*actors_[ActorGroup::ENEMY_BULLET]);
	actors_[ActorGroup::ENEMY_BULLET]->collideChildren(*actors_[ActorGroup::ENEMY_BULLET]);


}
