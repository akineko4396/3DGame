#include "main.h"
#include "../TitleScene/TitleScene.h"
#include "GameScene.h"
#include "Game/GameWorld/GameWorld.h"


//============================================================
// �X�V����
//============================================================
int GameScene::Update()
{

	// Escape�L�[
	if(INPUT.KeyCheck_Enter(VK_ESCAPE)){
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

	// �Q�[�����[���h�X�V
	GW.Update();





	return 0;
}

//============================================================
// �`�揈��
//============================================================
void GameScene::Draw()
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


	// �Ƃ肠����XYZ�������`�悵�Ƃ�
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(1, 0, 0), &YsVec4(1, 0, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 1, 0), &YsVec4(0, 1, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 0, 1), &YsVec4(0, 0, 1, 1));


	// �`��Ȃǂ�����

	// �Q�[�����[���h�`��
	GW.Draw();







}

//============================================================
// �f�[�^���
//============================================================
void GameScene::Release()
{
	Dw_Scroll(0,"�Q�[���V�[���������");

	// �Q�[�����[���h���
	GW.Release();
	GameWorld::DeleteWorld();
}

//============================================================
// �����ݒ�
//============================================================
void GameScene::Init()
{
	Dw_Scroll(0,"�Q�[���V�[��������");

	// ���s���C�g�쐬
	m_DirLight = ShMgr.m_LightMgr.AddDirLight();

	//============================================================
	// �f�[�^�ǂݍ��݂Ȃ�
	//============================================================

	// �Q�[�����[���h�쐬�E������
	GameWorld::CreateWorld();
	GW.Init();
}


