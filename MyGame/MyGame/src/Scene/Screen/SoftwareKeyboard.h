#pragma once
#include"../../Math/TwoDimensionalArray.h"
#include"../../Math/Vector2.h"
#include"../../Math/Point.h"
#include"../../Graphic/FontManager.h"
#include"../../Conv/ByteConverter.h"
#include"Cursor/KeyCursor.h"

#include<memory>
#include<list>

class SoftwareKeyboard;
//テキスト
struct SaveChara {
	SaveChara(const std::string& txt, bool iscanmin, std::vector<int> decoVec) :text(txt), isCanMin(iscanmin), decorateVec(decoVec) {

	}
	void changeDeco() {//装飾変更
		if (isMin)return;
		currentDeco = (currentDeco + 1) % decorateVec.size();
	}
	void changeMin() {//小文字化
		if (!isCanMin)return;

		isMin = !isMin;

		currentDeco = 0;
	}
	std::string getCurrentText()const {
		auto nm = ByteConverter::String_to_Int(text);
		if (isMin) {
			nm -= 1;//小文字化
		}
		else {
			nm += currentDeco;//装飾
		}
		std::string result = ByteConverter::Int_to_String(nm);
		return result;
	}
	std::string text;
	int currentDeco{ 0 };//現在の文字変換状況
	bool isMin{ false };//小文字にするか
	bool isCanMin{ false };//小文字になれるかどうか
	std::vector<int> decorateVec;//文字装飾
};

//ソフトウェアキーボードの各種ボタン
class KeyButton {
public:
	KeyButton(const Vector2& drawpos) :drawPos_{drawpos} {}
	virtual ~KeyButton() {}
	virtual void select(SoftwareKeyboard* kbd, const Point& currentMove) {}//カーソルが合った時
	virtual void push(SoftwareKeyboard* kbd) = 0;//ボタンが押された時
	virtual void draw(const Vector2& position)const=0;//描画

	Vector2 getDrawPos()const { return drawPos_; }



protected:
	Vector2 drawPos_;//描画基準位置
};
//文字入力ボタン
class KeyChar:public KeyButton {
public:
	KeyChar(const Vector2& drawpos, const std::string& character = "", std::vector<int> decorates = std::vector<int>{}, bool iscansmall=false) :KeyButton(drawpos),character(character), isCanSmall(iscansmall), decorateVec(decorates) {

	}
	void push(SoftwareKeyboard* kbd)override;
	void draw(const Vector2& position)const override{
		FontManager::GetInstance().DrawTextApplyFont(position.x + drawPos_.x, position.y + drawPos_.y, GetColor(255, 255, 255), FONT_ID::KEYBOARD_FONT, character);
	}

	bool isCanSmall{ false };//小文字化出来るか
	int decorateKey{ 0 };//文字の加算値
	std::string character;//文字
	std::vector<int> decorateVec;//文字の装飾値リスト
};

//空マス
class CursorMove:public KeyButton {
public:
	CursorMove(const Vector2& drawpos,Point up = Point{ 0,0 }, Point down = Point{ 0, 0 }, Point right = Point{ 0, 0 }, Point left = Point{ 0, 0 }) :KeyButton(drawpos),up_(up),down_(down),right_(right),left_(left) {

	}
	void select(SoftwareKeyboard* kbd, const Point& currentMove)override;

	void push(SoftwareKeyboard* kbd)override {

	}
	void draw(const Vector2& position)const override{}
private:
	Point up_;//上から来た時
	Point down_;//下から来た時
	Point right_;//右から来た時
	Point left_;//左から来た時
};
//小文字化ボタン
class ChangeMinChara :public KeyButton {
public:
	ChangeMinChara(const Vector2& drawpos): KeyButton(drawpos){

	}
	void select(SoftwareKeyboard* kbd, const Point& currentMove) override;

	void push(SoftwareKeyboard* kbd)override;
	void draw(const Vector2& position)const override {
		FontManager::GetInstance().DrawTextApplyFont(position.x + drawPos_.x, position.y + drawPos_.y, GetColor(255, 255, 255), FONT_ID::KEYBOARD_FONT, "MN");
	}

};

//装飾更新ボタン
class ChangeDecoChara :public KeyButton {
public:
	ChangeDecoChara(const Vector2& drawpos) : KeyButton(drawpos) {

	}

	void select(SoftwareKeyboard* kbd, const Point& currentMove) override;

	void push(SoftwareKeyboard* kbd)override;
	void draw(const Vector2& position)const override {
		FontManager::GetInstance().DrawTextApplyFont(position.x + drawPos_.x, position.y + drawPos_.y, GetColor(255, 255, 255), FONT_ID::KEYBOARD_FONT, "DC");
	}

};
class DecideName :public KeyButton {
public:
	DecideName(const Vector2& drawpos) :KeyButton(drawpos) {
		 
	}

	void select(SoftwareKeyboard* kbd, const Point& currentMove) override;

	void push(SoftwareKeyboard* kbd)override;
	void draw(const Vector2& position)const override {
		FontManager::GetInstance().DrawTextApplyFont(position.x + drawPos_.x, position.y + drawPos_.y, GetColor(255, 255, 255), FONT_ID::KEYBOARD_FONT, "OK");
	}

};
//struct CursorPoint {
//	CursorPoint(int target, std::vector<Point> next) :target(target), next(next) {
//
//	}
//	int target;//対象のキー
//	std::vector<Point> next;//移動先リスト(上,右,下,左)
//};
//仮想キーボード生成クラス
class SoftwareKeyboard {
public:
	enum InputState {
		INPUT_MEN,
		INPUT_WOMEN,
		INPUT_NONE
	};
public:
	SoftwareKeyboard();

	void initialize();
	void stateReset();
	void update(float deltaTime);

	void draw(const Vector2& position)const;

	Point& getCurrentKey() {
		return currentKey_;
	}
	std::vector<SaveChara>& getName() {
		return name_;
	};
	std::string getNameStr() const{
		std::string result{ "" };
		for (auto& n : name_) {
			result += n.getCurrentText();
		}
		return result;
	}
	void clearName() {
		name_.clear();
	}
	const std::vector<std::vector<std::shared_ptr<KeyButton>>>& getKeyList()const {
		return keylist;
	}
	InputState getState()const {
		return state_.back();
	}
	void nextState() {
		state_.pop_back();
	}
	bool isEnd()const {
		return state_.back() == InputState::INPUT_NONE;
	}

	void isdrawWide();
	void NotisdrawWide();

private:
	const float leftMargin = 60.0f;
	const float upMargin = 60.0f;
	const float centerMargin = 20.0f;
	const std::vector<std::vector<std::shared_ptr<KeyButton>>> keylist{//キーの
		{ std::make_shared<KeyChar>(Vector2{ 0.0f,0.0f },"ワ",std::vector<int>{0},true)						,std::make_shared<KeyChar>(Vector2{ leftMargin*1.0f,0.0f },"ラ",std::vector<int>{0})				,std::make_shared<KeyChar>(Vector2{ leftMargin*2.0f,0.0f },"ヤ",std::vector<int>{0},true)										,std::make_shared<KeyChar>(Vector2{ leftMargin*3.0f,0.0f },"マ",std::vector<int>{0})			,std::make_shared<KeyChar>(Vector2{ leftMargin*4.0f,0.0f },"ハ",std::vector<int>{0,1,2})			,std::make_shared<KeyChar>(Vector2{ leftMargin*5.0f,0.0f },"ナ",std::vector<int>{0})			,std::make_shared<KeyChar>(Vector2{ leftMargin*6.0f,0.0f },"タ",std::vector<int>{0,1})					,std::make_shared<KeyChar>(Vector2{ leftMargin*7.0f,0.0f },"サ",std::vector<int>{0,1})				,std::make_shared<KeyChar>(Vector2 { leftMargin*8.0f,0.0f },"カ",std::vector<int>{0,1})				,std::make_shared<KeyChar>(Vector2 { leftMargin*9.0f,0.0f },"ア",std::vector<int>{0},true)					,std::make_shared<ChangeMinChara>(Vector2{ leftMargin*10.0f,0.0f })  },
		{ std::make_shared<KeyChar>( Vector2{ 0.0f,upMargin*1.0f },"ヲ",std::vector<int>{0} )					,std::make_shared<KeyChar>( Vector2{ leftMargin*1.0f,upMargin*1.0f },"リ",std::vector<int>{0} )		,std::make_shared<KeyChar>( Vector2{ leftMargin*2.0f,upMargin*1.0f },"ユ",std::vector<int>{0},true)							,std::make_shared<KeyChar>( Vector2{ leftMargin*3.0f,upMargin*1.0f },"ミ",std::vector<int>{0} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*4.0f,upMargin*1.0f },"ヒ",std::vector<int>{0,1,2} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*5.0f,upMargin*1.0f },"ニ",std::vector<int>{0} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*6.0f,upMargin*1.0f },"チ",std::vector<int>{0,1} )		,std::make_shared<KeyChar>( Vector2{ leftMargin*7.0f,upMargin*1.0f },"シ",std::vector<int>{0,1} )	,std::make_shared<KeyChar>(Vector2 { leftMargin*8.0f,upMargin*1.0f },"キ",std::vector<int>{0,1} )	,std::make_shared<KeyChar>(Vector2 { leftMargin*9.0f,upMargin*1.0f },"イ",std::vector<int>{0},true)		,std::make_shared<ChangeDecoChara>(Vector2 { leftMargin*10.0f,upMargin*1.0f })},
		{ std::make_shared<KeyChar>( Vector2{ 0.0f,upMargin*2.0f },"ン",std::vector<int>{0} )					,std::make_shared<KeyChar>( Vector2{ leftMargin*1.0f,upMargin*2.0f },"ル",std::vector<int>{0} )		,std::make_shared<KeyChar>( Vector2{ leftMargin*2.0f,upMargin*2.0f },"ヨ",std::vector<int>{0},true)							,std::make_shared<KeyChar>( Vector2{ leftMargin*3.0f,upMargin*2.0f },"ム",std::vector<int>{0} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*4.0f,upMargin*2.0f },"フ",std::vector<int>{0,1,2} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*5.0f,upMargin*2.0f },"ヌ",std::vector<int>{0} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*6.0f,upMargin*2.0f },"ツ",std::vector<int>{0,1},true)	,std::make_shared<KeyChar>( Vector2{ leftMargin*7.0f,upMargin*2.0f },"ス",std::vector<int>{0,1} )	,std::make_shared<KeyChar>(Vector2 { leftMargin*8.0f,upMargin*2.0f },"ク",std::vector<int>{0,1} )	,std::make_shared<KeyChar>(Vector2 { leftMargin*9.0f,upMargin*2.0f },"ウ",std::vector<int>{0},true)			,std::make_shared<CursorMove>(Vector2{ leftMargin*10.0f,upMargin*2.0f },Point{ 0,2 },Point{ 0,0 },Point{ 0,0 },Point{ -1,0 }) },
		{ std::make_shared<CursorMove>(Vector2{ 0.0f,upMargin*3.0f },Point{1,0},Point{0,0},Point{1,0})			,std::make_shared<KeyChar>(Vector2{ leftMargin*1.0f,upMargin*3.0f },"レ",std::vector<int>{0})		,std::make_shared<CursorMove>(Vector2{ leftMargin*2.0f,upMargin*3.0f },Point{ 1,0 },Point{ 0,0 },Point{ -1,0 },Point{1,0})		,std::make_shared<KeyChar>(Vector2{ leftMargin*3.0f,upMargin*3.0f },"メ",std::vector<int>{0})	,std::make_shared<KeyChar>(Vector2{ leftMargin*4.0f,upMargin*3.0f },"ヘ",std::vector<int>{0,1,2})	,std::make_shared<KeyChar>(Vector2{ leftMargin*5.0f,upMargin*3.0f },"ネ",std::vector<int>{0})	,std::make_shared<KeyChar>(Vector2{ leftMargin*6.0f,upMargin*3.0f },"テ",std::vector<int>{0,1})			,std::make_shared<KeyChar>(Vector2{ leftMargin*7.0f,upMargin*3.0f },"セ",std::vector<int>{0,1})		,std::make_shared<KeyChar>(Vector2 { leftMargin*8.0f,upMargin*3.0f },"ケ",std::vector<int>{0,1})			,std::make_shared<KeyChar>(Vector2 { leftMargin*9.0f,upMargin*3.0f },"エ",std::vector<int>{0},true)	,std::make_shared<CursorMove>(Vector2{ leftMargin*10.0f,upMargin*3.0f },Point{ 0,0 },Point{ 0,-2 },Point{ 0,0 },Point{ -1,0 }) },
		{ std::make_shared<CursorMove>(Vector2{ 0.0f,upMargin*4.0f },Point{ 0,0 },Point{ 0,0 },Point{ 1,0 })	,std::make_shared<KeyChar>( Vector2{ leftMargin*1.0f,upMargin*4.0f },"ロ",std::vector<int>{0} )		,std::make_shared<CursorMove>(Vector2{ leftMargin*2.0f,upMargin*4.0f },Point{ 0,0 },Point{ 0,0 },Point{ -1,0 },Point{ 1,0 })	,std::make_shared<KeyChar>( Vector2{ leftMargin*3.0f,upMargin*4.0f },"モ",std::vector<int>{0} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*4.0f,upMargin*4.0f },"ホ",std::vector<int>{0,1,2} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*5.0f,upMargin*4.0f },"ノ",std::vector<int>{0} )	,std::make_shared<KeyChar>( Vector2{ leftMargin*6.0f,upMargin*4.0f },"ト",std::vector<int>{0,1} )		,std::make_shared<KeyChar>( Vector2{ leftMargin*7.0f,upMargin*4.0f },"ソ",std::vector<int>{0,1} )	,std::make_shared<KeyChar>(Vector2 { leftMargin*8.0f,upMargin*4.0f },"コ",std::vector<int>{0,1} )	,std::make_shared<KeyChar>(Vector2 { leftMargin*9.0f,upMargin*4.0f },"オ",std::vector<int>{0},true)		,std::make_shared<DecideName>(Vector2{ leftMargin*10.0f,upMargin*4.0f }) }
	};
	
	//const std::vector<std::vector<CursorPoint>> keymoveList{//移動先リスト
	//	{ { 0,{ { 0,0 },{ 1,0 },{ 0,1 },{ 0,0 } } },{ 1,{ { 1,0 },{ 2,0 },{ 1,1 },{ 0,0 } } },{ 2,{ { 2,0 },{ 3,0 },{ 2,1 },{ 1,0 } } },{ 3,{ { 3,0 },{ 4,0 },{ 3,1 },{ 2,0 } } },{ 4,{ { 4,0 },{ 5,0 },{ 4,1 },{ 3,0 } } },{ 5,{ { 5,0 },{ 6,0 },{ 5,1 },{ 4,0 } } },{ 6,{ { 6,0 },{ 7,0 },{ 6,1 },{ 5,0 } } },{ 7,{ { 7,0 },{ 8,0 },{ 7,1 },{ 6,0 } } },{ 8,{ { 8,0 },{ 9,0 },{ 8,1 },{ 7,0 } } },{ 9,{ { 9,0 },{ 9,0 },{ 9,1 },{ 8,0 } } } },
	//	{ { 10,{ { 0,0 },{ 1,1 },{ 0,2 },{ 0,1 } } },{ 11,{ { 1,0 },{ 2,1 },{ 1,2 },{ 0,1 } } },{ 12,{ { 2,0 },{ 3,1 },{ 2,2 },{ 1,1 } } },{ 13,{ { 3,0 },{ 4,1 },{ 3,2 },{ 2,1 } } },{ 14,{ { 4,0 },{ 5,1 },{ 4,2 },{ 3,1 } } },{ 15,{ { 5,0 },{ 6,1 },{ 5,2 },{ 4,1 } } },{ 16,{ { 6,0 },{ 7,1 },{ 6,2 },{ 5,1 } } },{ 17,{ { 7,0 },{ 8,1 },{ 7,2 },{ 6,1 } } },{ 18,{ { 8,0 },{ 9,1 },{ 8,2 },{ 7,1 } } },{ 19,{ { 9,0 },{ 9,1 },{ 9,2 },{ 8,1 } } } },
	//	{ { 20,{ { 0,1 },{ 1,2 },{ 0,3 },{ 0,2 } } },{ 21,{ { 1,1 },{ 2,2 },{ 0,3 },{ 0,2 } } },{ 22,{ { 2,1 },{ 3,2 },{ 1,3 },{ 1,2 } } },{ 23,{ { 3,1 },{ 4,2 },{ 1,3 },{ 2,2 } } },{ 24,{ { 4,1 },{ 5,2 },{ 2,3 },{ 3,2 } } },{ 25,{ { 5,1 },{ 6,2 },{ 3,3 },{ 4,2 } } },{ 26,{ { 6,1 },{ 7,2 },{ 4,3 },{ 5,2 } } },{ 27,{ { 7,1 },{ 8,2 },{ 5,3 },{ 6,2 } } },{ 28,{ { 8,1 },{ 9,2 },{ 6,3 },{ 7,2 } } },{ 29,{ { 9,1 },{ 9,2 },{ 7,3 },{ 8,2 } } } },
	//												{ { 30,{ { 1,2 },{ 1,3 },{ 0,4 },{ 0,3 } } },											{ 31,{ { 3,2 },{ 2,3 },{ 1,4 },{ 0,3 } } },{ 32,{ { 4,2 },{ 3,3 },{ 2,4 },{ 1,3 } } },{ 33,{ { 5,2 },{ 4,3 },{ 3,4 },{ 2,3 } } },{ 34,{ { 6,2 },{ 5,3 },{ 4,4 },{ 3,3 } } },{ 35,{ { 7,2 },{ 6,3 },{ 5,4 },{ 4,3 } } },{ 36,{ { 8,2 },{ 7,3 },{ 6,4 },{ 5,3 } } },{ 37,{ { 9,2 },{ 7,3 },{ 7,4 },{ 6,3 } } }},
	//												{ { 38,{ { 0,3 },{ 1,4 },{ 0,4 },{ 0,4 } } },											{ 39,{ { 1,3 },{ 2,4 },{ 1,4 },{ 0,4 } } },{ 40,{ { 2,3 },{ 3,4 },{ 2,4 },{ 1,4 } } },{ 41,{ { 3,3 },{ 4,4 },{ 3,4 },{ 2,4 } } },{ 42,{ { 4,3 },{ 5,4 },{ 4,4 },{ 3,4 } } },{ 43,{ { 5,3 },{ 6,4 },{ 5,4 },{ 4,4 } } },{ 44,{ { 6,3 },{ 7,4 },{ 6,4 },{ 5,4 } } },{ 45,{ { 7,3 },{ 7,4 },{ 7,4 },{ 6,4 } } }}
	//};
	Point currentKey_{ 0,0 };//現在のキー位置

	KeyCursor cursor_;
	
	std::list<InputState> state_{ InputState::INPUT_NONE,InputState::INPUT_WOMEN,InputState::INPUT_MEN };

	std::vector<SaveChara> name_;

	bool isdrawWide_{ false };
	bool istwoSize_{ false };
};