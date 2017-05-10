#pragma once

//===================================
// �L�����N�^�[�̊��N���X
// �@�L�����N�^�[�̃N���X���Ǘ�����
//===================================
class CharacterBase :public BaseGameObj
{
public:

	//==================================
	// m_cList�Ǘ��p�֐�
	//==================================
	//���X�g�ɃI�u�W�F�N�g��o�^
	static void PushObject(SPtr<CharacterBase> _obj){ m_cList.push_back(_obj); }

	//�I�u�W�F�N�g�S�Ă��X�V
	static void AllUpdate();

	//�I�u�W�F�N�g�S�Ă�`��
	static void AllDraw();

	//�I�u�W�F�N�g�S�Ă����
	static void FullClear();

	//�L���t���O���m�F
	static void CheckKillFlg();

	//���X�g�̃Q�b�^�[
	static std::vector<SPtr<CharacterBase>> & GetList(){ return m_cList; }

	//���ʔԍ�
	enum { PLAYER };

	//�I�u�W�F�N�g����Ԃ�
	static SPtr<CharacterBase>	GetThisCharacter(int _id);

	//===========
	// �Z�b�^�[
	//===========

	//���W���Z�b�g����
	inline void SetPos(const YsVec3 _pos){ m_vPos = _pos; }

	//�g��T�C�Y���Z�b�g
	inline void SetScale(const YsVec3 _scale){ m_vScale = _scale; }

	//��]�ʂ��Z�b�g
	inline void SetAngle(const YsVec3 _angle){ m_vAngle = _angle; }

	//�L���t���O���Z�b�g����
	inline void SetKillFlg(const int _k){ m_killFlg = _k; }

	//��ID���Z�b�g
	inline void SetId(const int _n){ m_Id = _n; }

	//===========
	// �Q�b�^�[
	//===========

	//�s���Ԃ�
	inline YsMatrix GetMatrix(){ return m_Mat; }

	//�L���t���O�̏���Ԃ�
	inline int	GetKillFlg(){ return m_killFlg; }

	//��ID���擾
	inline int	GetId(){ return m_Id; }


	//	�w�肳�ꂽ�N���X���C���X�^���X�����ă��X�g�Ɋi�[����
	template <class T>
	inline SPtr<T> CreateCharacterTask()
	{
		SPtr<T> add(new T);
		PushObject(add);
		return add;
	}

protected:

	// ���f���f�[�^
	SPtr<YsGameModel>		m_gmChara;

	// �L�����̍s��
	YsMatrix		m_mChara;

	// �L�����̍��W
	YsVec3			m_vPos;

	// �L�����̊g��T�C�Y
	YsVec3			m_vScale;

	//�L�����̉�]��
	YsVec3			m_vAngle;

	//���f��ID
	int				m_Id;

	//�L���t���O
	int				m_killFlg;

	//���X�g
	static std::vector<SPtr<CharacterBase>> m_cList;

};