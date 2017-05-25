#include "main.h"
#include "../GameWorld.h"

void Player::Init()
{
	//�@���f���ǂݍ���
	m_gmObj=APP.m_ResStg.LoadMesh("data/model/Player/Player.xed");
	m_moHammer.LoadMesh("data/model/Hammer/hammer.xed");
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
	m_aniPla.ChangeAnime_FromName("�ҋ@", true);

	// �L�[���̓R���|�[�l���g����
	SetInput(std::make_shared<KeyInputComponent>()); 

	// �A�N�V�����X�e�[�g
	m_ActionState = std::make_shared<PlayerAS_Wait>();
}

void Player::Update()
{

	// �X�N���v�g�֐�
	auto scriptProc = [this](YsAnimeKey_Script* scr)
	{
		//�����ŃA�j���[�V�������ɔ�������X�N���v�g����������
	};
	// �A�j���i�s�E�X�N���v�g���s
	// �X�N���v�g������ꍇ�́Afunc�����s�����
	m_aniPla.AnimationAndScript(1.0, scriptProc, &m_Mat);
	// �S�g��WorldMat���Z�o
	m_moPla.CalcBoneMatrix_SkipRoot(&m_mObj);

	// ��Ɨp�ϐ�
	/*static float		JUMP_POWER;			//�W�����v��
	const static float	GRAVITY = 0.1f;			//�d��
	static YsVec3		Pos;				//�v���C���[Y���W�ꎞ�ۑ��p
	static float		prev;				//�W�����v�����Ƃ��̍��W�ۑ��p
	static bool			JFlg = false;		//�W�����v���Ă��邩�̃t���O*/

	//���̓R���|�[�l���g����
	if (m_Controller) {
		m_Keys = m_Controller->Update();
	}

	if (m_Keys&GK_LLEFT) {
		m_mObj.Move_Local(-0.3f, 0.0f, 0.0f);
	}
	if (m_Keys&GK_LUP) {
		m_mObj.Move_Local(0.0f, 0.0f, 0.3f);
	}
	if (m_Keys&GK_LRIGHT) {
		m_mObj.Move_Local(0.3f, 0.0f, 0.0f);
	}
	if (m_Keys&GK_LDOWN) {
		m_mObj.Move_Local(0.0f, 0.0f, -0.3f);
	}

	if (m_ActionState) {
		auto p = m_ActionState;
		m_ActionState->Update(*this, m_aniPla, m_ActionState);
	}

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

	//����
	{
		auto bone = m_moPla.SearchBone("�E��_�~�[");
		if (bone) {
			m_mHammer = bone->WorldMat;
		}
	}
	m_moHammer.CalcBoneMatrix(&m_mHammer);
}

void Player::Draw()
{
	// SampleShader�N���X�ŕ`�悷��
	ShMgr.m_Samp.DrawModel(m_moPla, &m_mObj);

	////=======================================
	//// ����`��
	////=======================================
	ShMgr.m_Samp.DrawModel(m_moHammer, &m_mHammer);

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

//=====================================================
// �u�ҋ@�v���
//=====================================================
void PlayerAS_Wait::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// �����L�[
	if (Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("����", 0, 10, true);
		// �s���؂�ւ�
		SPtr<PlayerAS_Run> p = std::make_shared<PlayerAS_Run>();
		state=p;
		return;
	}
	// �}�E�X���N���b�N
	if (INPUT.MouseCheck_Enter(INPUT.MOUSE_L)) {
		//�A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�U��", 0, 10, false);
		// �s���؂�ւ�
		SPtr<PlayerAS_Attack> p = std::make_shared<PlayerAS_Attack>();
		state=p;
		return;
	}
}
//=====================================================
// �u����v���
//=====================================================
void PlayerAS_Run::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// �ړ��L�[�������Ă�H
	if (!(Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN)) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}
	// �A�j�����x���ړ����x�ɂ���
	//float RunSpeed = (float)Player.GetAnim().GetAnimeSpeed() * 0.05f;
	//Player.m_Mat.Move_Local(0, 0, RunSpeed);

}
//=====================================================
//	�u�U���v���
//=====================================================
void PlayerAS_Attack::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (!INPUT.MouseCheck_Enter(INPUT.MOUSE_L) && anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}
}
//=====================================================
// �ėp�s��
//=====================================================
void PlayerAS_Generic::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}
}