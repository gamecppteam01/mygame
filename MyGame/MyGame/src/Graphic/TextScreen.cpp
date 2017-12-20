#include "TextScreen.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/FontManager.h"
#include"../Define.h"
#include"../Function/Split.h"

static const int textSpeed = 3;


TextScreen::TextScreen()
{

}

void TextScreen::Init(const std::string& filename, int lineTextSize)
{
	isEnd_ = false;
	textSize_ = lineTextSize;//1行分の量を決める

	//データを初期化
	textList_.clear();

	//ファイルを読んでくる
	std::ifstream readText_("res/Text/" + filename);
	readText_.seekg(0, std::ios_base::end);
	std::size_t size = (std::size_t)readText_.tellg();//文字サイズを確認
	readText_.seekg(0, std::ios_base::beg);
	std::vector<char> charbuf(size);//文字列を全て格納する配列
	readText_.read(&charbuf[0], size);

	auto itr = std::remove_if(charbuf.begin(), charbuf.end(), [](char c) {return c == '\0'; });
	if(itr!=charbuf.end())charbuf.erase(itr);
	
	std::string strbuf;
	strbuf.assign(charbuf.begin(), charbuf.end());

	//改行毎に分割
	std::string br = "\n";
	auto pos = strbuf.find(br);
	while (pos != std::string::npos) {
		textList_.emplace_back();
		textList_.back().assign(strbuf.begin(), strbuf.begin() + pos);
		strbuf.erase(0, pos + br.size());
		pos = strbuf.find(br);
	}
	if (!strbuf.empty()) {
		textList_.emplace_back();
		textList_.back().assign(strbuf.begin(), strbuf.end());
	}
	std::vector<std::string> textVect;

	int count = 0;
	for (auto& s : textList_) {
		if (count%textLine == 0) {
			textVect.emplace_back();
			count = 0;
		}
		textVect.back() += s + '\n';
		count++;
	}

	textList_.clear();
	textList_.assign(textVect.begin(), textVect.end());

	//int lineCount;
	//for (auto& s : textVect) {
	//	count = 0;
	//	lineCount = 0;
	//	textList_.emplace_back();
	//	for (int i = 0; i < s.size(); i++) {
	//		char chartex = s[i];

	//		textList_.back() += chartex;
	//		if (chartex == '\n') {
	//			if (lineCount == 2) {
	//				textList_.emplace_back();
	//				count = 0;
	//				lineCount = 0;
	//			}
	//			else {
	//				lineCount++;
	//				count = 0;
	//			}
	//			continue;
	//		}
	//		//2バイト文字なら2文字列分の追加
	//		if (_mbclen((BYTE*)&chartex) == 2) {
	//			i++;
	//			textList_.back() += s[i];
	//		}
	//		count++;
	//	}
	//}
	textCount_ = 0;
	targetText_ = 0;
	timeCount_ = 0;

}


void TextScreen::Update()
{
	timeCount_++;
	textCount_ += timeCount_%textSpeed == 0 ? 1 : 0;//スピードのフレーム毎に更新

	textCount_ = min(textCount_, textList_[targetText_].size());//文字範囲を制限

}

void TextScreen::Check()
{
	//文章を表示し終わってなかったら終わり
	if (textCount_<textList_[targetText_].size()) {
		textCount_ = textList_[targetText_].size();
		return;
	}

	//範囲を超えていたら終わり
	if (textList_.size()-1<=targetText_) {
		isEnd_ = true;
		return;
	}

	targetText_++;//次のテキストへ
	textCount_ = 0;//表示を最初へ

}

void TextScreen::Draw(const Vector2& position) const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (128));
	Vector2 size=Sprite::GetInstance().GetSize(SPRITE_ID::TEXTFRAME_SPRITE);
	DrawBox(position.x, position.y, position.x +size.x, position.y + size.y, GetColor(128, 128, 128), TRUE);
	Sprite::GetInstance().Draw(SPRITE_ID::TEXTFRAME_SPRITE, Vector2{ position.x,position.y });
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	size = Sprite::GetInstance().GetSize(SPRITE_ID::FACEFRAME_SPRITE);
	float correct = 50;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, position.y+ correct, size.x-1, position.y + size.y+ correct, GetColor(200, 200, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Sprite::GetInstance().Draw(SPRITE_ID::FACE_SPRITE, Vector2{ 0.0f,position.y+ correct }+Vector2{ 16.f,17.f }, Vector2::Zero, Vector2::One);
	Sprite::GetInstance().Draw(SPRITE_ID::FACEFRAME_SPRITE, Vector2{ 0.0f,position.y+ correct });

	if (textList_.empty())return;

	std::string drawText = textList_.at(targetText_).substr(0, textCount_);
	FontManager::GetInstance().DrawTextApplyFont(position.x+80.0f, position.y+60.0f, GetColor(255, 255, 255), FONT_ID::TUTORIAL_FONT, drawText);

}

void TextScreen::End()
{
}

bool TextScreen::isEnd() const
{
	return isEnd_;
}

//int TextScreen::currentText()const
//{
//	int result = 0;
//	for (int i = 0; i < textCount_; i++) {
//		result++;
//		int size = _mbclen((BYTE*)&textList_.at(targetText_)[i]);
//		if (size == 2)i++;
//	}
//	return result;
//}
