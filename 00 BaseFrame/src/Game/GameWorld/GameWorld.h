#pragma once

//=====================================
//ゲームオブジェクト基本クラス
//　ゲーム中に登場する物体の基本となるクラス
//=====================================
class BaseGameObj :public BaseTask
{
public:
	//キャラの行列
	YsMatrix	m_Mat;
};

#include "Include.h"

//=====================================
//
//ゲームワールドクラス
//
//　ゲームの世界の基礎となるクラス
//
//=====================================
class GameWorld
{
public:
	//初期化
	void Init();

	//解放
	void Release();

	//更新
	void Update();

	//描画
	void Draw();


	//=================
	// その他
	//=================
	bool	m_PauseFlag = false;	//ポーズON/OFF

	int	Obj_Num_Max = 0;	//オブジェクトの数格納用

private:

	//=================
	//　カメラ
	//=================
	GameCamera		m_gwCam;
	GameCamera		m_ewCam;			//エディットカメラ
	WPtr<ObjectBase> m_wpCamera; // 現在カメラ視点になってるキャラへのアドレス
	WPtr<ObjectBase> m_wpPlayer; // プレイヤーキャラへのアドレス

	BOOL			m_EditFlg;			//エディット用フラグ

	//================================
	//　シングルトンパターン
	//================================
private:
	//インスタンス用
	static GameWorld*	s_pInst;

	//外部からインスタンス化させないためprivateコンストラクタ
	GameWorld(){
	}

public:
	//ゲームワールド削除
	static void DeleteWorld(){
		YsSafe_Delete(s_pInst);
	}

	//ゲームワールド作成
	static void CreateWorld(){
		DeleteWorld();
		s_pInst = new GameWorld();
	}

	//ゲームワールド取得
	static GameWorld& GetWorld(){
		return *s_pInst;
	}

};

#define GW GameWorld::GetWorld()