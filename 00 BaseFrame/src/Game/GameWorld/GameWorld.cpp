#include "main.h"
#include "Data/DataManager.h"
#include "GameWorld.h"
#include "Game/Edit/EditWorld.h"

//static�����o�ϐ��̖{��
GameWorld*	GameWorld::s_pInst = nullptr;

void GameWorld::Init()
{
	//�J�����̏�����
	m_gwCam.Init(20, 180, 0, false, true);
	m_ewCam.Init(20, 180, 0);

	//�G�f�B�b�g�t���O�����l
	m_EditFlg = FALSE;

	//�O������Q�[���I�u�W�F�N�g��ǂݍ���
	UPtr<DataManager> uDM(new DataManager);
	Obj_Num_Max = uDM->DataLoad("data/txt/Object1.txt");

	// �J�������_�L�����Ƃ��ċL��
	m_wpCamera = ObjectBase::GetThisObject(OBJECT_LIST::ID::PLAYER);
	// �v���C���[�Ƃ��ċL��
	m_wpPlayer = ObjectBase::GetThisObject(OBJECT_LIST::ID::PLAYER);

	// �G�f�B�b�g���[���h�쐬�E������
	EditWorld::CreateWorld();
	EW.Init(Obj_Num_Max);
}

void GameWorld::Release()
{

	//�O���̃e�L�X�g�t�@�C���֕ۑ�
	UPtr<DataManager> uDM(new DataManager);
	uDM->DataSave("data/txt/Object1.txt", Obj_Num_Max);

	//�G�f�B�b�g���[�h���
	EW.Release();
	EditWorld::DeleteWorld();

	ObjectBase::FullClear();

	m_wpCamera.reset();
	m_wpPlayer.reset();
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
	//�G�f�B�b�g���[�h
	//=======================================
	//�G�f�B�b�g���[�h
	if (INPUT.KeyCheck_Enter('N') && !m_EditFlg) {
		//�t���OON
		m_EditFlg = TRUE;
	}
	//�Q�[��
	if (INPUT.KeyCheck_Enter('M') && m_EditFlg) {
		//�t���OOFF
		m_EditFlg = FALSE;
	}
	if (m_EditFlg) {
		// �J��������
		m_ewCam.Update(ObjectBase::GetThisObject(OBJECT_LIST::ID::PLAYER)->GetPos());
		//�G�f�B�b�g���[�h�X�V
		EW.Update();
	}
	else {
		//�S�I�u�W�F�N�g�X�V
		ObjectBase::AllUpdate();
		// �J��������
		m_gwCam.Update(ObjectBase::GetThisObject(OBJECT_LIST::ID::PLAYER)->GetPos());
	}

	// Player���W�f�o�b�O�\��
	auto player = m_wpPlayer.lock();
	if (player) {
		Dw_Static(10, "pos(%.2f, %.2f, %.2f)", player->GetPos().x, player->GetPos().y, player->GetPos().z);
	}
}

void GameWorld::Draw()
{
	//==========================================
	// �J�����ݒ�
	//==========================================
	// �|�[�Y���łȂ��Ȃ�A�J�������_�ɐݒ肵�Ă���L�����́A�J�������������s
	/*if (m_PauseFlag == false) {
		if (m_wpCamera.expired() == false) {
			m_wpCamera.lock()->SetCamera();
		}
	}*/
	// �|�[�Y���Ȃ�AGameWorld�̃J�������g�p
	//else {
		if (m_EditFlg) {
			m_ewCam.SetCamera();
			//�G�f�B�b�g���[�h�`��
			EW.Draw();
		}
		else if (!m_EditFlg) {
			m_gwCam.SetCamera(ObjectBase::GetThisObject(OBJECT_LIST::ID::PLAYER)->GetPos());
		}
	//}

	//=======================================
	// �`�撼�O�ɃV�F�[�_�̃t���[���P�ʃf�[�^���X�V����
	//=======================================
	ShMgr.UpdateBeforeDraw();

	//�S�I�u�W�F�N�g�`��
	ObjectBase::AllDraw();
}