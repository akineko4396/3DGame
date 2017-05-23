#include "main.h"
#include "TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../SampleScene/SampleScene.h"

//=========================================
// �X�V����
//=========================================
int TitleScene::Update()
{
	// Space�L�[
	if(INPUT.KeyCheck_Enter(VK_SPACE)){
		// �V�[���؂�ւ�
		SPtr<GameScene> gs(new GameScene());
		gs->Init();
		APP.m_NowScene = gs;

		return 1;
	}

	// Escape�L�[
	if(INPUT.KeyCheck_Enter(VK_ESCAPE)){
		APP.ExitGame();
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

	
	//=========================================================
	// �J��������
	//=========================================================
	m_Cam.Update();


	return 0;
}

//=========================================
// �`�揈��
//=========================================
void TitleScene::Draw()
{
	//==========================================
	// �N���A
	//==========================================
	// �o�b�N�o�b�t�@���N���A����B
	YsDx.GetBackBuffer()->ClearRT(YsVec4(0.3f, 0.3f, 0.8f, 1));
	// Z�o�b�t�@�̃N���A
	YsDx.GetDepthStencil()->ClearDepth(true, true);

	// ���������[�h��
	ShMgr.m_bsAlpha.SetState();


	//==========================================
	// �J�����ݒ�
	//==========================================
	m_Cam.SetCamera();

	//==========================================
	// �`�撼�O�ɃV�F�[�_�̃t���[���P�ʃf�[�^���X�V����
	//==========================================
	ShMgr.UpdateBeforeDraw();



	// ��������
	std::string text;
	text = "[�^�C�g���V�[��]\n";
	text += "Space:�Q�[���V�[����\n";
	text += "Enter:�T���v���V�[����\n";
	text += "Shift:�G�f�B�b�g�V�[����\n";
	text += "Alt+Enter:�t���X�N���[���؂�ւ�\n";
	text += "Z�AX�AC:�A�j���[�V�����ύX\n";

	// 2D�`��
	YsDx.GetSprite().Begin(true);
	{
		YsDx.GetSprite().DrawFont(text, 1, 1, &YsVec4(0, 0, 0, 1));
		YsDx.GetSprite().DrawFont(text, 0, 0, &YsVec4(1, 1, 1, 1));

	}
	YsDx.GetSprite().End();

}

//============================================================
// �f�[�^���
//============================================================
void TitleScene::Release()
{
	// �T�E���h��~
	YsSndMgr.StopAll();


	Dw_Scroll(0, "�^�C�g���V�[���������");
}

//============================================================
// �����ݒ�
//============================================================
void TitleScene::Init()
{
	Dw_Scroll(0, "�^�C�g���V�[��������");

	// ���s���C�g�쐬
	m_DirLight = ShMgr.m_LightMgr.AddDirLight();

	// �J�����f�[�^������
	m_Cam.Init(20, 130, -3);
	m_Cam.m_BaseMat.SetPos(0, 1.2f, 0);


}
