#pragma once

#include "DxLib.h"

#include "ActorPtr.h"
#include"../Math/Math.h"
#include"Body\Base\IBodyPtr.h"
#include"Body\Base\DummyBody.h"
#include"../Judge/StepTimer.h"
#include"../Game/ID.h"
#include <string>
#include <memory>
#include <functional>
#include <forward_list>
#include <vector>
#include<list>
class IWorld;

class Actor:public std::enable_shared_from_this<Actor>{
public:
	// �R���X�g���N�^
	Actor(IWorld* world, const std::string& name, const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());
	// �R���X�g���N�^
	explicit Actor(const std::string& name = "none");
	// ���z�f�X�g���N�^
	virtual ~Actor() {}
	//������(�K�v�ȃL�����N�^�[�̂�override)
	virtual void initialize();
	void pause();
	void restart();
	virtual void onPause();
	virtual void onRestart();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �Փˏ���
	void collide(Actor& other);
	// �Փˎ��㏈��
	void collideResult();
	// ���S���Ă��邩�H
	bool isDead() const;
	// ���S����
	void dead();
	// ���O��Ԃ�
	const std::string& getName() const;
	// ���W��Ԃ�
	virtual Vector3& position();
	virtual Vector3 prevPosition();
	// ��]�s���Ԃ�
	Matrix& rotation();
	// �ϊ��s���Ԃ�
	Matrix getPose() const;
	// �q�̌���
	ActorPtr findCildren(const std::string& name);
	// �q�̌���
	ActorPtr findCildren(std::function<bool(const Actor&)> fn);
	// �q�̌����y�ђǉ�
	void findCildren(const std::string& name, std::list<ActorPtr>& actorList);
	// �q�̌����y�ђǉ�
	void findCildren(const std::string& name, std::list<std::weak_ptr<Actor>>& actorList);
	// �q�̒ǉ�
	void addChild(const ActorPtr& child);
	// �q������
	void eachChildren(std::function<void(Actor&)> fn);
	// �q������(const��)
	void eachChildren(std::function<void(const Actor&)> fn) const;
	// �q���폜����
	void removeChildren(std::function <bool(Actor&)> fn);
	// �q���폜����
	void removeChildren();
	// �q������
	void clearChildren();
	//�q�Ƃ̔���
	void collideChildren(Actor& other);
	//�q�̔���
	void collideSibling();
	// ���[�V�����̐ݒ�
	void setMotion(const int motion, const float speed);
	// World�̎擾
	IWorld* getWorld();
	// ���x��Ԃ�
	Vector3 velocity();
	//����̎擾
	IBodyPtr getBody();
	// ���ɏՓ˂�����
	bool isOnFloor() const;
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	//�ʒm����
	void receiveNotification(Notification start);

	int getCharacterNumber()const { return characterNumber_; }
	void setCharacterNumber(int num) { characterNumber_ = num; }
	// �R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;
protected:
	// �t�B�[���h�Ƃ̏Փ˔���(����Ɠ��������ꍇ��true��Ԃ�)
	virtual bool field(Vector3& result=Vector3());

protected:
	//�G�t�F�N�g�����ʒm�̏���
	virtual void CreateJustEffect();
	//�X�e�b�v����ʒm�̏���
	virtual void JustStep();

	// �ǂƂ̏Փ˔���
	bool wall_hit_check(Vector3& pos, std::vector<MV1_COLL_RESULT_POLY*> walls);
	// ���Ƃ̏Փ˔���
	bool floor_hit_check(Vector3& pos, std::vector<MV1_COLL_RESULT_POLY*> floors);
	// �J�v�Z���ƃ|���S���Ƃ̏Փ˔���
	bool hit_check_cap_tri(const Vector3& actor, const VECTOR poly[]);
	//���b�V���Ɛ����̓����蔻��
	bool hit_check_mesh_line(const Vector3& start, const Vector3& end, Vector3* point = nullptr, Vector3* normal = nullptr)const;
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);
	// �Փ˂�����
	virtual void onCollideResult();
	// �Փ˔���
	bool isCollide(Actor& other) const;

protected:
	//�L�����N�^�[���ʔԍ�
	int characterNumber_{ 0 };
	// ���[���h
	IWorld*	world_;
	// ���O
	std::string	name_;
	// ���W
	Vector3	position_;
	// ��]
	Matrix	rotation_;
	// �Փ˔���
	IBodyPtr body_;
	// ���S�t���O
	bool dead_;
	// ���f���n���h��
	MODEL_ID modelHandle_;
	// ���[�V����ID
	int	motionID_;
	// ���[�V�������x
	float motionSpeed_;
	// �ړ��O�̍��W
	Vector3	previousPosition_;
	// ���݂̍��W
	Vector3	currentPosition_;
	// �Փ˂����|���S���̐�
	int	hitNum_;
private:
	// �q�A�N�^�[
	std::forward_list<ActorPtr> children_;
};
