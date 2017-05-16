#include "main.h"
#include "TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../SampleScene/SampleScene.h"
#include "../EditScene/EditScene.h"

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

	//Shift�L�[
	if (INPUT.KeyCheck_Enter(VK_SHIFT)) {
		// �V�[���؂�ւ�
		SPtr<EditScene> es(new EditScene());
		es->Init();
		APP.m_NowScene = es;

		return 1;
	}

	// Enter
	if(INPUT.KeyCheck_Enter(VK_RETURN)){
		// �V�[���؂�ւ�
		SPtr<SampleScene> ss(new SampleScene());
		ss->Init();
		APP.m_NowScene = ss;

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

	//=========================================================
	// �L��������
	//=========================================================

	//---------------------------------------------
	// �L�����P
	//---------------------------------------------
	{

		if(INPUT.KeyCheck_Enter('Z')) {
			m_Chara.m_Anim.ChangeAnimeSmooth_FromName("�^�[��", 0, 0, true);
		}
		if(INPUT.KeyCheck_Enter('X')) {
			m_Chara.m_Anim.ChangeAnimeSmooth_FromName("����", 0, 10, true);
		}
		if(INPUT.KeyCheck_Enter('C')) {
			m_Chara.m_Anim.ChangeAnimeSmooth_FromName("����", 0, 10, true);
		}

		//-------------------------------------
		// �P���ȃA�j���[�V�����݂̂��s�����@
		//-------------------------------------
		/*
		// �A�j���[�V������i�߂�
		m_Chara.m_Anim.Animation(1.0);
		// �S�{�[���ATransMat���g��WorldMat���X�V
		m_Chara.m_Mo.CalcBoneMatrix(&m_Chara.m_Mat);
		*/

		//-------------------------------------
		// Root�{�[�����L�����̈ړ��p�Ɏg���A�A�j���[�V�����{�ړ����s�����@
		//-------------------------------------
		// �A�j���[�V������i�߂�
		// ��Root�{�[���ɕω��ʂɂ��Am_Chara.m_Mat���ω�����
		m_Chara.m_Anim.Animation(1.0, &m_Chara.m_Mat);
		// �S�{�[���ATransMat���g��WorldMat���X�V
		// ��Root�{�[���͈ړ��p�Ƃ��Ďg�����̂ŁA��������
		m_Chara.m_Mo.CalcBoneMatrix_SkipRoot(&m_Chara.m_Mat);

	}

	//---------------------------------------------
	// �L�����Q
	//---------------------------------------------
	{
		// �A�j���i�s���A�S�{�[����TransMat���X�V
		// ��Root�{�[���ɕω��ʂɂ��A�����Ŏw�肵���s�񂪕ω�����
		m_Chara2.m_Anim.Animation(1.0, &m_Chara2.m_Mat);
		
		// �A�j���i�s���A�S�{�[����TransMat���X�V
		// �����񂱂��ɂ́A�㔼�g�݂̂̃A�j�����Đ����Ă���̂ŁA�㔼�g�������X�V�����I
		m_Chara2.m_Anim2.Animation(1.0);

		// �S�{�[���ATransMat���g��WorldMat���X�V
		m_Chara2.m_Mo.CalcBoneMatrix_SkipRoot(&m_Chara2.m_Mat);

	}

	//---------------------------------------------
	// ��
	//---------------------------------------------
	for(int i=0;i<400;i++)
	{
		//-------------------------------------
		// �P���ȃA�j���[�V�����݂̂��s�����@
		//-------------------------------------
//		m_Box[i].m_Anim.Animation(1.0);
//		m_Box[i].m_Mo.CalcBoneMatrix(&m_Box[i].m_Mat);

		//-------------------------------------
		// Root�{�[�����L�����̈ړ��p�Ɏg���A�A�j���[�V�����{�ړ����s�����@
		//-------------------------------------
		m_Box[i].m_Anim.Animation(1.0, &m_Box[i].m_Mat);
		m_Box[i].m_Mo.CalcBoneMatrix_SkipRoot(&m_Box[i].m_Mat);
	}

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


	// �`��Ȃǂ�����


	//==========================================
	// [2D]�w�i�`��
	//==========================================
	YsDx.GetSprite().Begin();
	{
		YsDx.GetSprite().Draw(*m_texBack, 0, 0, m_texBack->GetInfo().Width, m_texBack->GetInfo().Height);
	}
	YsDx.GetSprite().End();

	//==========================================
	// [3D]���f���`��
	//==========================================

	// ���L�����`��
	for (int i = 0; i < 400; i++) {
		ShMgr.m_Samp.DrawModel(m_Box[i].m_Mo, &m_Box[i].m_Mat);
	}

	// �L�����P�`��
	ShMgr.m_Samp.DrawModel(m_Chara.m_Mo, &m_Chara.m_Mat);
	// �֊s�`��
	ShMgr.m_Samp.DrawModelOutline(m_Chara.m_Mo, &YsVec4(0.2f, 0.2f, 0.2f, 0.5f), &YsVec2(0.0005f, 0.015f));

	// �L�����Q�`��
	ShMgr.m_Es.DrawModel(m_Chara2.m_Mo, &m_Chara2.m_Mat);


	// ��������
	std::string text;
	text = "[�^�C�g���V�[��]\n";
	text += "Space:�Q�[���V�[����\n";
	text += "Enter:�T���v���V�[����\n";
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

	//--------------------------------------------------------
	// �e�N�X�`���ǂݍ���
	//--------------------------------------------------------
	m_texBack = APP.m_ResStg.LoadTexture("data/Texture/title_back.png");

	//--------------------------------------------------------
	//
	// ���f���ǂݍ���
	//  APP.m_ResStg�̑���ɁAYsDx.GetResStg()���g�p���Ă�����(�ǂ���������)
	//
	//--------------------------------------------------------
	// 3D���f����ǂݍ��݁A���̃A�h���X���L���B
	SPtr<YsGameModel> gmChara = APP.m_ResStg.LoadMesh("data/model/Hackadoll_1/model.xed");
	SPtr<YsGameModel> gmBox = APP.m_ResStg.LoadMesh("data/model/box/box.x");


	//--------------------------------------------------------
	//
	// �L�����ݒ�
	//
	//--------------------------------------------------------

	// �L�����P�ݒ�
	m_Chara.m_Mo.SetModel(gmChara);						// ���f�������b�V���I�u�W�F�N�g�փZ�b�g���A�g�����Ԃɂ���
	m_Chara.m_Mat.CreateMove(0, 0, 0);						// �����s���ݒ�

	m_Chara.m_Mo.InitAnimator(m_Chara.m_Anim);				// �A�j���[�^�[�ݒ�@�����ŃA�j���[�V�������ł���
	m_Chara.m_Anim.ChangeAnime(1, true);					// �A�j���ύX

	// �L�����Q�ݒ�
	m_Chara2.m_Mo.SetModel(gmChara);						// ���f�������b�V���I�u�W�F�N�g�փZ�b�g���A�g�����Ԃɂ���
	m_Chara2.m_Mat.CreateMove(1, 0, 0);						// �����s���ݒ�

	m_Chara2.m_Mo.InitAnimator(m_Chara2.m_Anim);			// �A�j���[�^�[�ݒ�@�����ŃA�j���[�V�������ł���
	m_Chara2.m_Mo.InitAnimator(m_Chara2.m_Anim2);			// �A�j���[�^�[�ݒ�@�����ŃA�j���[�V�������ł���

	m_Chara2.m_Anim.ChangeAnime(1, true);							// �A�j���ύX
	m_Chara2.m_Anim2.ChangeAnime_FromName("[����]���@�P", true);	// �A�j���ύX�@�A�j�����ł��w��ł���@����͏㔼�g�����̃A�j����ݒ肷��

	// ���L�����ݒ� 400��
	{

		// �S���L�����ݒ�
		for (int i = 0; i < 400; i++) {
			// ���W
			float x = (i / 20 - 10) * 3.0f;
			float z = (i % 20 - 10) * 3.0f;

			m_Box[i].m_Mo.SetModel(gmBox);					// ���f�������b�V���I�u�W�F�N�g�փZ�b�g���A�g�����Ԃɂ���
			m_Box[i].m_Mat.CreateMove(x, -1, z);				// �����s���ݒ�

			m_Box[i].m_Mo.InitAnimator(m_Box[i].m_Anim);		// �A�j���[�^�[�ݒ�@�����ŃA�j���[�V�������ł���
		}

		//---------------------------------
		// ���A�j����r���Œǉ�������@
		//---------------------------------

		// �A�j�����P�ǂݍ��ݒǉ��o�^����
		SPtr<YsAnimationSet> ani = std::make_shared<YsAnimationSet>();	// �A�j���f�[�^�쐬
		ani->LoadXMD("data/model/box/move2.xmd", "���ɂ�");				// �A�j���f�[�^�ǂݍ���
		m_Box[211].m_Anim.AddAnimation(ani);							// �A�j���[�^�ɓr���ŃA�j����ǉ����邱�Ƃ��ł���
			// �ȈՓI�ɁA���L�̂P�s�̏������ł�OK
			//m_Box[211].m_Anim.AddAnimation("data/model/box/move.xmd", "���ɂ�");	// �A�j����ǂݍ��݁A�ǉ�

		m_Box[211].m_Anim.ChangeAnime_FromName("���ɂ�", true);		// �A�j���ύX
	}


}
