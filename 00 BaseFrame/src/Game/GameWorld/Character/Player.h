#pragma once

//�O���錾
class BasePlayerAS;

//====================================
// �v���C���[�N���X
//====================================
class Player :public ObjectBase
{
public: 

	Player() { m_ObjId = OBJECT_LIST::ID::PLAYER; }

	//�������ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;
	

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

//=====================================

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