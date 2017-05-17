#pragma once

#include "Game/GameCamera.h"

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

//作成したインクルードヘッダー
#include "Base/ObjectBase.h"
#include "Character/Player.h"
#include "Object/Ground.h"
#include "Object/Stronghold.h"
#include "Object/Wall.h"
#include "Object/Sling.h"
#include "Object/Cannon.h"
#include "Object/Flamethrower.h"
#include "Object/Press.h"
#include "Object/BeltConveyor.h"
#include "Object/Arm.h"
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
	//　カメラ
	//=================
	GameCamera m_Cam;

	//=================
	//　タスクシステム
	//=================
	TaskManager	m_EffectTaskMgr;		//エフェクト用タスクマネージャー（キャラクターリスト）

	//=================
	// その他
	//=================
	bool	m_PauseFlag = false;	//ポーズON/OFF

	int	Obj_Num_Max = 0;	//オブジェクトの数格納用

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