#include "main.h"
#include "Data/DataManager.h"
#include "GameWorld.h"
#include "Game/Edit/EditWorld.h"

//static�����o�ϐ��̖{��
GameWorld*	GameWorld::s_pInst = nullptr;

void GameWorld::Init()
{
	//�O������Q�[���I�u�W�F�N�g��ǂݍ���
	UPtr<DataManager> uDM(new DataManager);
	Obj_Num_Max = uDM->DataLoad("data/txt/Object1.txt");

	// �G�f�B�b�g���[���h�쐬�E������
	EditWorld::CreateWorld();
	EW.Init(Obj_Num_Max);
}

void GameWorld::Release()
{

	//�O���̃e�L�X�g�t�@�C���֕ۑ�
	UPtr<DataManager> uDM(new DataManager);
	uDM->DataSave("data/txt/Object1.txt", Obj_Num_Max);

	//�S�I�u�W�F�N�g���
	ObjectBase::FullClear();

	//�G�f�B�b�g���[�h���
	EW.Release();
	EditWorld::DeleteWorld();
}

void GameWorld::Update()
{
	//=======================================
	// �|�[�YON/OFF
	//=======================================
	if (INPUT.KeyCheck_Enter('P')){
		m_PauseFlag = !m_PauseFlag;
	}

	//�S�I�u�W�F�N�g�X�V
	ObjectBase::AllUpdate();

	//�G�f�B�b�g���[�h�X�V
	EW.Update();
}

void GameWorld::Draw()
{

	//=======================================
	// �`�撼�O�ɃV�F�[�_�̃t���[���P�ʃf�[�^���X�V����
	//=======================================
	ShMgr.UpdateBeforeDraw();

	//�S�I�u�W�F�N�g�`��
	ObjectBase::AllDraw();

	//�G�f�B�b�g���[�h�`��
	EW.Draw();
}