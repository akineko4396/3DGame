#pragma once

//======================
// �O���錾
//======================

//�L�����N�^�[�x�[�X�N���X
class CharacterBase;

//�I�u�W�F�N�g�x�[�X�N���X
class ObjectBase;

//=================================================
// �f�[�^��ǂݏ�������N���X
//=================================================

class DataManager
{
public:

	/*DataLoad------------------------------------

	�O���t�@�C����ǂݍ���
	�Q�[���Ɏg�p����L�����N�^��I�u�W�F�N�g��
	�C���X�^���X�����ă��X�g�Ɋi�[����

	_FileName		:	�t�@�C���p�X

	return			:	�߂�l�Ȃ�

	--------------------------------------------*/
	void DataLoad(const std::string _FileName);

	/*DataLoad------------------------------------

	�O���t�@�C���ɏ�������
	�Q�[���Ɏg�p�����L�����N�^��I�u�W�F�N�g��
	�e�L�X�g�t�@�C���ɏ����o��

	_FileName		:	�t�@�C���p�X

	return			:	�߂�l�Ȃ�

	--------------------------------------------*/
	void DataSave(const std::string _FileName);

	/*GetSplit--------------------------------->

	�w�肵��������؂�����
	�f�[�^�ƂȂ镶�����Ԃ�
	�߂�l�Ƃ��Đ؂������������Ԃ�

	_Str	:	���ƂȂ镶����
	_Split	:	�؂��肽��������(������)

	return	:	vector�^

	<----------------------------------------*/
	std::vector<std::string> GetSplit(
		std::string _Str,
		std::string _Split
		);

	/*(template)CreateGameCharacter---------------

	CharacterBase�Ƀv�b�V�����ď��������s��

	template		:	�v�b�V������N���X
	_SetId			:	���ʔԍ�
	_SetPosition	:	���W
	_SetScale		:	�g��T�C�Y
	_SetAngle		:	�p�x

	return			:	�߂�l�Ȃ�

	-----------------------------------------*/
	template <class T>
	inline void CreateGameCharacter(
		INT						_SetId,
		YsVec3					_SetPosition,
		YsVec3					_SetScale,
		YsVec3					_SetAngle
		)
	{
		//�@���X�g�ɃC���X�^���X�������I�u�W�F�N�g���v�b�V������
		SPtr<T> add = CharacterBase::CreateCharacterTask<T>();

		//�@���ʔԍ����Z�b�g����
		add->SetId(_SetId);

		//�@���W���Z�b�g����
		add->SetPos(_SetPosition);

		//�@�g��T�C�Y���Z�b�g����
		add->SetScale(_SetScale);

		//�@��]�ʂ��Z�b�g����
		add->SetAngle(_SetAngle);

		//�@�L�����N�^�̏�����������
		add->Init();
	}

	/*(template)CreateGameObject---------------

	ObjectBase�Ƀv�b�V�����ď��������s��

	template		:	�v�b�V������N���X
	_SetId			:	���ʔԍ�
	_SetPosition	:	���W
	_SetScale		:	�g��T�C�Y
	_SetAngle		:	�p�x

	return			:	�߂�l�Ȃ�

	-----------------------------------------*/
	template <class T>
	inline void CreateGameObject(
		INT						_SetId,
		YsVec3					_SetPosition,
		YsVec3					_SetScale,
		YsVec3					_SetAngle
		)
	{
		//�@���X�g�ɃC���X�^���X�������I�u�W�F�N�g���v�b�V������
		SPtr<T> add = ObjectBase::CreateCharacterTask<T>();

		//�@���ʔԍ����Z�b�g����
		add->SetId(_SetId);

		//�@���W���Z�b�g����
		add->SetPos(_SetPosition);

		//�@�g��T�C�Y���Z�b�g����
		add->SetScale(_SetScale);

		//�@��]�ʂ��Z�b�g����
		add->SetAngle(_SetAngle);

		//�@�I�u�W�F�N�g�̏�����������
		add->Init();
	}

	//================================
	//�@�V���O���g���p�^�[��
	//================================
private:
	//�C���X�^���X�p
	static DataManager*	s_pdmInst;

	//�O������C���X�^���X�������Ȃ�����private�R���X�g���N�^
	DataManager(){
	}

public:

	//�f�[�^�}�l�[�W���[�폜
	static void DeleteDataManager(){
		YsSafe_Delete(s_pdmInst);
	}

	//�f�[�^�}�l�[�W���[�쐬
	static void CreateDataManager(){
		DeleteDataManager();
		s_pdmInst = new DataManager();
	}

	//�f�[�^�}�l�[�W���[�擾
	static DataManager& GetDataManager(){
		return *s_pdmInst;
	}
};

#define DM DataManager::GetDataManager()