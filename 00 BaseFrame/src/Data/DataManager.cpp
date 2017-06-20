#include "main.h"
#include "Game/GameWorld/GameWorld.h"
#include "DataManager.h"
#include "FilePath.h"


int DataManager::TxtDataLoad(const std::string& _FileName)
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
		return 0;
	}

	int num_cnt = 0;

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
			/*else if ((*FileIt) == "Id")
			{
				FileIt += 2;
				Id = atoi((*FileIt).c_str());
			}*/


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
			//====================
			// �L�����N�^
			//====================
			//�v���C���[
			{
				if ((*FileIt) == "Player")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(PLAYER_PATH);

					CreateGameObject<Player>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::PLAYER);
					num_cnt++;
				}
			}

			//====================
			//�I�u�W�F�N�g
			//====================
			//�X�e�[�W
			{
				if ((*FileIt) == "Ground")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(GROUND_PATH);

					CreateGameObject<Ground>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::GROUND);
					num_cnt++;
				}
			}

			//���_
			{
				if ((*FileIt) == "Stronghold")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Stronghold>(num_cnt, vPos, vScale, vAngle, drawModel,OBJECT_LIST::ID::STRONGHOLD);
					num_cnt++;
				}
			}

			//��
			{
				if ((*FileIt) == "Wall")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Wall>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::WALL);
					num_cnt++;
				}
			}

			//���Ί�
			{
				if ((*FileIt) == "Sling")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Sling>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::SLING);
					num_cnt++;
				}
			}

			//��C
			{
				if ((*FileIt) == "Cannon")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Cannon>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::CANNON);
					num_cnt++;
				}
			}

			//�Ή����ˊ�
			{
				if ((*FileIt) == "Flamethrower")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Flamethrower>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::FLAMETHROWER);
					num_cnt++;
				}
			}

			//�v���X�@
			{
				if ((*FileIt) == "Press")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Press>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::PRESS);
					num_cnt++;
				}
			}

			//�A�[��
			{
				if ((*FileIt) == "Arm")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(ARM_PATH);

					CreateGameObject<Arm>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::ARM);
					num_cnt++;
				}
			}

			//�x���g�R���x�A
			{
				if ((*FileIt) == "Belt")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(BELT_PATH);

					CreateGameObject<BeltConveyor>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::BELTCONVEYOR);
					num_cnt++;
				}
			}

			//�u���b�W
			{
				if ((*FileIt) == "Bridge")
				{
					// �`��p���b�V���ǂݍ���
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(BRIDGE_PATH);

					CreateGameObject<Bridge>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::BRIDGE);
					num_cnt++;
				}
			}

			++FileIt;

		}
	}

	return num_cnt;
}

void DataManager::TxtDataSave(const std::string& _FileName, int _num)
{

	std::ofstream ofs;

	// �ǂݍ���
	ofs.open(_FileName.c_str());

	//	�ǂݍ��ݎ��s
	if (!ofs)
	{
		//	���b�Z�[�W������
		MessageBox(NULL, "�e�L�X�g�t�@�C�����ǂݍ��߂Ă��܂���", "�x��", MB_OK);

		//	���������Ԃ�
		return;
	}

	// �e�L�X�g���̃f�[�^������
	ofs.trunc;

	//��Ɨp�ϐ�
	static int num_cnt;
	YsVec3 Pos = YsVec3(0.0f, 0.0f, 0.0f);
	YsVec3 Scale = YsVec3(1.0f, 1.0f, 1.0f);
	YsVec3 Angle = YsVec3(0.0f, 0.0f, 0.0f);

	//���X�g�������ׂĉ�
	for (num_cnt = 0; num_cnt < _num; num_cnt++) {

		//���f�[�^���i�[
		Pos = HELP.GetObject_All(num_cnt)->GetPos();
		Scale = HELP.GetObject_All(num_cnt)->GetScale();
		if (HELP.GetObject_All(num_cnt)->GetObjId() == OBJECT_LIST::ID::PLAYER) {
			Angle = HELP.GetObject_All(num_cnt)->GetAxis();
		}
		else {
			Angle = HELP.GetObject_All(num_cnt)->GetAngle();
		}


		//�N���X���ۑ�
		switch (HELP.GetObject_All(num_cnt)->GetObjId()) {
			//�v���C���[
		case OBJECT_LIST::ID::PLAYER:
			ofs << "ClassName(Player)" << TXT_DATA_SAVE << std::endl; break;
			//�G�l�~�[
		case OBJECT_LIST::ID::ENEMY:
			ofs << "ClassName(Enemy)" << TXT_DATA_SAVE << std::endl; break;
			//�X�e�[�W
		case OBJECT_LIST::ID::GROUND:
			ofs << "ClassName(Ground)" << TXT_DATA_SAVE << std::endl; break;
			//���_
		case OBJECT_LIST::ID::STRONGHOLD:
			ofs << "ClassName(Stronghold)" << TXT_DATA_SAVE << std::endl; break;
			//��
		case OBJECT_LIST::ID::WALL:
			ofs << "ClassName(Wall)" << TXT_DATA_SAVE << std::endl; break;
			//���Ί�
		case OBJECT_LIST::ID::SLING:
			ofs << "ClassName(Sling)" << TXT_DATA_SAVE << std::endl; break;
			//��C
		case OBJECT_LIST::ID::CANNON:
			ofs << "ClassName(Cannon)" << TXT_DATA_SAVE << std::endl; break;
			//�Ή����ˊ�
		case OBJECT_LIST::ID::FLAMETHROWER:
			ofs << "ClassName(Flamethrower)" << TXT_DATA_SAVE << std::endl; break;
			//�v���X�@
		case OBJECT_LIST::ID::PRESS:
			ofs << "ClassName(Press)" << TXT_DATA_SAVE << std::endl; break;
			//�A�[��
		case OBJECT_LIST::ID::ARM:
			ofs << "ClassName(Arm)" << TXT_DATA_SAVE << std::endl; break;
			//�x���g�R���x�A
		case OBJECT_LIST::ID::BELTCONVEYOR:
			ofs << "ClassName(Belt)" << TXT_DATA_SAVE << std::endl; break;
			//�u���b�W
		case OBJECT_LIST::ID::BRIDGE:
			ofs << "ClassName(Bridge)" << TXT_DATA_SAVE << std::endl; break;
		}
	}

	//�t�@�C���N���[�Y
	ofs.close();
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







int DataManager::CsvDataLoad(const std::string& _FileName)
{
	//�I�u�W�F�N�g��������
	int num_cnt = 0;

	//===========================
	// CSV�f�[�^�ǂݍ���
	//===========================
	csv.Load(_FileName);

	//�ǂݍ��݁E�z�u(�O�s�ڂ̓^�C�g���s�Ȃ̂ŁA�P�s�ڂ���)
	for (UINT i = 1; i < csv.m_Tbl.size(); i++) {
		// �f�[�^�擾
		std::string modelName = csv.GetCol(i, "���f����");
		YsVec3 pos;
		pos.x = std::stof(csv.GetCol(i, "X���W"));
		pos.y = std::stof(csv.GetCol(i, "Y���W"));
		pos.z = std::stof(csv.GetCol(i, "Z���W"));
		float size = std::stof(csv.GetCol(i, "�T�C�Y"));
		YsVec3 rotate;
		rotate.x = std::stof(csv.GetCol(i, "�p�xX"));
		rotate.y = std::stof(csv.GetCol(i, "�p�xY"));
		rotate.z = std::stof(csv.GetCol(i, "�p�xZ"));
		std::string className = csv.GetCol(i, "�N���X");

		// �`��p���b�V���ǂݍ���
		SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(modelName);

		YsVec3 scale = YsVec3(size, size, size);

		//====================
		// �L�����N�^
		//====================
		//�v���C���[
		{
			if (className == "Player")
			{
				CreateGameObject<Player>(num_cnt, pos, scale, rotate, drawModel,OBJECT_LIST::ID::PLAYER);
				num_cnt++;
			}
		}

		//====================
		//�I�u�W�F�N�g
		//====================
		//�X�e�[�W
		{
			if (className == "Ground")
			{
				CreateGameObject<Ground>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::GROUND);
				num_cnt++;
			}
		}

		//���_
		{
			if (className == "Stronghold")
			{
				CreateGameObject<Stronghold>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::STRONGHOLD);
				num_cnt++;
			}
		}

		//��
		{
			if (className == "Wall")
			{
				CreateGameObject<Wall>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::WALL);
				num_cnt++;
			}
		}

		//���Ί�
		{
			if (className == "Sling")
			{
				CreateGameObject<Sling>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::SLING);
				num_cnt++;
			}
		}

		//��C
		{
			if (className == "Cannon")
			{
				CreateGameObject<Cannon>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::CANNON);
				num_cnt++;
			}
		}

		//�Ή����ˊ�
		{
			if (className == "Flamethrower")
			{
				CreateGameObject<Flamethrower>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::FLAMETHROWER);
				num_cnt++;
			}
		}

		//�v���X�@
		{
			if (className == "Press")
			{
				CreateGameObject<Press>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::PRESS);
				num_cnt++;
			}
		}

		//�A�[��
		{
			if (className == "Arm")
			{
				CreateGameObject<Arm>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::ARM);
				num_cnt++;
			}
		}

		//�x���g�R���x�A
		{
			if (className == "BeltConveyor")
			{
				CreateGameObject<BeltConveyor>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::BELTCONVEYOR);
				num_cnt++;
			}
		}

		//�u���b�W
		{
			if (className == "Bridge")
			{
				CreateGameObject<Bridge>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::BRIDGE);
				num_cnt++;
			}
		}
	}

	return num_cnt;
}

void DataManager::CsvDataSave(const std::string& _FileName, int _num)
{
	std::ofstream ofs;

	// �ǂݍ���
	ofs.open(_FileName.c_str());

	//	�ǂݍ��ݎ��s
	if (!ofs)
	{
		//	���b�Z�[�W������
		MessageBox(NULL, "�e�L�X�g�t�@�C�����ǂݍ��߂Ă��܂���", "�x��", MB_OK);

		//	���������Ԃ�
		return;
	}

	// �e�L�X�g���̃f�[�^������
	ofs.trunc;

	//��Ɨp�ϐ�
	static int num_cnt;
	YsVec3 Pos = YsVec3(0.0f, 0.0f, 0.0f);
	float size = 1.0f;
	YsVec3 Angle = YsVec3(0.0f, 0.0f, 0.0f);
	std::string modelName;

	//��ޖ����ɕۑ�
	ofs << "���f����," << "X���W," << "Y���W," << "Z���W," << "�T�C�Y," << "�p�xX," << "�p�xY," << "�p�xZ," << "�N���X" << std::endl;

	//���X�g�������ׂĉ�
	for (num_cnt = 0; num_cnt < _num; num_cnt++) {

		//���f�[�^���i�[
		Pos = HELP.GetObject_All(num_cnt)->GetPos();
		size = HELP.GetObject_All(num_cnt)->GetScale().x;
		if (HELP.GetObject_All(num_cnt)->GetObjId() == OBJECT_LIST::ID::PLAYER) {
			Angle = HELP.GetObject_All(num_cnt)->GetAxis();
		}
		else {
			Angle = HELP.GetObject_All(num_cnt)->GetAngle();
		}


		//�N���X���ۑ�
		switch (HELP.GetObject_All(num_cnt)->GetObjId()) {
			//�v���C���[
		case OBJECT_LIST::ID::PLAYER:
			modelName = PLAYER_PATH;
			ofs << CSV_DATA_SAVE << "Player" << std::endl; break;
			//�G�l�~�[
		case OBJECT_LIST::ID::ENEMY:
			ofs << CSV_DATA_SAVE << "Enemy" << std::endl; break;
			//�X�e�[�W
		case OBJECT_LIST::ID::GROUND:
			modelName = GROUND_PATH;
			ofs << CSV_DATA_SAVE << "Ground" << std::endl; break;
			//���_
		case OBJECT_LIST::ID::STRONGHOLD:
			ofs << CSV_DATA_SAVE << "Stronghold" << std::endl; break;
			//��
		case OBJECT_LIST::ID::WALL:
			ofs << CSV_DATA_SAVE << "Wall" << std::endl; break;
			//���Ί�
		case OBJECT_LIST::ID::SLING:
			ofs << CSV_DATA_SAVE << "Sling" << std::endl; break;
			//��C
		case OBJECT_LIST::ID::CANNON:
			ofs << CSV_DATA_SAVE << "Cannon" << std::endl; break;
			//�Ή����ˊ�
		case OBJECT_LIST::ID::FLAMETHROWER:
			ofs << CSV_DATA_SAVE << "Flamethrower" << std::endl; break;
			//�v���X�@
		case OBJECT_LIST::ID::PRESS:
			ofs << CSV_DATA_SAVE << "Press" << std::endl; break;
			//�A�[��
		case OBJECT_LIST::ID::ARM:
			modelName = ARM_PATH;
			ofs << CSV_DATA_SAVE << "Arm" << std::endl; break;
			//�x���g�R���x�A
		case OBJECT_LIST::ID::BELTCONVEYOR:
			modelName = BELT_PATH;
			ofs << CSV_DATA_SAVE << "BeltConveyor" << std::endl; break;
			//�u���b�W
		case OBJECT_LIST::ID::BRIDGE:
			modelName = BRIDGE_PATH;
			ofs << CSV_DATA_SAVE << "Bridge" << std::endl; break;
		}
	}

	//�t�@�C���N���[�Y
	ofs.close();
}