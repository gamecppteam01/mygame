#include "TextScreen.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/FontManager.h"
#include"../Define.h"

static const int textSpeed = 3;


TextScreen::TextScreen()
{

}

void TextScreen::Init(const std::string& filename, int windowTextSize)
{
	textSize_ = windowTextSize;//1�\�����̗ʂ����߂�

	//�f�[�^��������
	textList_.clear();
	textList_.push_back("");

	//�t�@�C����ǂ�ł���
	std::ifstream readText_("res/Text/" + filename);
	readText_.seekg(0, std::ios_base::end);
	std::size_t size = (std::size_t)readText_.tellg();//�����T�C�Y���m�F
	readText_.seekg(0, std::ios_base::beg);
	std::vector<char> charbuf(size);//�������S�Ċi�[����z��
	readText_.read(&charbuf[0], size);

	auto itr = std::remove_if(charbuf.begin(), charbuf.end(), [](char c) {return c == '\0'; });
	if(itr!=charbuf.end())charbuf.erase(itr);

	int count = 0;
	for (int i = 0; i < charbuf.size(); i++) {

		char chartex = charbuf[i];
		
		//��؂蕶���Ȃ玟��
		if (chartex == '\n') {
			textList_.push_back("");
			count = 0;
			continue;
		}

		count++;
		//2�o�C�g�����Ȃ�2�����񕪂̒ǉ�
		if (_mbclen((BYTE*)&chartex) == 2) {
			textList_.back() += chartex;
			i++;
			textList_.back() += charbuf[i];

		}
		//1�o�C�g�����Ȃ�1�������̒ǉ�
		else textList_.back() += chartex;


		if (i == charbuf.size()-1)break;

		if (count >= textSize_) {
			textList_.push_back("");
			count = 0;
		}
	}
	textCount_ = 0;
	targetText_ = 0;
	timeCount_ = 0;

	insertPoints_[0] = CheckInsertPoinst(textList_[targetText_], insertPoints_[1], insertPoints_[2], insertPoints_[3]);
}


void TextScreen::Update()
{
	timeCount_++;
	textCount_ += timeCount_%textSpeed == 0 ? 1 : 0;//�X�s�[�h�̃t���[�����ɍX�V

	textCount_ = min(textCount_, textList_[targetText_].size());//�����͈͂𐧌�

}

void TextScreen::Check()
{
	//���͂�\�����I����ĂȂ�������I���
	if (textCount_<textList_[targetText_].size()) {
		textCount_ = textList_[targetText_].size();
		return;
	}

	//�͈͂𒴂��Ă�����I���
	if (textList_.size()-1<=targetText_) {
		return;
	}

	targetText_++;//���̃e�L�X�g��
	textCount_ = 0;//�\�����ŏ���

	insertPoints_[0] = CheckInsertPoinst(textList_[targetText_], insertPoints_[1], insertPoints_[2], insertPoints_[3]);

}

void TextScreen::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (128));
	DrawBox(100, 100, WINDOW_WIDTH - 100, 350, GetColor(128, 128, 128), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int splitCount = textSize_ / textLine;
	splitCount += textSize_%textLine == 0 ? 0 : 1;//����؂�Ė���������l�ǉ�

	if (textList_.empty())return;

	int length = textCount_;

	std::string drawText = textList_.at(targetText_).substr(0, textCount_);
	if (currentText()>splitCount)drawText.insert(drawText.begin() + insertPoints_[1], '\n');
	if (currentText()>splitCount*2)drawText.insert(drawText.begin() + insertPoints_[2], '\n');
	FontManager::GetInstance().DrawTextApplyFont(200, 150, GetColor(255, 255, 255), FONT_ID::JAPANESE_FONT, drawText);

}

void TextScreen::End()
{
}


int TextScreen::CheckInsertPoinst(const std::string& checkText, int & point1, int & point2, int& point3)
{
	int result = 0;
	int splitCount = textSize_ / textLine;
	splitCount += textSize_%textLine == 0 ? 0 : 1;//����؂�Ė���������l�ǉ�

	int count = 0;
	for (int i = 0; i < checkText.size(); i++) {
		count++;
		int size = _mbclen((BYTE*)&checkText[i]);
		if (size == 2)i++;
		if (count == splitCount) {
			result++;
			point1 = i + 1;
		}
		if (count == splitCount * 2) {
			result++;
			point2 = i + 2;
		}
	}
	point3 = count;
	return result;
}


int TextScreen::currentText()const
{
	int result = 0;
	for (int i = 0; i < textCount_; i++) {
		result++;
		int size = _mbclen((BYTE*)&textList_.at(targetText_)[i]);
		if (size == 2)i++;
	}
	return result;
}
