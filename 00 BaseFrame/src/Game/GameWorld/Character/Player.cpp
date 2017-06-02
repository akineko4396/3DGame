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
	m_mObj.Scale_Local(m_vScale);
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

	m_SkyFlag = 0;
	m_CameraEffectCnt = 0;

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
	m_aniPla.AnimationAndScript(1.0, scriptProc, &m_mObj);
	// �S�g��WorldMat���Z�o
	m_moPla.CalcBoneMatrix_SkipRoot(&m_mObj);

	//���̓R���|�[�l���g����
	if (m_Controller) {
		m_Keys = m_Controller->Update();
	}
	/*//�e���v���[�g
	YsVec3			m_vTmpVec = YsVec3(0, 0, 0);
	//�ړ���
	YsVec3			m_vToVec = YsVec3(0, 0, 0);

	YsMatrix	mRot;
	//A�L�[
	if (m_Keys&GK_LLEFT) {
		//m_mObj.Move_Local(-0.3f, 0.0f, 0.0f);
		D3DXMatrixRotationY(&mRot, D3DXToRadian(m_NormalAngleY));
		D3DXVec3TransformCoord(&m_vTmpVec, &YsVec3(-0.1, 0, 0), &mRot);
		m_vToVec += m_vTmpVec;
		MovePosition(m_vToVec);
	}
	//W�L�[
	/*static POINT *pt = INPUT.GetMouseMoveValue();
	static POINT *oldpt;
	pt->x = pt->x % 360;
	oldpt = pt;
	static float p = 0;
	if (INPUT.KeyCheck_Enter('W')) {
		m_mObj.RotateY_Local(p*0.5f);
		p = 0;
	}
	if (m_Keys&GK_LUP) {
		pt = INPUT.GetMouseMoveValue();
		pt->x = pt->x % 360;
		m_mObj.Move_Local(0.0f, 0.0f, 0.3f);
		m_mObj.RotateY_Local(pt->x*0.5f);
	}
	else {
		p += INPUT.GetMouseMoveValue()->x;
	}

	else if (m_Keys&GK_LUP) {
		D3DXMatrixRotationY(&mRot, D3DXToRadian(m_NormalAngleY));
		D3DXVec3TransformCoord(&m_vTmpVec, &YsVec3(0, 0, 0.1), &mRot);
		m_vToVec += m_vTmpVec;
		MovePosition(m_vToVec);
	}

	//D�L�[
	else if (m_Keys&GK_LRIGHT) {
		//m_mObj.Move_Local(0.3f, 0.0f, 0.0f);
		D3DXMatrixRotationY(&mRot, D3DXToRadian(m_NormalAngleY));
		D3DXVec3TransformCoord(&m_vTmpVec, &YsVec3(0.1, 0, 0), &mRot);
		m_vToVec += m_vTmpVec;
		MovePosition(m_vToVec);
	}
	//S�L�[
	else if (m_Keys&GK_LDOWN) {
		//m_mObj.Move_Local(0.0f, 0.0f, -0.3f);
		D3DXMatrixRotationY(&mRot, D3DXToRadian(m_NormalAngleY));
		D3DXVec3TransformCoord(&m_vTmpVec, &YsVec3(0, 0, -0.1), &mRot);
		m_vToVec += m_vTmpVec;
		MovePosition(m_vToVec);
	}*/

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

	//===========================================================
	// �W�����v����
	//===========================================================
	// ��Ɨp�ϐ�
	/*static float		JUMP_POWER;			//�W�����v��
	const static float	GRAVITY = 0.01f;			//�d��
	static float		Jump;				//Y�ړ���
	static float		prev;				//�W�����v�����Ƃ��̍��W�ۑ��p
	static bool			m_JumpFlg = false;		//�W�����v���Ă��邩�̃t���O
	static bool			m_UpDownFlg = false;	//�㏸�����t���O

	if (INPUT.KeyCheck_Enter(VK_SPACE) && !m_JumpFlg && !m_UpDownFlg){
		m_JumpFlg = true;
		JUMP_POWER = 0.1;
		prev = m_mObj.GetPos().y;
		Jump = 0;
	}
	if (m_JumpFlg){
		if (!m_UpDownFlg) {
			JUMP_POWER -= GRAVITY;
			Jump += JUMP_POWER;
			if (JUMP_POWER >= 0) {
				m_UpDownFlg = true;
			}
		}
		else if(m_UpDownFlg) {
			static YsVec3	Pos;				//�v���C���[��Y���W�ꎞ�ۑ��p
			Pos = m_mObj.GetPos();

			JUMP_POWER -= GRAVITY;
			Jump += JUMP_POWER;

			if (Pos.y <= 0) {
				m_JumpFlg = false;
				m_UpDownFlg = false;
				Jump = prev - Pos.y;
			}
		}
		m_mObj.Move_Local(0.0f, Jump, 0.0f);
	}*/

	//UpdateMatrix();

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

//==========================
//�s��X�V
//==========================
void Player::UpdateMatrix()
{
	//�}�E�X��Y����]�ʂ��擾
	m_NormalAngleY = INPUT.GetMouseMoveValue()->x;

	//�g��
	m_mObj.CreateScale(m_vScale);

	//���W�Z�b�g
	m_mObj.Move(m_vPos);

	//Y���Z�b�g
	m_mObj.RotateY_Local(m_vAngle.y);

	//X���Z�b�g
	m_mObj.RotateX_Local(m_vAngle.x);

	//Z���Z�b�g
	m_mObj.RotateZ_Local(m_vAngle.z);
}

//==========================
//���W�ړ�
//==========================
void Player::MovePosition(YsVec3& _ToVec)
{
	//���݂̌����Ă�����p
	YsVec3	NowVec;

	//�ړ���
	m_vPos.Add(_ToVec);

	//��]�ʂ��Z�b�g
	m_mObj.CreateRotateY(m_vAngle.y);

	//�����Ă�����p�����߂�
	D3DXVec3TransformNormal(&NowVec, &YsVec3(0, 0, 1), &m_mObj);

	//���K��
	_ToVec.Normalize();

	//���ς����߂�
	float Dot = _ToVec.Dot(NowVec);

	//�p�x�Ԋ�
	Dot = D3DXToDegree(acos(Dot));

	//���ς�������x�̒l�𒴂��Ă�����
	if (Dot >= 0.1f)
	{
		//�O�ς����߂�
		YsVec3 Cross;
		Cross.Cross(Cross, NowVec, _ToVec);

		//���K��
		Cross.Normalize();

		//���ς̉�]��
		if (Dot >= 10) {
			//�I�[�o�[���Ȃ��悤��
			Dot = 10.0f;
		}
		//�O�ς�������x�������
		if (Cross.y >= 0.9f) {
			//Y���ɓ��ς����Z
			m_vAngle.y += Dot;
		}
		else if (Cross.y <= -0.9f) {
			//Y���ɓ��ς����Z
			m_vAngle.y -= Dot;
		}
		else {
			//Y���ɓ��ς����Z
			m_vAngle.y += Dot;
		}
		//���]���Ȃ��悤��
		m_vAngle.y = static_cast<float>((int)m_vAngle.y % 360);
	}
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
		auto camBone = m_moPla.SearchBone("Camera");
		if (camBone) {
			m_Cam.mCam = camBone->WorldMat;
		}
	}
	// �ʏ펞
	else {
		// �J�����̃x�[�X�s��ɁA�L�����̍��W�����Z����
		YsMatrix mChara;
		mChara = m_Cam.m_BaseMat;
		mChara.GetPos() += m_mObj.GetPos();
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
		anime.ChangeAnimeSmooth_FromName("����", 0, 10, true, 1);
		// �s���؂�ւ�
		SPtr<PlayerAS_Run> p = std::make_shared<PlayerAS_Run>();
		state=p;
		return;
	}
	// �}�E�X���N���b�N
	if (INPUT.MouseCheck_Enter(INPUT.MOUSE_L)) {
		//�A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�U��", 0, 10, false, 1);
		// �s���؂�ւ�
		SPtr<PlayerAS_Attack> p = std::make_shared<PlayerAS_Attack>();
		state=p;
		return;
	}

	// ���C
	/*if (Player.m_SkyFlag == 0) {
		Player.m_vMove *= 0.9f;
	}
	// �͈ړ�
	Player.GetMatrix().Move(Player.m_vMove);*/
}
//=====================================================
// �u����v���
//=====================================================
void PlayerAS_Run::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// �ړ��L�[�������Ă�H
	if (!(Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN)) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 1);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}

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
	Player.GetMatrix().SetLookAt(vZ, YsVec3::Up);
	// �A�j�����x���ړ����x�ɂ���
	float walkSpeed = (float)anime.GetAnimeSpeed() * 0.05f;
	Player.GetMatrix().Move_Local(0, 0, walkSpeed);
	// �d��
	//Player.m_vMove.y -= 0.01f;
	// ���C
	/*if (Player.m_SkyFlag == 0) {
		Player.m_vMove *= 0.9f;
	}
	// �͈ړ�
	Player.GetMatrix().Move(Player.m_vMove);*/
}
//=====================================================
//	�u�U���v���
//=====================================================
void PlayerAS_Attack::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (!INPUT.MouseCheck_Enter(INPUT.MOUSE_L) && anime.IsAnimationEnd()) {
		// �A�j���؂�ւ�
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 1);
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
		anime.ChangeAnimeSmooth_FromName("�ҋ@", 0, 10, true, 1);
		// �s���؂�ւ�
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}

	// ���C
	/*if (Player.m_SkyFlag == 0) {
		Player.m_vMove *= 0.9f;
	}
	// �͈ړ�
	Player.GetMatrix().Move(Player.m_vMove);*/
}