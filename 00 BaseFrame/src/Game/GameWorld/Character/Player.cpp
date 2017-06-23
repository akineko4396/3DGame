#include "main.h"
#include "../GameWorld.h"

void Player::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{

	//�@���f���ǂݍ���
	//m_gmChara=APP.m_ResStg.LoadMesh("data/model/Player/Player2.xed");
	m_moHammer.LoadMesh("data/model/Hammer/hammer.xed");
	//�@���f���f�[�^���Z�b�g
	m_moChara.SetModel(_gm);
	//�@�����̍s��ݒ�
	m_mChara = _m;

	//�@�A�j���[�^��������
	m_moChara.InitAnimator(m_aniPla);
	//�@�����A�j��
	m_aniPla.ChangeAnime_FromName("�ҋ@", true);

	// �L�[���̓R���|�[�l���g����
	SetInput(std::make_shared<KeyInputComponent>()); 

	// �A�N�V�����X�e�[�g
	m_ActionState = std::make_shared<PlayerAS_Wait>();

	m_SkyFlag = 0;
	m_CameraEffectCnt = 0;

	//ID�ݒ�
	m_CharaId = OBJECT_LIST::ID::PLAYER;

	// �J�����ݒ�
	m_Cam.Init(0, 0, -3, false); // �������Ɉ������ʒu
	m_Cam.m_BaseMat.CreateMove(0, 1.7f, 0);
	m_Cam.m_BaseMat.SetPos(0, 1.7f, 0); // �x�[�X�̈ʒu�́A�����炢�̈ʒu
	m_Cam.m_LocalMat.RotateX(15); // ���₷���悤�ɏ��������낷
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
	m_aniPla.AnimationAndScript(1.0, scriptProc, &m_mChara);
	// �S�g��WorldMat���Z�o
	m_moChara.CalcBoneMatrix_SkipRoot(&m_mChara);

	//���̓R���|�[�l���g����
	if (m_Controller) {
		m_Keys = m_Controller->Update();
	}

	// �J�������o�J�E���g
	m_CameraEffectCnt--;
	if (m_CameraEffectCnt < 0)m_CameraEffectCnt = 0;

	POINT* pt = INPUT.GetMouseMoveValue();
	pt->x = pt->x % 360;
	m_Cam.m_BaseMat.RotateY_Local(pt->x*0.5f);

	if (m_ActionState) {
		auto p = m_ActionState;
		m_ActionState->Update(*this, m_aniPla, m_ActionState);
	}

	//�A�j���[�V������i�߂�
	// ���m�ɂ́A�A�j���[�V�����������ƂɁA�S�{�[���́uTransMat�v���X�V����
	m_aniPla.Animation(1.0);

	/*auto bone = m_moChara.SearchBone("��");
	if (bone){
	bone->TransMat.RotateY_Local(45);
	}*/

	//�S�{�[���́uWorldMat�v���uTransMat�v�����ƂɎZ�o����
	// ���ۂɕ`��ȂǂŕK�v�Ȃ̂�����WorldMat�ł�
	m_moChara.CalcBoneMatrix(&m_mChara);

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
		auto bone = m_moChara.SearchBone("�E��_�~�[");
		if (bone) {
			m_mHammer = bone->WorldMat;
		}
	}
	m_moHammer.CalcBoneMatrix(&m_mHammer);
}

void Player::Draw()
{
	// SampleShader�N���X�ŕ`�悷��
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);

	////=======================================
	//// ����`��
	////=======================================
	ShMgr.m_Samp.DrawModel(m_moHammer, &m_mHammer);

	////=======================================
	//// �L�����P �{�[�����\��
	////=======================================
	//YsDx.GetSprite().Begin(true);
	//for (auto& bn : m_moChara.GetBoneTree()){
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

//======================
//�J��������
//======================
void Player::SetCamera()
{
	//=============================================================
	// �ˉe�s��
	//=============================================================
	m_Cam.SetPerspectiveFovLH(60, (float)YsDx.GetRezoW() / YsDx.GetRezoH(), 0.01f, 1000);
	//=============================================================
	// �r���[�s��
	//=============================================================
	// �J�������o��
	if (m_CameraEffectCnt > 0) {
		auto camBone = m_moChara.SearchBone("Camera");
		if (camBone) {
			m_Cam.mCam = camBone->WorldMat;
		}
	}
	// �ʏ펞
	else {
		// �J�����̃x�[�X�s��ɁA�L�����̍��W�����Z����
		YsMatrix mChara;
		mChara = m_Cam.m_BaseMat;
		mChara.GetPos() += m_mChara.GetPos();
		// �ŏI�I�ȃJ�����s������߂�
		m_Cam.mCam = m_Cam.m_LocalMat * mChara;
	}
	// �J�����s�񂩂�r���[�s��쐬
	m_Cam.CameraToView();
}

//=====================================================
// �u�ҋ@�v���
//=====================================================
void PlayerAS_Wait::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// �����L�[
	if (Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("����", 0, 10, true, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_Run> p = std::make_shared<PlayerAS_Run>();
		state=p;
		return;
	}
	// �}�E�X���N���b�N
	if (Player.GetKeys() & GK_X) {
		//�A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�U��", 0, 10, false, 1);
		// �s���؂�ւ�
		SPtr<PlayerAS_Attack> p = std::make_shared<PlayerAS_Attack>();
		state=p;
		return;
	}
	// �X�y�[�X�L�[
	if (Player.GetKeys() & GK_A) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�W�����v(�㏸)", 0, 10, false, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_JumpUp> p = std::make_shared<PlayerAS_JumpUp>();
		state = p;
		return;
	}

	//�Ƃ肠�����\���L�[��
	if (Player.GetKeys() & GK_DOWN) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�̂�����", 0, 10, false, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_KnockBack> p = std::make_shared<PlayerAS_KnockBack>();
		state = p;
		return;
	}

	//�ꎞ�v�Z�p�s��
	YsMatrix mMat;
	//�v���C���[�s��ۑ�
	mMat = Player.GetMatrix();

	// ���C
	/*if (Player.m_SkyFlag == 0) {
		Player.m_vMove *= 0.9f;
	}*/
	// �͈ړ�
	//mMat.Move(Player.m_vMove);

	//�v���C���[�s��ɃZ�b�g
	Player.SetMatrix(mMat);
}
//=====================================================
// �u����v���
//=====================================================
void PlayerAS_Run::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// �ړ��L�[�������Ă�H
	if (!(Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN)) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}

	// �W�����v�U��
	if (Player.GetKeys() & GK_X) {
		//�A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�W�����v�U��", 0, 2, false, 1);
		// �s���؂�ւ�
		SPtr<PlayerAS_JumpAttack> p = std::make_shared<PlayerAS_JumpAttack>();
		state = p;
		return;
	}

	//�ꎞ�v�Z�p�s��
	YsMatrix mMat;
	//�v���C���[�s��ۑ�
	mMat = Player.GetMatrix();

	// �ړ��ɂ�鎋�_�␳
	float rotaAng = 0;
	/*if (Player.GetKeys() & GK_LEFT) {
	rotaAng = -1.0f;
	}
	if (Player.GetKeys() & GK_RIGHT) {
	rotaAng = 1.0f;
	}*/
	if (Player.GetKeys() & GK_LUP) {
		rotaAng *= 0.5f;
	}
	// �J������]
	Player.GetCam().m_BaseMat.RotateY_Local(rotaAng);
	// �L�[�ɂ��L�����̌�������]
	YsVec3 vTar;
	if (Player.GetKeys() & GK_LRIGHT) {
		vTar += Player.GetCam().m_BaseMat.GetXAxis();
	}
	else if (Player.GetKeys() & GK_LLEFT) {
		vTar -= Player.GetCam().m_BaseMat.GetXAxis();
	}
	if (Player.GetKeys() & GK_LUP) {
		vTar += Player.GetCam().m_BaseMat.GetZAxis();
	}
	else if (Player.GetKeys() & GK_LDOWN) {
		vTar -= Player.GetCam().m_BaseMat.GetZAxis();
	}
	vTar.y = 0;
	vTar.Normalize();
	YsVec3 vZ = Player.GetMatrix().GetZAxis();
	vZ.Homing(vTar, 10);
	mMat.SetLookAt(vZ, YsVec3::Up);
	// �A�j�����x���ړ����x�ɂ���
	float walkSpeed = (float)anime.GetAnimeSpeed() * 0.5f;
	mMat.Move_Local(0, 0, walkSpeed);
	// �d��
	//Player.m_vMove.y -= 0.01f;
	// ���C
	/*if (Player.m_SkyFlag == 0) {
		Player.m_vMove *= 0.9f;
	}*/
	// �͈ړ�
	//mMat.Move(Player.m_vMove);

	//�v���C���[�s��ɃZ�b�g
	Player.SetMatrix(mMat);
}
//=====================================================
//	�u�U���v���
//=====================================================
void PlayerAS_Attack::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (!(Player.GetKeys() & GK_X) && anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state = p;
		return;
	}
}
//=====================================================
//	�u�W�����v�U���v���
//=====================================================
void PlayerAS_JumpAttack::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state = p;
		return;
	}
}
//=====================================================
//	�u�W�����v(�㏸)�v���
//=====================================================
void PlayerAS_JumpUp::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�W�����v(�~��)", 0, 10, true, 0.01);
		// �s���؂�ւ�
		SPtr<PlayerAS_JumpDown> p = std::make_shared<PlayerAS_JumpDown>();
		state = p;
		return;
	}

	//�ꎞ�v�Z�p�s��
	YsMatrix mMat;
	//�v���C���[�s��ۑ�
	mMat = Player.GetMatrix();

	// �͈ړ�
	//mMat.Move(Player.m_vMove);

	//�v���C���[�s��ɃZ�b�g
	Player.SetMatrix(mMat);
}
//=====================================================
//	�u�W�����v(�~��)�v���
//=====================================================
void PlayerAS_JumpDown::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state = p;
		return;
	}

	//�ꎞ�v�Z�p�s��
	YsMatrix mMat;
	//�v���C���[�s��ۑ�
	mMat = Player.GetMatrix();

	// �͈ړ�
	//mMat.Move(Player.m_vMove);

	//�v���C���[�s��ɃZ�b�g
	Player.SetMatrix(mMat);
}
//=====================================================
//	�u�̂�����v���
//=====================================================
void PlayerAS_KnockBack::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state = p;
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
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 0.5);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}

	//�ꎞ�v�Z�p�s��
	YsMatrix mMat;
	//�v���C���[�s��ۑ�
	mMat = Player.GetMatrix();

	// ���C
	/*if (Player.m_SkyFlag == 0) {
	Player.m_vMove *= 0.9f;
	}*/
	// �͈ړ�
	//mMat.Move(Player.m_vMove);

	//�v���C���[�s��ɃZ�b�g
	Player.SetMatrix(mMat);
}