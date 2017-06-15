#pragma once

//�O���錾
class BasePlayerAS;

//====================================
// �v���C���[�N���X
//====================================
class Player :public ObjectBase
{
public: 

	//�������ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

	//�J��������
	virtual void SetCamera() override;

	//�J�����̏����Ƃ��Ă���
	inline GameCamera GetCam() { return m_Cam; }
	

private:

	//���f���f�[�^
	YsModelObject	m_moPla;

	// �A�j���[�^�[
	YsAnimator		m_aniPla;

	//�n���}�[
	YsModelObject	m_moHammer;
	YsMatrix			m_mHammer;
	
	// �s�����Ƃɕω�����A�N�V�����X�e�[�g
	SPtr<BasePlayerAS> m_ActionState;

	//���ϗp�̊p�x
	float				m_NormalAngleY;

	//----------------------------------
	// �J�����֌W
	//----------------------------------
	int m_CameraEffectCnt = 0; // �J�������o�J�E���g
	GameCamera m_Cam; // �J���� �ړ��̊�ɂ��Ȃ�

public:

	//�ړ���
	YsVec3			m_vMove;

	int m_SkyFlag = 0; // 0:�n�� 1:��

	//�W�����v��
	float				m_JumpPower;
};

//======================================
//Player�A�N�V������{�N���X
//======================================
class BasePlayerAS
{
public:
	virtual ~BasePlayerAS(){}
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state){}
};

//======================================
//�u�ҋ@�v���
//======================================
class PlayerAS_Wait:public BasePlayerAS
{
public:
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//�u����v���
//======================================
class PlayerAS_Run:public BasePlayerAS
{
public:
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//�u�U���v���
//======================================
class PlayerAS_Attack:public BasePlayerAS
{
public:
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//�u�W�����v�U���v���
//======================================
class PlayerAS_JumpAttack :public BasePlayerAS
{
public:
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//�u�W�����v(�㏸)�v���
//======================================
class PlayerAS_JumpUp :public BasePlayerAS
{
public:
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//�u�W�����v(�~��)�v���
//======================================
class PlayerAS_JumpDown :public BasePlayerAS
{
public:
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//�u�̂�����v���
//======================================
class PlayerAS_KnockBack :public BasePlayerAS
{
public:
	//������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//=====================================================
// �ėp�s��
// �A�j���[�V�������I��������u�����v�ɖ߂邾��
//=====================================================
class PlayerAS_Generic : public BasePlayerAS 
{
public:
	// ������s�����
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};