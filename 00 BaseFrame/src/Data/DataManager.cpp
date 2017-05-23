#include "main.h"
#include "Game/GameWorld/GameWorld.h"
#include "Game/Edit/EditWorld.h"
#include "DataManager.h"


int DataManager::DataLoad(const std::string& _FileName)
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
					CreateGameObject<Player>(num_cnt, vPos, vScale, vAngle);
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
					CreateGameObject<Ground>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//拠点
			{
				if ((*FileIt) == "Stronghold")
				{
					CreateGameObject<Stronghold>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//壁
			{
				if ((*FileIt) == "Wall")
				{
					CreateGameObject<Wall>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//投石器
			{
				if ((*FileIt) == "Sling")
				{
					CreateGameObject<Sling>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//大砲
			{
				if ((*FileIt) == "Cannon")
				{
					CreateGameObject<Cannon>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//火炎放射器
			{
				if ((*FileIt) == "Flamethrower")
				{
					CreateGameObject<Flamethrower>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//プレス機
			{
				if ((*FileIt) == "Press")
				{
					CreateGameObject<Press>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//アーム
			{
				if ((*FileIt) == "Arm")
				{
					CreateGameObject<Arm>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//ベルトコンベア
			{
				if ((*FileIt) == "Belt")
				{
					CreateGameObject<BeltConveyor>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			//ブリッジ
			{
				if ((*FileIt) == "Bridge")
				{
					CreateGameObject<Bridge>(num_cnt, vPos, vScale, vAngle);
					num_cnt++;
				}
			}

			++FileIt;

		}
	}

	return num_cnt;
}

//コードが長いため簡略化
#define DATA_SAVE_NORMAL "\t" << "Pos(" << Pos.x << "," << Pos.y << "," << Pos.z << ")" << "\t" << "Scale(" << Scale.x << "," << Scale.y << "," << Scale.z << ")" << "\t" << "Angle(" << Angle.x << "," << Angle.y << "," << Angle.z << ")" 

void DataManager::DataSave(const std::string _FileName, int _num)
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
	static YsVec3 Pos;
	static YsVec3 Scale;
	static YsVec3 Angle;

	//リスト内をすべて回す
	for (num_cnt = 0; num_cnt < _num; num_cnt++) {

		//仮データを格納
		Pos = ObjectBase::GetThisObject(num_cnt)->GetPos();
		Scale = ObjectBase::GetThisObject(num_cnt)->GetScale();
		Angle = ObjectBase::GetThisObject(num_cnt)->GetAngle();


		//クラス情報保存
		switch (ObjectBase::GetThisObject(num_cnt)->GetObjId()) {
			//プレイヤー
		case OBJECT_LIST::ID::PLAYER:
			ofs << "ClassName(Player)" << DATA_SAVE_NORMAL << std::endl; break;
			//エネミー
		case OBJECT_LIST::ID::ENEMY:
			ofs << "ClassName(Enemy)" << DATA_SAVE_NORMAL << std::endl; break;
			//ステージ
		case OBJECT_LIST::ID::GROUND:
			ofs << "ClassName(Ground)" << DATA_SAVE_NORMAL << std::endl; break;
			//拠点
		case OBJECT_LIST::ID::STRONGHOLD:
			ofs << "ClassName(Stronghold)" << DATA_SAVE_NORMAL << std::endl; break;
			//壁
		case OBJECT_LIST::ID::WALL:
			ofs << "ClassName(Wall)" << DATA_SAVE_NORMAL << std::endl; break;
			//投石器
		case OBJECT_LIST::ID::SLING:
			ofs << "ClassName(Sling)" << DATA_SAVE_NORMAL << std::endl; break;
			//大砲
		case OBJECT_LIST::ID::CANNON:
			ofs << "ClassName(Cannon)" << DATA_SAVE_NORMAL << std::endl; break;
			//火炎放射器
		case OBJECT_LIST::ID::FLAMETHROWER:
			ofs << "ClassName(Flamethrower)" << DATA_SAVE_NORMAL << std::endl; break;
			//プレス機
		case OBJECT_LIST::ID::PRESS:
			ofs << "ClassName(Press)" << DATA_SAVE_NORMAL << std::endl; break;
			//アーム
		case OBJECT_LIST::ID::ARM:
			ofs << "ClassName(Arm)" << DATA_SAVE_NORMAL << std::endl; break;
			//ベルトコンベア
		case OBJECT_LIST::ID::BELTCONVEYOR:
			ofs << "ClassName(Belt)" << DATA_SAVE_NORMAL << std::endl; break;
			//ブリッジ
		case OBJECT_LIST::ID::BRIDGE:
			ofs << "ClassName(Bridge)" << DATA_SAVE_NORMAL << std::endl; break;
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