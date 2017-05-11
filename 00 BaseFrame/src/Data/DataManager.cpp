#include "main.h"
#include "Game/GameWorld/GameWorld.h"
#include "DataManager.h"


void DataManager::DataLoad(const std::string& _FileName)
{
	std::ifstream ifs;

	//	�ǂݍ���
	ifs.open(_FileName.c_str());

	//	�ǂݍ��ݎ��s
	if (!ifs)
	{
		//	���b�Z�[�W������
		MessageBox(NULL, "�e�L�X�g�t�@�C�����ǂݍ��߂Ă��܂���", "�x��", MB_OK);

		//	���������Ԃ�
		return;
	}


	for (;;)
	{
		std::string line;

		//	��s�ǂݍ���
		getline(ifs, line);

		//	�ǂݍ��ݏI��
		if (ifs.fail())
		{
			break;
		}


		/*---------------------------------------------------------------------

		��؂肽��������ݒ�Avector�z��Ɋi�[(�؂��肽�������͕����w���)

		��
		string sp = "abc";

		sp = GetSplit(line, "ac");

		sp�ɂ�"abc"�̂���a��c���؂���ꂽb�݂̂��A���Ă���

		---------------------------------------------------------------------*/
		std::vector<std::string> sp = GetSplit(line, "(),");


		//	�f�t�H���g�X�e�[�^�X
		YsVec3 vPos = YsVec3(0.0f, 0.0f, 0.0f);
		YsVec3 vScale = YsVec3(1.0f, 1.0f, 1.0f);
		YsVec3 vAngle = YsVec3(0.0f, 0.0f, 0.0f);
		INT		 Id = -1;


		//	�ŏ��̃A�h���X���C�e���[�^�Ɋi�[
		auto FileIt = sp.begin();


		/*-----------------------------------------------------

		�w�肳�ꂽ�^�O�����������ꍇ�A���̃^�O���̐��l��
		�p�ӂ��ꂽ�X�e�[�^�X�p�̕ϐ��ɑ��
		���l��+2�̈ʒu�Ɏw��


		�^�O
		{
		Pos				:	���W�x�N�g��
		Scale			:	�g��x�N�g��
		Angle			:	�p�x�x�N�g��
		Id			:	���ʔԍ�
		}

		-----------------------------------------------------*/

		while (FileIt != sp.end())
		{
			if ((*FileIt) == "Pos")
			{
				FileIt += 2;
				vPos.x = static_cast<float>(atof((*FileIt).c_str()));

				FileIt += 2;
				vPos.y = static_cast<float>(atof((*FileIt).c_str()));

				FileIt += 2;
				vPos.z = static_cast<float>(atof((*FileIt).c_str()));
			}
			else if ((*FileIt) == "Scale")
			{
				FileIt += 2;
				vScale.x = static_cast<float>(atof((*FileIt).c_str()));

				FileIt += 2;
				vScale.y = static_cast<float>(atof((*FileIt).c_str()));

				FileIt += 2;
				vScale.z = static_cast<float>(atof((*FileIt).c_str()));
			}
			else if ((*FileIt) == "Angle")
			{
				FileIt += 2;
				vAngle.x = static_cast<float>(atof((*FileIt).c_str()));

				FileIt += 2;
				vAngle.y = static_cast<float>(atof((*FileIt).c_str()));

				FileIt += 2;
				vAngle.z = static_cast<float>(atof((*FileIt).c_str()));
			}
			else if ((*FileIt) == "Id")
			{
				FileIt += 2;
				Id = atoi((*FileIt).c_str());
			}


			++FileIt;
		}


		//-----------------------------------------------------
		//
		//	Class�^�O�̒����m�F���āA�w�肵��Class���������
		//	�C���X�^���X������ObjectManager�Ƀv�b�V������
		//	�X�e�[�^�X�͐�ɐݒ�l��������
		//
		//-----------------------------------------------------
		FileIt = sp.begin();

		while (FileIt != sp.end())
		{
			// �L�����N�^
			{
				if ((*FileIt) == "Player")
				{
					CreateGameObject<Player>(Id, vPos, vScale, vAngle);
				}
			}

			//�I�u�W�F�N�g
			{
				if ((*FileIt) == "Ground")
				{
					CreateGameObject<Ground>(Id, vPos, vScale, vAngle);
				}
			}

			++FileIt;

		}
	}
}

void DataManager::DataSave(const std::string _FileName)
{



}

/*trim------------------------------------------->

�w�肳�ꂽ�������؂���
�؂�����������̑O��̂���Ȃ������������

_Str				: �؂��肽��������̌�
_TrimCharacterList	: ����Ȃ�������

return : string�^

<-----------------------------------------------*/
static std::string trim(const std::string& _Str, const char* _TrimCharacterList = " \t\v\r\n")
{
	std::string result;

	// ��������g�������镶���ȊO��������ʒu���������܂��B
	std::string::size_type left = _Str.find_first_not_of(_TrimCharacterList);

	if (left != std::string::npos)
	{
		// ��������g�������镶���ȊO�����������ꍇ�́A�����悤�ɉE��������������܂��B
		std::string::size_type right = _Str.find_last_not_of(_TrimCharacterList);

		// �߂�l�����肵�܂��B�����ł͉E�����猟�����Ă��A�g�������镶���ȊO���K�����݂���̂Ŕ���s�v�ł��B
		result = _Str.substr(left, right - left + 1);
	}

	return result;
}


std::vector<std::string> DataManager::GetSplit(
	std::string _Str,
	std::string _Split)
{
	//	�������i�[���邽�߂̕ϐ�
	std::vector<std::string> vecRet;


	//	�������������̂����̂����ꂩ���q�b�g�����
	while (_Str.find_first_of(_Split) != std::string::npos)
	{

		//	�؂��肽���������ݒ�
		_Str = trim(_Str, " ");
		_Str = trim(_Str, "\t\v\r\n");

		//	�؂��肽�����������擾
		int Cp = _Str.find_first_of(_Split);

		//	����������݂̂������ꍇ
		if (Cp <= 0)
		{
			Cp += 1;
		}

		//	�擪�󕶎����i�[����Ȃ��悤��
		if (Cp > 0)
		{

			//	�i�[
			vecRet.push_back(_Str.substr(0, Cp));

		}

		//	��؂蕶�����񕶎��ȏ�ɑΉ�
		_Str = _Str.substr(Cp);
	}

	//	���X�g��Ԃ�
	return vecRet;
}