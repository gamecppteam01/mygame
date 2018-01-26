#include "AvoidSearch.h"
#include"../../../World/IWorld.h"
#include"../../../Field/FieldGrid.h"
#include<algorithm>
#include"../../../Define.h"
#include"../../../Math/Random.h"

static const float centerScore = 1.0f;
static const float sideRate = 0.8f;
Vector3 AvoidSearch::Search(IWorld* world, Vector3 position, const std::list<Vector3>& target,Vector3 finalPosition, Point& prevPoint,Point* pointptr, std::list<TestDP>* dp)
{
	//�Ώۂ̈ʒu
	Point point = world->getGrid().getGridNum(position);

	//DebugDraw::DebugDrawFormatString(500, 400, GetColor(255, 0, 0), "%d:%d", point.x, point.y);	
	//DebugDraw::DebugDrawFormatString(500, 500, GetColor(255, 0, 0), "%f:%f:%f", chip.position.x, chip.position.y, chip.position.z);

	std::vector<FieldChip> chips;
	Point rounds[8]{
		{0,-1},//0
		{1,-1},//45
		{1,0},//90
		{1,1},//135
		{0,1},//180
		{-1,1},//225
		{-1,0},//270
		{-1,-1}//315
	};
	bool isIn = false;//�`�b�v�����邩
	//����8�}�X������Ă���
	for (int i = 0; i < 8; i++) {
		auto chip = world->getGrid().getGridChip(point + rounds[i], &isIn);
		//if (!isIn)continue;
		if (chip.point == prevPoint)chip.score += 5.0f;
		chips.push_back(chip);
	}
	
	for (auto t : target) {
		auto ftoTargetVector = t - position;//���g���瑊���
		auto fangle = Vector3::Angle(Vector3::Forward, ftoTargetVector);
		auto fisLeftVector = Vector3::Cross(Vector3::Forward, ftoTargetVector);
		if (fisLeftVector.y < 0.0f)fangle = 360.0f - fangle;

		auto aresult = SearchAngleNum(fangle);
		chips[aresult].score += centerScore;//�������̂���
		chips[(aresult + 4 + 8) % 8].score += centerScore*std::powf(sideRate, 4);//�t��
		for (int i = 0; i < 3; i++) {
			int key = (aresult - i - 1 + 8) % 8;
			chips[key].score += centerScore*std::powf(sideRate, i + 1);
			key = (aresult + i + 1 + 8) % 8;
			chips[key].score += centerScore*std::powf(sideRate, i + 1);
		}
	}

	//�ړI�n�ւ̃R�X�g��������
	auto toTargetVector = finalPosition - position;//���g���瑊���
	auto angle = Vector3::Angle(Vector3::Forward, toTargetVector);
	auto isLeftVector = Vector3::Cross(Vector3::Forward, toTargetVector);
	if (isLeftVector.y < 0.0f)angle = 360.0f - angle;

	auto result = SearchAngleNum(angle);
	float mulCount = 2.0f;
	auto dist = Vector3::Distance(position, finalPosition);
	if (dist <= 0.0f)dist = 1.0f;
	auto fieldlength = world->getGrid().getFieldSize().Length();
	auto fdivd = fieldlength / dist;
	fdivd = fdivd*0.5f*target.size();
	if (dp != nullptr)dp->emplace_back(Vector2{ 200.f,400.f }, fdivd);

	chips[result].score -= fdivd;//�������̂���
	chips[(result + 1 + 8) % 8].score -= fdivd*0.9f;//�������̂���
	chips[(result - 1 + 8) % 8].score -= fdivd*0.9f;//�������̂���
	chips[(result + 2 + 8) % 8].score -= fdivd*0.1f;//�������̂���
	chips[(result - 2 + 8) % 8].score -= fdivd*0.1f;//�������̂���

	//�P�c���ɂ͍s���Â炭����
	//chips[(result + 4 + 8) % 8].score *= mulCount * 4;//�t��
	//for (int i = 1; i < 3; i++) {
	//	int key = (result - i - 1 + 8) % 8;
	//	chips[key].score *= mulCount*i;
	//	key = (result + i + 1 + 8) % 8;
	//	chips[key].score *= mulCount*i;
	//}
	//chips[result].score /= divCount;//�������̂���
	//chips[(result + 4 + 8) % 8].score /= divCount*std::powf(1.0f-sideRate, 4);//�t��
	//for (int i = 1; i < 3; i++) {
	//	int key = (result - i - 1 + 8) % 8;
	//	chips[key].score /= divCount*std::powf(1.0f - sideRate, i + 1);
	//	key = (result + i + 1 + 8) % 8;
	//	chips[key].score /= divCount*std::powf(1.0f - sideRate, i + 1);
	//}
	auto prev_to_Vector = position - world->getGrid().getGridChip(prevPoint).position;//�O���獡��
	auto isLeft_prev_to_Vector = Vector3::Cross(prev_to_Vector, toTargetVector);
	bool isLeft = false;
	if (isLeft_prev_to_Vector.y > 0.0f)isLeft = true;

	float angleAddScore = 0.5f*target.size();
	chips[result].score -= angleAddScore;//�������̂���
	if (isLeft) {
		chips[(result - 1 + 8) % 8].score -= angleAddScore;//�������̂���
	}
	else {
		chips[(result + 1 + 8) % 8].score -= angleAddScore;//�������̂���
	}

	if (dp != nullptr) {
		int i = 0;
		for (auto c : chips) {
			Vector3 dangle = Vector3::Backward*Matrix::CreateRotationY(-i*45.0f);
			Vector2 drawpos = SCREEN_SIZE*0.5f + Vector2{ dangle.x,dangle.z }*150.0f;
			DebugDraw::DebugDrawFormatString(drawpos.x, drawpos.y, GetColor(255, 0, 0), "%f", c.score);
			dp->push_back(TestDP{ drawpos,c.score });
			i++;
		}
	}
	auto itr = std::remove_if(chips.begin(), chips.end(), [](auto& c) {
		return !c.isIn; 
	});//�L���łȂ��`�b�v�͏���
	chips.erase(itr, chips.end());
	if (chips.empty())return position;//�����Ώۂ��Ȃ������猳�̈ʒu�̂܂�

	std::sort(chips.begin(), chips.end(), FieldChipSort());
	auto minScore = chips.front().score;
	auto seconditr = std::remove_if(chips.begin(), chips.end(), [minScore](auto& c) {
		return c.score > minScore;
	});
	//�L���łȂ��`�b�v�͏���
	chips.erase(seconditr, chips.end());
	if (chips.empty())return position;//�����Ώۂ��Ȃ������猳�̈ʒu�̂܂�

	int nearest = 0;
	FieldChip resultChip = chips.front();
	for (auto& c : chips) {
		if (Vector3::Distance(finalPosition, resultChip.position) > Vector3::Distance(finalPosition, c.position)) {
			resultChip = c;
		}
	}
	//world->getGrid().addCost(chips.front().point);
	if(pointptr!=nullptr)*pointptr = resultChip.point;
	prevPoint = point;
	return resultChip.position;
}

Vector3 AvoidSearch::selectPoint(IWorld* world, Vector3 position, const std::list<Vector3>& target, Point* pointptr)
{
	std::list<int> ignorexList;
	std::list<int> ignoreyList;

	Point pt = world->getGrid().getGridNum(position);
	ignorexList.push_back(pt.x);
	ignorexList.push_back(pt.x + 1);
	ignorexList.push_back(pt.x - 1);
	ignoreyList.push_back(pt.y);
	ignoreyList.push_back(pt.y + 1);
	ignoreyList.push_back(pt.y - 1);

	for (auto t : target) {
		Point point = world->getGrid().getGridNum(t);
		ignorexList.push_back(point.x);
		ignoreyList.push_back(point.y);
	}

	std::list<int> xlist;
	std::list<int> ylist;
	for (int i = 0; i < world->getGrid().getXYSize().x; i++) {
		xlist.push_back(i);
	}
	xlist.remove_if([&](int& a) {return std::find(ignorexList.begin(), ignorexList.end(), a) != ignorexList.end(); });
	for (int i = 0; i < world->getGrid().getXYSize().y; i++) {
		ylist.push_back(i);
	}
	ylist.remove_if([&](int& a) {return std::find(ignoreyList.begin(), ignoreyList.end(), a) != ignoreyList.end(); });

	std::vector<int> xlistv;
	xlistv.assign(xlist.begin(), xlist.end());
	std::vector<int> ylistv;
	ylistv.assign(ylist.begin(), ylist.end());

	Point result;
	result.x = Random::GetInstance().Randomize(xlistv);
	result.y = Random::GetInstance().Randomize(ylistv);

	if (pointptr != nullptr)*pointptr = result;
	//world->getGrid().resetCost();
	return world->getGrid().getGridChip(result).position;
}

int AvoidSearch::SearchAngleNum(float angle)
{
	angle += 22.5f;//�J�n�ʒu�͍��΂ߏ�
	angle /= 45.0f;
	return (int)std::fmodf(std::floorf(angle) + 8.0f, 8.0f);
}

//�E���E����͎��g�̑O�����x�N�g���ƁA���g���瑊��ւ̃x�N�g���̊O�ς�y�������Ȃ獶�A���Ȃ�E�ɑ��肪����
//�E�O�㔻��͎��g�̑O�����x�N�g���ƁA���g���瑊��ւ̃x�N�g���̓��ς̒l�����Ȃ�O�A���Ȃ���ɑ��肪����
//�E���g�̏�����x�N�g������]����ꍇ�̍��E����́A���g�̏�����x�N�g���ƁA��ōs�������E����p�̊O�σx�N�g���œ��ς����A���̒l�����Ȃ獶�ɁA���Ȃ�E�ɑ��肪����
