#pragma once

//====================
// namespace
//====================
namespace OBJECT_LIST {

	enum ID {

		//�v���C���[
		PLAYER					=	0,

		//�{�X
		BOSS						=	1,

		//�X�P���g��
		SKELETON				=	2,

		//�f�[����
		DEMON					=	3,

		//�X�e�[�W
		GROUND				=	4,

		//���_
		STRONGHOLD		=	5,

		//��
		WALL					=	6,

		//���Ί�
		SLING					=	7,

		//��C
		CANNON				=	8,

		//�Ή����ˊ�
		FLAMETHROWER	=	9,

		//�v���X�@
		PRESS					=	10,

		//�A�[��
		ARM						=	11,

		//�x���g�R���x�A
		BELTCONVEYOR		=	12,

		//�u���b�W
		BRIDGE					=	13,

		//�I�u�W�F�N�g�ő吔
		MAX_NUM,

		//������
		FREE				= -1,

	};

}

//===================================
// �L�����N�^�[���N���X
// �@�v���C���[�Ȃǂ̃N���X���Ǘ�����
//===================================
class CharacterBase :public BaseGameObj
{
public:

	//==================================
	// m_oList�Ǘ��p�֐�
	//==================================
	//���X�g�ɃI�u�W�F�N�g��o�^
	static void PushChara(SPtr<CharacterBase> _obj) { m_cList.push_back(_obj); }

	//�I�u�W�F�N�g�S�Ă��X�V
	static void AllUpdate();

	//�I�u�W�F�N�g�S�Ă�`��
	static void AllDraw();

	//�I�u�W�F�N�g�S�Ă����
	static void FullClear();

	//�L���t���O���m�F
	static void CheckKillFlg();

	//���X�g�̃Q�b�^�[
	static std::vector<SPtr<CharacterBase>> & GetList() { return m_cList; }

	//�J��������
	virtual void SetCamera() {}

	//===========
	// �Q�b�^�[
	//===========

	//�s����Z�b�g����
	inline void SetMatrix(const YsMatrix _Mat) { m_mChara = _Mat; }

	//���W���Z�b�g����
	inline void SetPos(const YsVec3 _pos) { m_vPos = _pos; }

	//�g��T�C�Y���Z�b�g
	inline void SetScale(const YsVec3 _scale) { m_vScale = _scale; }

	//��]�ʂ��Z�b�g
	inline void SetAngle(const YsVec3 _angle) { m_vAngle = _angle; }

	//�L���t���O���Z�b�g����
	inline void SetKillFlg(const int _k) { m_killFlg = _k; }

	// ���̓R���g���[��(�R���|�[�l���g)���Z�b�g
	inline void SetInput(SPtr<GameInputComponent> p) {
		m_Controller = p;
	}

	//===========
	// �Z�b�^�[
	//===========

	//���f���f�[�^��Ԃ�
	inline YsModelObject& GetModel() { return m_moChara; }

	//�s���Ԃ�
	inline YsMatrix GetMatrix() { return m_mChara; }

	//���W��Ԃ�
	inline YsVec3	GetPos() { return m_mChara.GetPos(); }

	//�g��T�C�Y��Ԃ�
	inline YsVec3 GetScale() { return m_mChara.GetScale(); }

	//�s�񂩂��]�ʂ�Ԃ�
	inline YsVec3 GetAxis() { return YsVec3(m_mChara.GetXAxis().x, m_mChara.GetYAxis().y, m_mChara.GetZAxis().z); }

	//���ډ�]�ʂ�Ԃ�
	inline YsVec3 GetAngle() { return m_vAngle; }

	//�L���t���O�̏���Ԃ�
	inline int	GetKillFlg() { return m_killFlg; }

	//�I�u�W�F�N�gID���擾
	inline int	GetObjId() { return m_CharaId; }

	// ���݉�����Ă���L�[���擾
	inline int GetKeys() { return m_Keys; }


	//	�w�肳�ꂽ�N���X���C���X�^���X�����ă��X�g�Ɋi�[����
	template <class T>
	inline static SPtr<T> CreateCharaTask()
	{
		SPtr<T> add(new T);
		PushChara(add);
		return add;
	}

protected:

	//���X�g
	static std::vector<SPtr<CharacterBase>> m_cList;
	
	//	���f���f�[�^
	YsModelObject		m_moChara;

	// �s��
	YsMatrix			m_mChara;

	// �L�����̍��W
	YsVec3			m_vPos;

	// �L�����̊g��T�C�Y
	YsVec3			m_vScale;

	//�L�����̉�]��
	YsVec3			m_vAngle;

	//�I�u�W�F�N�gID
	int				m_CharaId;

	//�L���t���O
	int				m_killFlg;

	// ���݉�������Ă�L�[ ���̃L�[���ɂ��L�����𓮂���(Player��AI��)
	// �e�r�b�g(0�`31)���e�L�[�̏��
	int m_Keys = 0;

	// ���̓R���g���[��
	SPtr<GameInputComponent> m_Controller;
};