#include "main.h"
#include "Data/DataManager.h"
#include "GameWorld.h"

//static�����o�ϐ��̖{��
GameWorld*	GameWorld::s_pInst = nullptr;

void GameWorld::Init()
{
	//�O������Q�[���I�u�W�F�N�g��ǂݍ���
	UPtr<DataManager> uDM(new DataManager);
	uDM->DataLoad("data/txt/Object1.txt");

	//�J�����̏�����
	m_Cam.Init(20, 180, 0, false, true);
}

void GameWorld::Release()
{
	//=======================================
	// �^�X�N�`��@�S�^�X�N��Release���s
	//=======================================
	//m_EffectTaskMgr.Release();

	ObjectBase::FullClear();
}

void GameWorld::Update()
{
	//=======================================
	// �|�[�YON/OFF
	//=======================================
	if (INPUT.KeyCheck_Enter('P')){
		m_PauseFlag = !m_PauseFlag;
	}

	//=======================================
	// �J��������
	//=======================================
	m_Cam.Update();

	// �ړ�
	if (INPUT.KeyCheck('W')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetZAxis() * 0.03f);
	}
	if (INPUT.KeyCheck('S')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetZAxis() * -0.03f);
	}
	if (INPUT.KeyCheck('A')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetXAxis() * -0.03f);
	}
	if (INPUT.KeyCheck('D')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetXAxis() * 0.03f);
	}

	//=======================================
	// �^�X�N����@�S�G�t�F�N�g��Update���s
	//=======================================
	//m_EffectTaskMgr.UpdateTask();

	ObjectBase::AllUpdate();
}

void GameWorld::Draw()
{
	//=======================================
	// �J�����ݒ�
	//=======================================
	m_Cam.SetCamera();

	//=======================================
	// �`�撼�O�ɃV�F�[�_�̃t���[���P�ʃf�[�^���X�V����
	//=======================================
	ShMgr.UpdateBeforeDraw();

	//=======================================
	// �^�X�N�`��@�S�^�X�N��Draw���s
	//=======================================
	//YsDx.DS_ZSetting(true, false);	//Z�������݂�OFF
	//m_EffectTaskMgr.DrawTask();
	//YsDx.DS_ZSetting(true, true);	//Z�������݂�ON�ɖ߂�

	ObjectBase::AllDraw();
}