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
	//対象の位置
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
	bool isIn = false;//チップがいるか
	//周囲8マスを取ってくる
	for (int i = 0; i < 8; i++) {
		auto chip = world->getGrid().getGridChip(point + rounds[i], &isIn);
		//if (!isIn)continue;
		if (chip.point == prevPoint)chip.score += 5.0f;
		chips.push_back(chip);
	}
	
	for (auto t : target) {
		auto ftoTargetVector = t - position;//自身から相手へ
		auto fangle = Vector3::Angle(Vector3::Forward, ftoTargetVector);
		auto fisLeftVector = Vector3::Cross(Vector3::Forward, ftoTargetVector);
		if (fisLeftVector.y < 0.0f)fangle = 360.0f - fangle;

		auto aresult = SearchAngleNum(fangle);
		chips[aresult].score += centerScore;//向きそのもの
		chips[(aresult + 4 + 8) % 8].score += centerScore*std::powf(sideRate, 4);//逆側
		for (int i = 0; i < 3; i++) {
			int key = (aresult - i - 1 + 8) % 8;
			chips[key].score += centerScore*std::powf(sideRate, i + 1);
			key = (aresult + i + 1 + 8) % 8;
			chips[key].score += centerScore*std::powf(sideRate, i + 1);
		}
	}

	//目的地へのコストを下げる
	auto toTargetVector = finalPosition - position;//自身から相手へ
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

	chips[result].score -= fdivd;//向きそのもの
	chips[(result + 1 + 8) % 8].score -= fdivd*0.9f;//向きそのもの
	chips[(result - 1 + 8) % 8].score -= fdivd*0.9f;//向きそのもの
	chips[(result + 2 + 8) % 8].score -= fdivd*0.1f;//向きそのもの
	chips[(result - 2 + 8) % 8].score -= fdivd*0.1f;//向きそのもの

	//ケツ側には行きづらくする
	//chips[(result + 4 + 8) % 8].score *= mulCount * 4;//逆側
	//for (int i = 1; i < 3; i++) {
	//	int key = (result - i - 1 + 8) % 8;
	//	chips[key].score *= mulCount*i;
	//	key = (result + i + 1 + 8) % 8;
	//	chips[key].score *= mulCount*i;
	//}
	//chips[result].score /= divCount;//向きそのもの
	//chips[(result + 4 + 8) % 8].score /= divCount*std::powf(1.0f-sideRate, 4);//逆側
	//for (int i = 1; i < 3; i++) {
	//	int key = (result - i - 1 + 8) % 8;
	//	chips[key].score /= divCount*std::powf(1.0f - sideRate, i + 1);
	//	key = (result + i + 1 + 8) % 8;
	//	chips[key].score /= divCount*std::powf(1.0f - sideRate, i + 1);
	//}
	auto prev_to_Vector = position - world->getGrid().getGridChip(prevPoint).position;//前から今へ
	auto isLeft_prev_to_Vector = Vector3::Cross(prev_to_Vector, toTargetVector);
	bool isLeft = false;
	if (isLeft_prev_to_Vector.y > 0.0f)isLeft = true;

	float angleAddScore = 0.5f*target.size();
	chips[result].score -= angleAddScore;//向きそのもの
	if (isLeft) {
		chips[(result - 1 + 8) % 8].score -= angleAddScore;//向きそのもの
	}
	else {
		chips[(result + 1 + 8) % 8].score -= angleAddScore;//向きそのもの
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
	});//有効でないチップは消す
	chips.erase(itr, chips.end());
	if (chips.empty())return position;//検索対象がなかったら元の位置のまま

	std::sort(chips.begin(), chips.end(), FieldChipSort());
	auto minScore = chips.front().score;
	auto seconditr = std::remove_if(chips.begin(), chips.end(), [minScore](auto& c) {
		return c.score > minScore;
	});
	//有効でないチップは消す
	chips.erase(seconditr, chips.end());
	if (chips.empty())return position;//検索対象がなかったら元の位置のまま

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
	angle += 22.5f;//開始位置は左斜め上
	angle /= 45.0f;
	return (int)std::fmodf(std::floorf(angle) + 8.0f, 8.0f);
}

//・左右判定は自身の前向きベクトルと、自身から相手へのベクトルの外積のy軸が正なら左、負なら右に相手がいる
//・前後判定は自身の前向きベクトルと、自身から相手へのベクトルの内積の値が正なら前、負なら後ろに相手がいる
//・自身の上向きベクトルが回転する場合の左右判定は、自身の上向きベクトルと、上で行った左右判定用の外積ベクトルで内積を取り、その値が正なら左に、負なら右に相手がいる
