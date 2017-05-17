#include "main.h"
#include "../TitleScene/TitleScene.h"
#include "EditScene.h"


//============================================================
// �X�V����
//============================================================
int EditScene::Update()
{

	// Escape�L�[
	if (INPUT.KeyCheck_Enter(VK_ESCAPE)) {
		// �V�[���؂�ւ�
		SPtr<TitleScene> ts(new TitleScene());
		ts->Init();
		APP.m_NowScene = ts;

		return 1;
	}

	//==========================================
	// ���C�g���X�V
	//	�����̏����e�V�F�[�_���Ŏg�p���܂�
	//==========================================
	// ���s����
	m_DirLight->SetData(
		YsVec3(0.5f, -1, -0.2f),		// ���C�g����
		YsVec4(0.8f, 0.8f, 0.8f, 1)		// ��{�F(Diffuse)
	);

	// ���F(Ambient)
	ShMgr.m_LightMgr.m_AmbientLight.Set(0.2f, 0.2f, 0.2f);

	//=======================================
	// �J��������
	//=======================================
	m_Cam.Update();



	return 0;
}

//============================================================
// �`�揈��
//============================================================
void EditScene::Draw()
{
	//==========================================
	// �N���A
	//==========================================
	// �o�b�N�o�b�t�@���N���A����B
	YsDx.GetBackBuffer()->ClearRT(YsVec4(0.3f, 0.3f, 0.3f, 1));
	// Z�o�b�t�@�̃N���A
	YsDx.GetDepthStencil()->ClearDepth(true, true);

	// ���������[�h��
	ShMgr.m_bsAlpha.SetState();

	//=======================================
	// �J�����ݒ�
	//=======================================
	m_Cam.SetCamera();

	// ���ڂ̂悤�ɐ��������ċ�؂�
	static int cnt;
	for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(-50 + cnt * 1, 0, 50), YsVec3(-50 + cnt * 1, 0, -50), &YsVec4(1, 1, 1, 1));
	for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(50, 0, -50 + cnt * 1), YsVec3(-50, 0, -50 + cnt * 1), &YsVec4(1, 1, 1, 1));

	// �Ƃ肠����XYZ�������`�悵�Ƃ�
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(1, 0, 0), &YsVec4(1, 0, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 1, 0), &YsVec4(0, 1, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 0, 1), &YsVec4(0, 0, 1, 1));


	// �`��Ȃǂ�����




}

//============================================================
// �f�[�^���
//============================================================
void EditScene::Release()
{
	Dw_Scroll(0, "�G�f�B�b�g�V�[���������");

}

//============================================================
// �����ݒ�
//============================================================
void EditScene::Init()
{
	Dw_Scroll(0, "�G�f�B�b�g�V�[��������");

	// ���s���C�g�쐬
	m_DirLight = ShMgr.m_LightMgr.AddDirLight();

	//�J�����̏�����
	m_Cam.Init(20, 130, -3);
	m_Cam.m_BaseMat.SetPos(0, 1.2f, 0);

	//============================================================
	// �f�[�^�ǂݍ��݂Ȃ�
	//============================================================


}


