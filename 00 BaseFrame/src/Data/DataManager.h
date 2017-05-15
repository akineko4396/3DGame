#pragma once

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

	return			:	�I�u�W�F�N�g����Ԃ�

	--------------------------------------------*/
	int DataLoad(const std::string& _FileName);

	/*DataLoad------------------------------------

	�O���t�@�C���ɏ�������
	�Q�[���Ɏg�p�����L�����N�^��I�u�W�F�N�g��
	�e�L�X�g�t�@�C���ɏ����o��

	_FileName		:	�t�@�C���p�X

	return			:	�߂�l�Ȃ�

	--------------------------------------------*/
	void DataSave(const std::string _FileName, int _num);

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
		INT						_SetNum,
		YsVec3					_SetPosition,
		YsVec3					_SetScale,
		YsVec3					_SetAngle
		)
	{
		//�@���X�g�ɃC���X�^���X�������I�u�W�F�N�g���v�b�V������
		SPtr<T> add = ObjectBase::CreateObjectTask<T>();

		//�@���ʔԍ����Z�b�g����
		add->SetNum(_SetNum);

		//�@���W���Z�b�g����
		add->SetPos(_SetPosition);

		//�@�g��T�C�Y���Z�b�g����
		add->SetScale(_SetScale);

		//�@��]�ʂ��Z�b�g����
		add->SetAngle(_SetAngle);

		//�@�I�u�W�F�N�g�̏�����������
		add->Init();
	}

};