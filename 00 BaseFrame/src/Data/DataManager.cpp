#include "main.h"
#include "Game/GameWorld/GameWorld.h"
#include "DataManager.h"
#include "FilePath.h"


int DataManager::TxtDataLoad(const std::string& _FileName)
{
	std::ifstream ifs;

	//	読み込み
	ifs.open(_FileName.c_str());

	//	読み込み失敗
	if (!ifs)
	{
		//	メッセージをだす
		MessageBox(NULL, "テキストファイルが読み込めていません", "警告", MB_OK);

		//	何もせず返す
		return 0;
	}

	int num_cnt = 0;

	for (;;)
	{
		std::string line;

		//	一行読み込む
		getline(ifs, line);

		//	読み込み終了
		if (ifs.fail())
		{
			break;
		}


		/*---------------------------------------------------------------------

		区切りたい文字を設定、vector配列に格納(切り取りたい文字は複数指定可)

		例
		string sp = "abc";

		sp = GetSplit(line, "ac");

		spには"abc"のうちaとcが切り取られたbのみが帰ってくる

		---------------------------------------------------------------------*/
		std::vector<std::string> sp = GetSplit(line, "(),");


		//	デフォルトステータス
		YsVec3 vPos = YsVec3(0.0f, 0.0f, 0.0f);
		YsVec3 vScale = YsVec3(1.0f, 1.0f, 1.0f);
		YsVec3 vAngle = YsVec3(0.0f, 0.0f, 0.0f);
		INT		 Id = -1;


		//	最初のアドレスをイテレータに格納
		auto FileIt = sp.begin();


		/*-----------------------------------------------------

		指定されたタグが見つかった場合、そのタグ内の数値を
		用意されたステータス用の変数に代入
		数値は+2の位置に指定


		タグ
		{
		Pos				:	座標ベクトル
		Scale			:	拡大ベクトル
		Angle			:	角度ベクトル
		Id			:	識別番号
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
		//	Classタグの中を確認して、指定したClass名があれば
		//	インスタンス化してObjectManagerにプッシュする
		//	ステータスは先に設定値を代入する
		//
		//-----------------------------------------------------
		FileIt = sp.begin();

		while (FileIt != sp.end())
		{
			//====================
			// キャラクタ
			//====================
			//プレイヤー
			{
				if ((*FileIt) == "Player")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(PLAYER_PATH);

					CreateGameObject<Player>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::PLAYER);
					num_cnt++;
				}
			}

			//====================
			//オブジェクト
			//====================
			//ステージ
			{
				if ((*FileIt) == "Ground")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(GROUND_PATH);

					CreateGameObject<Ground>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::GROUND);
					num_cnt++;
				}
			}

			//拠点
			{
				if ((*FileIt) == "Stronghold")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Stronghold>(num_cnt, vPos, vScale, vAngle, drawModel,OBJECT_LIST::ID::STRONGHOLD);
					num_cnt++;
				}
			}

			//壁
			{
				if ((*FileIt) == "Wall")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Wall>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::WALL);
					num_cnt++;
				}
			}

			//投石器
			{
				if ((*FileIt) == "Sling")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Sling>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::SLING);
					num_cnt++;
				}
			}

			//大砲
			{
				if ((*FileIt) == "Cannon")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Cannon>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::CANNON);
					num_cnt++;
				}
			}

			//火炎放射器
			{
				if ((*FileIt) == "Flamethrower")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Flamethrower>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::FLAMETHROWER);
					num_cnt++;
				}
			}

			//プレス機
			{
				if ((*FileIt) == "Press")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh("");

					CreateGameObject<Press>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::PRESS);
					num_cnt++;
				}
			}

			//アーム
			{
				if ((*FileIt) == "Arm")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(ARM_PATH);

					CreateGameObject<Arm>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::ARM);
					num_cnt++;
				}
			}

			//ベルトコンベア
			{
				if ((*FileIt) == "Belt")
				{
					// 描画用メッシュ読み込み
					SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(BELT_PATH);

					CreateGameObject<BeltConveyor>(num_cnt, vPos, vScale, vAngle, drawModel, OBJECT_LIST::ID::BELTCONVEYOR);
					num_cnt++;
				}
			}

			//ブリッジ
			{
				if ((*FileIt) == "Bridge")
				{
					// 描画用メッシュ読み込み
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

	// 読み込み
	ofs.open(_FileName.c_str());

	//	読み込み失敗
	if (!ofs)
	{
		//	メッセージをだす
		MessageBox(NULL, "テキストファイルが読み込めていません", "警告", MB_OK);

		//	何もせず返す
		return;
	}

	// テキスト内のデータを消去
	ofs.trunc;

	//作業用変数
	static int num_cnt;
	YsVec3 Pos = YsVec3(0.0f, 0.0f, 0.0f);
	YsVec3 Scale = YsVec3(1.0f, 1.0f, 1.0f);
	YsVec3 Angle = YsVec3(0.0f, 0.0f, 0.0f);

	//リスト内をすべて回す
	for (num_cnt = 0; num_cnt < _num; num_cnt++) {

		//仮データを格納
		Pos = HELP.GetObject_All(num_cnt)->GetPos();
		Scale = HELP.GetObject_All(num_cnt)->GetScale();
		if (HELP.GetObject_All(num_cnt)->GetObjId() == OBJECT_LIST::ID::PLAYER) {
			Angle = HELP.GetObject_All(num_cnt)->GetAxis();
		}
		else {
			Angle = HELP.GetObject_All(num_cnt)->GetAngle();
		}


		//クラス情報保存
		switch (HELP.GetObject_All(num_cnt)->GetObjId()) {
			//プレイヤー
		case OBJECT_LIST::ID::PLAYER:
			ofs << "ClassName(Player)" << TXT_DATA_SAVE << std::endl; break;
			//エネミー
		case OBJECT_LIST::ID::ENEMY:
			ofs << "ClassName(Enemy)" << TXT_DATA_SAVE << std::endl; break;
			//ステージ
		case OBJECT_LIST::ID::GROUND:
			ofs << "ClassName(Ground)" << TXT_DATA_SAVE << std::endl; break;
			//拠点
		case OBJECT_LIST::ID::STRONGHOLD:
			ofs << "ClassName(Stronghold)" << TXT_DATA_SAVE << std::endl; break;
			//壁
		case OBJECT_LIST::ID::WALL:
			ofs << "ClassName(Wall)" << TXT_DATA_SAVE << std::endl; break;
			//投石器
		case OBJECT_LIST::ID::SLING:
			ofs << "ClassName(Sling)" << TXT_DATA_SAVE << std::endl; break;
			//大砲
		case OBJECT_LIST::ID::CANNON:
			ofs << "ClassName(Cannon)" << TXT_DATA_SAVE << std::endl; break;
			//火炎放射器
		case OBJECT_LIST::ID::FLAMETHROWER:
			ofs << "ClassName(Flamethrower)" << TXT_DATA_SAVE << std::endl; break;
			//プレス機
		case OBJECT_LIST::ID::PRESS:
			ofs << "ClassName(Press)" << TXT_DATA_SAVE << std::endl; break;
			//アーム
		case OBJECT_LIST::ID::ARM:
			ofs << "ClassName(Arm)" << TXT_DATA_SAVE << std::endl; break;
			//ベルトコンベア
		case OBJECT_LIST::ID::BELTCONVEYOR:
			ofs << "ClassName(Belt)" << TXT_DATA_SAVE << std::endl; break;
			//ブリッジ
		case OBJECT_LIST::ID::BRIDGE:
			ofs << "ClassName(Bridge)" << TXT_DATA_SAVE << std::endl; break;
		}
	}

	//ファイルクローズ
	ofs.close();
}

/*trim------------------------------------------->

指定された文字列を切り取り
切り取った文字列の前後のいらない部分を削り取る

_Str				: 切り取りたい文字列の元
_TrimCharacterList	: いらない文字列

return : string型

<-----------------------------------------------*/
static std::string trim(const std::string& _Str, const char* _TrimCharacterList = " \t\v\r\n")
{
	std::string result;

	// 左側からトリムする文字以外が見つかる位置を検索します。
	std::string::size_type left = _Str.find_first_not_of(_TrimCharacterList);

	if (left != std::string::npos)
	{
		// 左側からトリムする文字以外が見つかった場合は、同じように右側からも検索します。
		std::string::size_type right = _Str.find_last_not_of(_TrimCharacterList);

		// 戻り値を決定します。ここでは右側から検索しても、トリムする文字以外が必ず存在するので判定不要です。
		result = _Str.substr(left, right - left + 1);
	}

	return result;
}


std::vector<std::string> DataManager::GetSplit(
	std::string _Str,
	std::string _Split)
{
	//	文字を格納するための変数
	std::vector<std::string> vecRet;


	//	検索したい候補のうちのいずれかがヒットすれば
	while (_Str.find_first_of(_Split) != std::string::npos)
	{

		//	切り取りたい文字列を設定
		_Str = trim(_Str, " ");
		_Str = trim(_Str, "\t\v\r\n");

		//	切り取りたい文字数を取得
		int Cp = _Str.find_first_of(_Split);

		//	文字数が一つのみだった場合
		if (Cp <= 0)
		{
			Cp += 1;
		}

		//	先頭空文字が格納されないように
		if (Cp > 0)
		{

			//	格納
			vecRet.push_back(_Str.substr(0, Cp));

		}

		//	区切り文字が二文字以上に対応
		_Str = _Str.substr(Cp);
	}

	//	リストを返す
	return vecRet;
}







int DataManager::CsvDataLoad(const std::string& _FileName)
{
	//オブジェクト個数初期化
	int num_cnt = 0;

	//===========================
	// CSVデータ読み込み
	//===========================
	csv.Load(_FileName);

	//読み込み・配置(０行目はタイトル行なので、１行目から)
	for (UINT i = 1; i < csv.m_Tbl.size(); i++) {
		// データ取得
		std::string modelName = csv.GetCol(i, "モデル名");
		YsVec3 pos;
		pos.x = std::stof(csv.GetCol(i, "X座標"));
		pos.y = std::stof(csv.GetCol(i, "Y座標"));
		pos.z = std::stof(csv.GetCol(i, "Z座標"));
		float size = std::stof(csv.GetCol(i, "サイズ"));
		YsVec3 rotate;
		rotate.x = std::stof(csv.GetCol(i, "角度X"));
		rotate.y = std::stof(csv.GetCol(i, "角度Y"));
		rotate.z = std::stof(csv.GetCol(i, "角度Z"));
		std::string className = csv.GetCol(i, "クラス");

		// 描画用メッシュ読み込み
		SPtr<YsGameModel> drawModel = YsDx.GetResStg()->LoadMesh(modelName);

		YsVec3 scale = YsVec3(size, size, size);

		//====================
		// キャラクタ
		//====================
		//プレイヤー
		{
			if (className == "Player")
			{
				CreateGameObject<Player>(num_cnt, pos, scale, rotate, drawModel,OBJECT_LIST::ID::PLAYER);
				num_cnt++;
			}
		}

		//====================
		//オブジェクト
		//====================
		//ステージ
		{
			if (className == "Ground")
			{
				CreateGameObject<Ground>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::GROUND);
				num_cnt++;
			}
		}

		//拠点
		{
			if (className == "Stronghold")
			{
				CreateGameObject<Stronghold>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::STRONGHOLD);
				num_cnt++;
			}
		}

		//壁
		{
			if (className == "Wall")
			{
				CreateGameObject<Wall>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::WALL);
				num_cnt++;
			}
		}

		//投石器
		{
			if (className == "Sling")
			{
				CreateGameObject<Sling>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::SLING);
				num_cnt++;
			}
		}

		//大砲
		{
			if (className == "Cannon")
			{
				CreateGameObject<Cannon>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::CANNON);
				num_cnt++;
			}
		}

		//火炎放射器
		{
			if (className == "Flamethrower")
			{
				CreateGameObject<Flamethrower>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::FLAMETHROWER);
				num_cnt++;
			}
		}

		//プレス機
		{
			if (className == "Press")
			{
				CreateGameObject<Press>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::PRESS);
				num_cnt++;
			}
		}

		//アーム
		{
			if (className == "Arm")
			{
				CreateGameObject<Arm>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::ARM);
				num_cnt++;
			}
		}

		//ベルトコンベア
		{
			if (className == "BeltConveyor")
			{
				CreateGameObject<BeltConveyor>(num_cnt, pos, scale, rotate, drawModel, OBJECT_LIST::ID::BELTCONVEYOR);
				num_cnt++;
			}
		}

		//ブリッジ
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

	// 読み込み
	ofs.open(_FileName.c_str());

	//	読み込み失敗
	if (!ofs)
	{
		//	メッセージをだす
		MessageBox(NULL, "テキストファイルが読み込めていません", "警告", MB_OK);

		//	何もせず返す
		return;
	}

	// テキスト内のデータを消去
	ofs.trunc;

	//作業用変数
	static int num_cnt;
	YsVec3 Pos = YsVec3(0.0f, 0.0f, 0.0f);
	float size = 1.0f;
	YsVec3 Angle = YsVec3(0.0f, 0.0f, 0.0f);
	std::string modelName;

	//種類名を先に保存
	ofs << "モデル名," << "X座標," << "Y座標," << "Z座標," << "サイズ," << "角度X," << "角度Y," << "角度Z," << "クラス" << std::endl;

	//リスト内をすべて回す
	for (num_cnt = 0; num_cnt < _num; num_cnt++) {

		//仮データを格納
		Pos = HELP.GetObject_All(num_cnt)->GetPos();
		size = HELP.GetObject_All(num_cnt)->GetScale().x;
		if (HELP.GetObject_All(num_cnt)->GetObjId() == OBJECT_LIST::ID::PLAYER) {
			Angle = HELP.GetObject_All(num_cnt)->GetAxis();
		}
		else {
			Angle = HELP.GetObject_All(num_cnt)->GetAngle();
		}


		//クラス情報保存
		switch (HELP.GetObject_All(num_cnt)->GetObjId()) {
			//プレイヤー
		case OBJECT_LIST::ID::PLAYER:
			modelName = PLAYER_PATH;
			ofs << CSV_DATA_SAVE << "Player" << std::endl; break;
			//エネミー
		case OBJECT_LIST::ID::ENEMY:
			ofs << CSV_DATA_SAVE << "Enemy" << std::endl; break;
			//ステージ
		case OBJECT_LIST::ID::GROUND:
			modelName = GROUND_PATH;
			ofs << CSV_DATA_SAVE << "Ground" << std::endl; break;
			//拠点
		case OBJECT_LIST::ID::STRONGHOLD:
			ofs << CSV_DATA_SAVE << "Stronghold" << std::endl; break;
			//壁
		case OBJECT_LIST::ID::WALL:
			ofs << CSV_DATA_SAVE << "Wall" << std::endl; break;
			//投石器
		case OBJECT_LIST::ID::SLING:
			ofs << CSV_DATA_SAVE << "Sling" << std::endl; break;
			//大砲
		case OBJECT_LIST::ID::CANNON:
			ofs << CSV_DATA_SAVE << "Cannon" << std::endl; break;
			//火炎放射器
		case OBJECT_LIST::ID::FLAMETHROWER:
			ofs << CSV_DATA_SAVE << "Flamethrower" << std::endl; break;
			//プレス機
		case OBJECT_LIST::ID::PRESS:
			ofs << CSV_DATA_SAVE << "Press" << std::endl; break;
			//アーム
		case OBJECT_LIST::ID::ARM:
			modelName = ARM_PATH;
			ofs << CSV_DATA_SAVE << "Arm" << std::endl; break;
			//ベルトコンベア
		case OBJECT_LIST::ID::BELTCONVEYOR:
			modelName = BELT_PATH;
			ofs << CSV_DATA_SAVE << "BeltConveyor" << std::endl; break;
			//ブリッジ
		case OBJECT_LIST::ID::BRIDGE:
			modelName = BRIDGE_PATH;
			ofs << CSV_DATA_SAVE << "Bridge" << std::endl; break;
		}
	}

	//ファイルクローズ
	ofs.close();
}