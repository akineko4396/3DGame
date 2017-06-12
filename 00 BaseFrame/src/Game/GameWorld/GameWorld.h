#pragma once

//=====================================
//�Q�[���I�u�W�F�N�g��{�N���X
//�@�Q�[�����ɓo�ꂷ�镨�̂̊�{�ƂȂ�N���X
//=====================================
class BaseGameObj :public BaseTask
{
public:
	//�L�����̍s��
	YsMatrix	m_Mat;
};

#include "Include.h"

//=====================================
//
//�Q�[�����[���h�N���X
//
//�@�Q�[���̐��E�̊�b�ƂȂ�N���X
//
//=====================================
class GameWorld
{
public:
	//������
	void Init();

	//���
	void Release();

	//�X�V
	void Update();

	//�`��
	void Draw();


	//=================
	// ���̑�
	//=================
	bool	m_PauseFlag = false;	//�|�[�YON/OFF

	int	Obj_Num_Max = 0;	//�I�u�W�F�N�g�̐��i�[�p

private:

	//=================
	//�@�J����
	//=================
	GameCamera		m_gwCam;
	GameCamera		m_ewCam;			//�G�f�B�b�g�J����
	WPtr<ObjectBase> m_wpCamera; // ���݃J�������_�ɂȂ��Ă�L�����ւ̃A�h���X
	WPtr<ObjectBase> m_wpPlayer; // �v���C���[�L�����ւ̃A�h���X

	BOOL			m_EditFlg;			//�G�f�B�b�g�p�t���O

	//================================
	//�@�V���O���g���p�^�[��
	//================================
private:
	//�C���X�^���X�p
	static GameWorld*	s_pInst;

	//�O������C���X�^���X�������Ȃ�����private�R���X�g���N�^
	GameWorld(){
	}

public:
	//�Q�[�����[���h�폜
	static void DeleteWorld(){
		YsSafe_Delete(s_pInst);
	}

	//�Q�[�����[���h�쐬
	static void CreateWorld(){
		DeleteWorld();
		s_pInst = new GameWorld();
	}

	//�Q�[�����[���h�擾
	static GameWorld& GetWorld(){
		return *s_pInst;
	}

};

#define GW GameWorld::GetWorld()