#include "main.h"
#include "../GameWorld.h"

void Player::Init()
{
	//�@���f���ǂݍ���
	m_gmObj=APP.m_ResStg.LoadMesh("data/model/Hackadoll_1/model.xed");
	//�@���f���f�[�^���Z�b�g
	m_moPla.SetModel(m_gmObj);
	//�@�����̍s��ݒ�
	m_mObj.CreateMove(m_vPos);
	//�@�����̃T�C�Y
	m_mObj.Scale(m_vScale);
	//�@�����̉�]��
	m_mObj.RotateY_Local(m_vAngle.y);
	m_mObj.RotateX_Local(m_vAngle.x);
	m_mObj.RotateZ_Local(m_vAngle.z);

	//�@�A�j���[�^��������
	m_moPla.InitAnimator(m_aniPla);
	//�@�����A�j��
	m_aniPla.ChangeAnime_FromName("����", true);
}

void Player::Update()
{

	// ��Ɨp�ϐ�
	/*static float		JUMP_POWER;			//�W�����v��
	const static float	GRAVITY = 0.1f;			//�d��
	static YsVec3		Pos;				//�v���C���[Y���W�ꎞ�ۑ��p
	static float		prev;				//�W�����v�����Ƃ��̍��W�ۑ��p
	static bool			JFlg = false;		//�W�����v���Ă��邩�̃t���O*/

	//===========================================================
	// �ړ�����
	//===========================================================
	if (INPUT.KeyCheck('W'))m_mObj.Move_Local(0.0f, 0.0f, 0.1f);
	if (INPUT.KeyCheck('S'))m_mObj.Move_Local(0.0f, 0.0f, -0.1f);
	if (INPUT.KeyCheck('A'))m_mObj.Move_Local(-0.1f, 0.0f, 0.0f);
	if (INPUT.KeyCheck('D'))m_mObj.Move_Local(0.1f, 0.0f, 0.0f);

	//===========================================================
	// �W�����v����
	//===========================================================
	/*if (INPUT.KeyCheck(VK_SPACE) && !JFlg){
		JFlg = true;
		JUMP_POWER = 1;
		Pos = m_mObj.GetPos();
		prev = Pos.y;
	}
	if (JFlg){
		if (Pos.y >= prev){
			JUMP_POWER -= GRAVITY;
			Pos.y += JUMP_POWER;
		}
		else {
			JFlg = false;
			Pos.y = prev;
		}
		m_mObj.Move_Local(0.0f, Pos.y, 0.0f);
	}*/

	//�A�j���[�V������i�߂�
	// ���m�ɂ́A�A�j���[�V�����������ƂɁA�S�{�[���́uTransMat�v���X�V����
	m_aniPla.Animation(1.0);

	/*auto bone = m_moPla.SearchBone("��");
	if (bone){
	bone->TransMat.RotateY_Local(45);
	}*/

	//�S�{�[���́uWorldMat�v���uTransMat�v�����ƂɎZ�o����
	// ���ۂɕ`��ȂǂŕK�v�Ȃ̂�����WorldMat�ł�
	m_moPla.CalcBoneMatrix(&m_mObj);

	//Space�Ŏ��̃A�j����
	/*if (INPUT.KeyCheck_Enter(VK_SPACE)){
	//�L�����P
	int aniNo = m_aniPla.GetAnimeNo();
	aniNo++;
	if (aniNo >= m_aniPla.GetMaxAnimeNum()){
	aniNo = 0;
	}
	m_aniPla.ChangeAnimeSmooth(aniNo, 0, 20, true);
	}*/
}

void Player::Draw()
{
	// SampleShader�N���X�ŕ`�悷��
	ShMgr.m_Samp.DrawModel(m_moPla, &m_mObj);

	////=======================================
	//// ����`��
	////=======================================
	//auto bone = m_moPla.SearchBone("RHandPoint");		//�{�[������
	//if (bone){		//�{�[������
	//	// �{�[��	�̍s����g���āA�����`��
	//	ShMgr.m_Samp.DrawModel(m_moKatana, &bone->WorldMat);
	//}

	////=======================================
	//// �L�����P �{�[�����\��
	////=======================================
	//YsDx.GetSprite().Begin(true);
	//for (auto& bn : m_moPla.GetBoneTree()){
	//	// �{�[���s���2D���W�֕ϊ�
	//	YsVec3 v2D;
	//	m_Cam.Convert3Dto2D(v2D, bn->WorldMat.GetPos());
	//	if (v2D.z > 0){
	//		YsDx.GetSprite().DrawFont(bn->pSrcBoneNode->BoneName, v2D.x + 1, v2D.y + 1, &YsVec4(0, 0, 0, 1));
	//		YsDx.GetSprite().DrawFont(bn->pSrcBoneNode->BoneName, v2D.x, v2D.y, &YsVec4(1, 1, 1, 1));
	//	}
	//}
	//YsDx.GetSprite().End();
}