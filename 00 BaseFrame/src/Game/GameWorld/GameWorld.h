#pragma once

#include "Game/GameCamera.h"

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

//�쐬�����C���N���[�h�w�b�_�[
#include "Base/ObjectBase.h"
#include "Character/Player.h"
#include "Object/Ground.h"
#include "Object/Stronghold.h"
#include "Object/Wall.h"
#include "Object/Sling.h"
#include "Object/Cannon.h"
#include "Object/Flamethrower.h"
#include "Object/Press.h"
#include "Object/BeltConveyor.h"
#include "Object/Arm.h"
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
	//�@�J����
	//=================
	GameCamera m_Cam;

	//=================
	//�@�^�X�N�V�X�e��
	//=================
	TaskManager	m_EffectTaskMgr;		//�G�t�F�N�g�p�^�X�N�}�l�[�W���[�i�L�����N�^�[���X�g�j

	//=================
	// ���̑�
	//=================
	bool	m_PauseFlag = false;	//�|�[�YON/OFF

	int	Obj_Num_Max = 0;	//�I�u�W�F�N�g�̐��i�[�p

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