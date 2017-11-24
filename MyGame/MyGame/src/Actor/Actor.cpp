#include "Actor.h"
#include <algorithm>

#include "Body/Base/DummyBody.h"
#include "Body/Base/HitInfo.h"
#include "../World/IWorld.h"
#include"../Field/Field.h"

#include "../Define.h"

// �R���X�g���N�^
Actor::Actor(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body) :
	world_(world),
	name_(name),
	position_(position),
	rotation_(Matrix::Identity),
	body_(body),
	dead_(false),
	modelHandle_(MODEL_ID::DUMMY_MODEL),
	motionID_(-1),
	motionSpeed_(1.0f),
	hitNum_(0),
	previousPosition_(Vector3::Zero),
	currentPosition_(Vector3::Zero) {
}

// �R���X�g���N�^
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(Vector3::Zero),
	rotation_(Matrix::Identity),
	body_(std::make_shared<DummyBody>()),
	dead_(false),
	modelHandle_(MODEL_ID::DUMMY_MODEL),
	motionID_(-1),
	motionSpeed_(1.0f),
	hitNum_(0),
	previousPosition_(Vector3::Zero),
	currentPosition_(Vector3::Zero) {
}


void Actor::initialize()
{
}

// �X�V
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.update(deltaTime); });

	previousPosition_ = position_;
}

// �`��
void Actor::draw() const {
	onDraw();
	eachChildren([&](const Actor& child) { child.draw(); });
}


// �Փ˔���
void Actor::collide(Actor& other) {
	if (isCollide(other)) {
		onCollide(other);
		other.onCollide(*this);
	}
	eachChildren([&](Actor& child) { child.collide(other); });
}

void Actor::collideResult()
{
	onCollideResult();
	eachChildren([&](Actor& child) { child.collideResult(); });
}


// ���S���Ă��邩�H
bool Actor::isDead() const {
	return dead_;
}

// ���S����
void Actor::dead() {
	dead_ = true;
}

// ���O��Ԃ�
const std::string& Actor::getName() const {
	return name_;
}

// ���W��Ԃ�
Vector3& Actor::position() {
	return position_;
}

Vector3 Actor::prevPosition()
{
	return previousPosition_;
}

// ��]�s���Ԃ�
Matrix& Actor::rotation() {
	return rotation_;
}

// �ϊ��s���Ԃ�
Matrix Actor::getPose() const {
	return Matrix(rotation_).Translation(position_);
}

// �q�̌���
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// �q�̌���
ActorPtr Actor::findCildren(std::function<bool(const Actor&)> fn) {
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	return nullptr;
}

void Actor::findCildren(const std::string & name, std::list<ActorPtr>& actorList)
{
	for (auto& c : children_) {
		if (c->getName() == name) {
			actorList.push_back(c);
		}
	}
}
void Actor::findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	for (auto& c : children_) {
		if (c->getName() == name) {
			actorList.push_back(c);
		}
	}
}

// �q�̏Փ˔���
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
		other.eachChildren([&](Actor& target) { my.collide(target); });
	});
}

// �q�̏Փ˔���
void Actor::collideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->collide(*actor); });
	}
}

// �q�̒ǉ�
void Actor::addChild(const ActorPtr& child) {
	children_.push_front(child);
}

// �q������
void Actor::eachChildren(std::function<void(Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q������ (const�Łj
void Actor::eachChildren(std::function<void(const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q���폜
void Actor::removeChildren() {
	removeChildren([](Actor& child) { return child.isDead(); });
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// �q���폜
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

// �q������
void Actor::clearChildren() {
	children_.clear();
}

// ���[�V�����̐ݒ�
void Actor::setMotion(const int motion, const float speed) {
	motionID_ = motion;
	motionSpeed_ = speed;
}

// World�̎擾
IWorld* Actor::getWorld() {
	return world_;
}

// ����̌`�̎擾
IBodyPtr Actor::getBody() {
	return body_;
}

// ���x��Ԃ�
Vector3 Actor::velocity() {
	return position_ - previousPosition_;
}

// ���ɏՓ˂�����
bool Actor::isOnFloor() const {
	return hitNum_ > 0;
}

// ���b�Z�[�W����
void Actor::handleMessage(EventMessage message, void* param) {
	onMessage(message, param);
	eachChildren([&](Actor& child) { child.handleMessage(message, param); });
}

void Actor::receiveNotification(Notification start)
{
	switch (start)
	{
	case Notification::Call_CreateJustEffect: {
		CreateJustEffect();
		break;
	}
	case Notification::Call_JustStep: {
		JustStep();
		break;
	}
	default:
		break;
	}

}

// �t�B�[���h�Ƃ̏Փ˔���
bool Actor::field(Vector3& result) {
	Vector3 hitcenter;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), (VECTOR*)&hitcenter))
	{
		result = hitcenter;

		return true;
	}
	return false;
}

void Actor::CreateJustEffect()
{
}

void Actor::JustStep()
{
}

// �ǂƂ̏Փ˔���
bool Actor::wall_hit_check(Vector3 & pos, std::vector<MV1_COLL_RESULT_POLY*> walls) {
	// �Փ˃t���O
	bool hitFlag = false;

	// �ړ��x�N�g��
	Vector3 dir = currentPosition_ - previousPosition_;

	// �ړ��������ǂ����ŏ����𕪊�
	if (dir.Horizontal().Length() <= 0) return false;

	// �ǃ|���S���̐������J��Ԃ�
	for (int i = 0; i < walls.size(); i++) {
		// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
		if (!(hitFlag = hit_check_cap_tri(currentPosition_, walls[i]->Position))) continue;

		// �ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
		// �v���C���[���X���C�h������x�N�g��
		Vector3 polyNormal = Vector3::VECTORToVector3(walls[i]->Normal);

		// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
		Vector3 slideVec = Vector3::Cross(dir, polyNormal);

		// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
		// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
		slideVec = Vector3::Cross(polyNormal, slideVec);

		// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
		currentPosition_ = previousPosition_ + slideVec;

		// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
		for (int j = 0; j < walls.size(); j++) {
			// �������Ă����烋�[�v���甲����
			if (hit_check_cap_tri(currentPosition_, walls[j]->Position)) break;
		}
	}

	// �ǂɓ������Ă�����ǂ��牟���o���������s��
	if (!hitFlag) return false;

	// �ǃ|���S���̐������J��Ԃ�
	for (int i = 0; i < walls.size(); i++) {
		// �v���C���[�Ɠ������Ă��邩�𔻒�
		if (!hit_check_cap_tri(currentPosition_, walls[i]->Position)) continue;

		// �������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
		currentPosition_ = currentPosition_ + Vector3::VECTORToVector3(walls[i]->Normal);

		// �ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
		for (int j = 0; j < walls.size(); j++) {
			// �������Ă����烋�[�v�𔲂���
			if (hit_check_cap_tri(currentPosition_, walls[j]->Position)) break;
		}
	}

	return hitFlag;
}

// ���Ƃ̏Փ˔���
bool Actor::floor_hit_check(Vector3 & pos, std::vector<MV1_COLL_RESULT_POLY*> floors) {
	// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
	bool hitFlag = false;

	float MaxY = 0.0f;

	// ���|���S���̐������J��Ԃ�
	for (int i = 0; i < floors.size(); i++) {
		// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
		HITRESULT_LINE LineRes = HitCheck_Line_Triangle(Vector3::Vector3ToVECTOR(currentPosition_), Vector3::Vector3ToVECTOR(currentPosition_ + Vector3::Up * PERSON_HEIGHT), floors[i]->Position[0], floors[i]->Position[1], floors[i]->Position[2]);

		// �������Ă��Ȃ������牽�����Ȃ�
		if (LineRes.HitFlag == FALSE) continue;

		// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
		if (hitFlag && MaxY > LineRes.Position.y) continue;

		// �|���S���ɓ��������t���O�𗧂Ă�
		hitFlag = true;

		// �ڐG�����x���W��ۑ�����
		MaxY = LineRes.Position.y;
	}

	// ���|���S���ɓ����������ǂ����ŏ����𕪊�
	if (!hitFlag) return false;

	// �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
	currentPosition_.y = MaxY;

	return hitFlag;
}

// �J�v�Z���ƃ|���S���Ƃ̏Փ˔���
bool Actor::hit_check_cap_tri(const Vector3& actor, const VECTOR poly[]) {
	return HitCheck_Capsule_Triangle(Vector3::Vector3ToVECTOR(actor + body_->points(0)), Vector3::Vector3ToVECTOR(actor + body_->points(1)), body_->radius(), poly[0], poly[1], poly[2])==TRUE;
}

bool Actor::hit_check_mesh_line(const Vector3 & start, const Vector3 & end, Vector3 * point, Vector3 * normal) const
{
	//�������Ă��邩�𒲂ׂāA��_�Ɩ@����Ԃ�
	const auto coll_poly = MV1CollCheck_Line(world_->getField()->modelHandle(), 0, start, end);
	//��_�Ɩ@���f�[�^������
	if (coll_poly.HitFlag == TRUE) {
		if (point != nullptr) {
			*point = Vector3::VECTORToVector3(coll_poly.HitPosition);
		}
		if (normal != nullptr) {
			*normal = Vector3::VECTORToVector3(coll_poly.Normal);
		}
	}
	return coll_poly.HitFlag == TRUE;

}

// ���b�Z�[�W����
void Actor::onMessage(EventMessage, void*) {}

// �X�V
void Actor::onUpdate(float) {}

// �`��
void Actor::onDraw() const {
	body_->transform(getPose())->draw();
}

// �Փ˂���
void Actor::onCollide(Actor&) {}

void Actor::onCollideResult()
{
}

// �Փ˔���
bool Actor::isCollide(Actor& other) const {
	//getPose��ʂ��āA�����I�ɍ�������������
	return body_->transform(getPose())->isCollide(*other.getBody()->transform(other.getPose()).get(), HitInfo());
}
