#include "main.h"
#include "Data/DataManager.h"
#include "EditWorld.h"

//static�����o�ϐ��̖{��
EditWorld* EditWorld::s_pInst = nullptr;

void EditWorld::Init(int _ObjNum)
{
	//�J�����̏�����
	m_Cam.Init(20, 180, 0, false, true);

	//���݂̃I�u�W�F�N�g������
	Obj_Num_Max = _ObjNum;

	//�G�f�B�b�g�t���O�����l
	m_EditFlg = FALSE;

}

void EditWorld::Release()
{

}

void EditWorld::Update()
{

	//=======================================
	// �J��������
	//=======================================
	m_Cam.Update();

	//�G�f�B�b�g���[�h�̎�
	if (m_EditFlg) {

		if (INPUT.KeyCheck_Enter('S')) {
			//�O���̃e�L�X�g�t�@�C���֕ۑ�
			UPtr<DataManager> uDM(new DataManager);
			uDM->DataSave("data/txt/Object1.txt", Obj_Num_Max);
		}

	}
	//�Q�[���̎�
	else if (!m_EditFlg) {
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
	}

	//�G�f�B�b�g���[�h��
	if (INPUT.KeyCheck_Enter('N') && !m_EditFlg) {
		//�J�����̏�����
		m_Cam.Init(20, 180, 0);

		//�t���OON
		m_EditFlg = TRUE;
	}
	//�Q�[����
	if (INPUT.KeyCheck_Enter('M') && m_EditFlg) {
		//�J�����̏�����
		m_Cam.Init(20, 180, 0, false, true);

		//�t���OOFF
		m_EditFlg = FALSE;
	}

}

void EditWorld::Draw()
{
	//=======================================
	// �J�����ݒ�
	//=======================================
	m_Cam.SetCamera();

	//�G�f�B�b�g���[�h�̎�
	if (m_EditFlg) {

		// ���ڂ̂悤�ɐ��������ċ�؂�
		static int cnt;
		for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(-50 + cnt * 1, 0, 50), YsVec3(-50 + cnt * 1, 0, -50), &YsVec4(1, 1, 1, 1));
		for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(50, 0, -50 + cnt * 1), YsVec3(-50, 0, -50 + cnt * 1), &YsVec4(1, 1, 1, 1));

		// �Ƃ肠����XYZ�������`�悵�Ƃ�
		ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(1, 0, 0), &YsVec4(1, 0, 0, 1));
		ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 1, 0), &YsVec4(0, 1, 0, 1));
		ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 0, 1), &YsVec4(0, 0, 1, 1));

		// ��������
		std::string text;
		text = "[�G�f�B�b�g���[�h]\n";
		text += "M:�Q�[���V�[����\n";
		text += "S:�Z�[�u\n";

		// 2D�`��(����)
		YsDx.GetSprite().Begin(true);
		{
			YsDx.GetSprite().DrawFont(text, 1, 1, &YsVec4(0, 0, 0, 1));
			YsDx.GetSprite().DrawFont(text, 0, 0, &YsVec4(1, 1, 1, 1));
		}
		YsDx.GetSprite().End();
		
	}
	//�Q�[���̎�
	else if(!m_EditFlg){

	}
}