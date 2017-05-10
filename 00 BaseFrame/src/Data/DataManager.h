#pragma once

//======================
// 前方宣言
//======================

//キャラクターベースクラス
class CharacterBase;

//オブジェクトベースクラス
class ObjectBase;

//=================================================
// データを読み書きするクラス
//=================================================

class DataManager
{
public:

	/*DataLoad------------------------------------

	外部ファイルを読み込む
	ゲームに使用するキャラクタやオブジェクトを
	インスタンス化してリストに格納する

	_FileName		:	ファイルパス

	return			:	戻り値なし

	--------------------------------------------*/
	void DataLoad(const std::string _FileName);

	/*DataLoad------------------------------------

	外部ファイルに書きこむ
	ゲームに使用したキャラクタやオブジェクトを
	テキストファイルに書き出す

	_FileName		:	ファイルパス

	return			:	戻り値なし

	--------------------------------------------*/
	void DataSave(const std::string _FileName);

	/*GetSplit--------------------------------->

	指定した文字を切り取って
	データとなる文字列を返す
	戻り値として切り取った文字列を返す

	_Str	:	元となる文字列
	_Split	:	切り取りたい文字列(複数化)

	return	:	vector型

	<----------------------------------------*/
	std::vector<std::string> GetSplit(
		std::string _Str,
		std::string _Split
		);

	/*(template)CreateGameCharacter---------------

	CharacterBaseにプッシュして初期化を行う

	template		:	プッシュするクラス
	_SetId			:	識別番号
	_SetPosition	:	座標
	_SetScale		:	拡大サイズ
	_SetAngle		:	角度

	return			:	戻り値なし

	-----------------------------------------*/
	template <class T>
	inline void CreateGameCharacter(
		INT						_SetId,
		YsVec3					_SetPosition,
		YsVec3					_SetScale,
		YsVec3					_SetAngle
		)
	{
		//　リストにインスタンス化したオブジェクトをプッシュする
		SPtr<T> add = CharacterBase::CreateCharacterTask<T>();

		//　識別番号をセットする
		add->SetId(_SetId);

		//　座標をセットする
		add->SetPos(_SetPosition);

		//　拡大サイズをセットする
		add->SetScale(_SetScale);

		//　回転量をセットする
		add->SetAngle(_SetAngle);

		//　キャラクタの初期化をする
		add->Init();
	}

	/*(template)CreateGameObject---------------

	ObjectBaseにプッシュして初期化を行う

	template		:	プッシュするクラス
	_SetId			:	識別番号
	_SetPosition	:	座標
	_SetScale		:	拡大サイズ
	_SetAngle		:	角度

	return			:	戻り値なし

	-----------------------------------------*/
	template <class T>
	inline void CreateGameObject(
		INT						_SetId,
		YsVec3					_SetPosition,
		YsVec3					_SetScale,
		YsVec3					_SetAngle
		)
	{
		//　リストにインスタンス化したオブジェクトをプッシュする
		SPtr<T> add = ObjectBase::CreateCharacterTask<T>();

		//　識別番号をセットする
		add->SetId(_SetId);

		//　座標をセットする
		add->SetPos(_SetPosition);

		//　拡大サイズをセットする
		add->SetScale(_SetScale);

		//　回転量をセットする
		add->SetAngle(_SetAngle);

		//　オブジェクトの初期化をする
		add->Init();
	}

	//================================
	//　シングルトンパターン
	//================================
private:
	//インスタンス用
	static DataManager*	s_pdmInst;

	//外部からインスタンス化させないためprivateコンストラクタ
	DataManager(){
	}

public:

	//データマネージャー削除
	static void DeleteDataManager(){
		YsSafe_Delete(s_pdmInst);
	}

	//データマネージャー作成
	static void CreateDataManager(){
		DeleteDataManager();
		s_pdmInst = new DataManager();
	}

	//データマネージャー取得
	static DataManager& GetDataManager(){
		return *s_pdmInst;
	}
};

#define DM DataManager::GetDataManager()