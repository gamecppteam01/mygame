#pragma once
#include"Sound.h"
#include"../Graphic/DebugDraw.h"
#include"../Actor/Actor.h"
#include"../Method/MethodTimer.h"

class TempoManager {
public:
	TempoManager():bpm_(0) {

	}
	~TempoManager() {

	}
	void initialize() {
		bpm_ = 0;
		actors_.clear();
		justStepTimer_.Initialize();
	}
	//�y�Ȃ�ݒ肷��
	void setMusic(BGM_ID soundId,float bpm,int beat=3,int musicCount=4) {

		//�T�E���h���\�[�X�̓ǂݍ���
		soundHandle_=Sound::GetInstance().GetHandle(soundId);
		ChangeVolumeSoundMem(80, soundHandle_);
		//���g���̐ݒ�(44.1khz)�Œ�l�ɂ���
		sps_ = GetFrequencySoundMem(soundHandle_);
		//SetFrequencySoundMem(44100, soundHandle_);
		//bpm��ݒ肷��
		bpm_ = bpm;
		//�y�Ȏ��Ԃ��擾����
		soundSize_ = GetSoundTotalSample(soundHandle_);

		beat_ = beat;

		sample_ = 0;
		tempoCount_ = 0.0f;
	}
	//�y�Ȃ��Đ�����
	void startMusic() {
		//�T�E���h���Đ�
		PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK);
		pause_ = false;
		sample_ = 0;
		tempoCount_ = 0.0f;

	}
	//�y�Ȃ��~����
	void stopMusic() {
		//�T�E���h���~
		StopSoundMem(soundHandle_);
	}
	//�y�Ȃ̈ꎞ��~
	void pauseMusic() {
		pause_ = true;
		StopSoundMem(soundHandle_);
	}
	//�y�Ȃ̍ĊJ
	void restartMusic() {
		PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK, FALSE);
		pause_ = false;
	}
	void setActor(const ActorPtr& actor) {
		actors_.push_back(actor);
	}
	void update(float deltaTime) {
		//���݂̃T���v���ʒu���擾
		sample_ = GetCurrentPositionSoundMem(soundHandle_);
		float oneTimeSample = 60.0f/ bpm_ *sps_;//1���薈�̍��v�T���v����
		float bpmSample = fmodf(sample_, oneTimeSample);//1���薈�ɋ�؂�
		tempoCount_ = bpmSample / oneTimeSample;

		if (getMeasureCount() % musicCount_ == 0) {
			justStepTimer_.Initialize();
			justStepTimer_.Add([&] {
				for (auto& act : actors_) {
					act.lock()->receiveNotification(Notification::Call_JustStep);
				}

			});
		}
		//1���ڈȊO�̓W���X�g���΂��Ȃ�
		if (getMeasureCount() % musicCount_ != musicCount_-1)return;
		if (tempoCount_ < 0.1f) {
			justStepTimer_.Action();
		}
		//float timeSample = fmodf(sample, sps);
		//float bpmSample = timeSample / (bpm_ / 60.0f);
		//float frameSample = bpmSample / sps;
	}
	//���ݔ��ł̊������擾����
	float getTempoCount() const{
		return tempoCount_;
	}
	//������Ԃ�
	int getBeatCount() const{
		float oneTimeSample = 60.0f / bpm_ *sps_;//1���薈�̍��v�T���v����
		float bpmSample = sample_/ oneTimeSample;//1���薈�ɋ�؂�
		int result = max((int)bpmSample, 0);
		return result;
	}
	//���݉����ߖڂ���Ԃ�
	int getMeasureCount()const {
		return getBeatCount() / beat_;
	}
	void draw()const {
		if(getBeatCount() % beat_ == 0)return;
		DebugDraw::DebugDrawCircle(400, 400, 30, GetColor(255, 255, 255));
	}
	//�Đ����I��������
	bool isEnd()const {
		//�|�[�Y�ł̍Đ���~�łȂ��y�Ȃ��Đ�����ĂȂ��ꍇ�I��
		return  !pause_&&CheckSoundMem(soundHandle_)==FALSE;
	}
	//�c��Đ�����
	int getRemainTime()const {
		return (soundSize_ - sample_) / sps_;
	}
	//1�����Ƃ̎��Ԃ�Ԃ�
	float getOneBeatTime()const {
		return 60.0f / bpm_;
	}
	//�����q����Ԃ�
	int getBeat()const {
		return beat_;
	}
	//�����ߖ��ŋ�؂邩
	int getMusicCount()const {
		return musicCount_;
	}
private:
	//�T�E���h�n���h��
	int soundHandle_;
	//bpm���w�肷��
	float bpm_;
	//���݂̃T���v����
	int sample_;

	//1���߂�����̔���
	int beat_{ 3 };
	//�����ߋ�؂�ɂ��邩
	int musicCount_{ 4 };
	//0�`255�͈̔͂Ńe���|�����^�C�}�[
	float tempoCount_;
	MethodTimer justStepTimer_;
	std::vector<std::weak_ptr<Actor>> actors_;
	//�y�ȃT���v����
	int soundSize_;
	//���f�t���O
	bool pause_{ false };
private:
	//�T���v�����O���g��(�f�t�H���g44,1khz)
	int sps_{ 44100 };


};