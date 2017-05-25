#pragma once

//==========================
// namespace
//==========================
namespace OPTION {

	enum ID {

		//オブジェクト
		OBJ = 0,

		//座標
		POS = 1,

		//拡大サイズ
		SCALE = 2,

		//回転量
		ANGLE = 3,

		//最大数
		MAX_NUM = 4,

	};

}


#include "Game/GameCamera.h"

//======================================================
//
//エディットワールドクラス
//
//　ゲームの世界を作成する基礎となるクラス
//　現在はゲームシーン中のカメラの管理もこちらでやっている
//
//======================================================
class EditWorld {
public:
	//初期化
	void Init(int _ObjNum);

	//解放
	void Release();

	//更新
	void Update();

	//描画
	void Draw();

	//プレイヤーの座標セット
	inline void SetPPos(YsVec3 _pos) { pPos = _pos; }

	//=================
	// その他
	//=================
	bool	m_PauseFlag = false;	//ポーズON/OFF

	int	Obj_Num_Max = 0;	//オブジェクトの数格納用

	//=================
	//　カメラ
	//=================
	GameCamera m_Cam;


	//================================
	//　シングルトンパターン
	//================================
private:
	//インスタンス用
	static EditWorld*	s_pInst;

	//外部からインスタンス化させないためprivateコンストラクタ
	EditWorld() {
	}

public:
	//ゲームワールド削除
	static void DeleteWorld() {
		YsSafe_Delete(s_pInst);
	}

	//ゲームワールド作成
	static void CreateWorld() {
		DeleteWorld();
		s_pInst = new EditWorld();
	}

	//ゲームワールド取得
	static EditWorld& GetWorld() {
		return *s_pInst;
	}

private:

	//=======================
	// エディットに必要な変数
	//=======================
	int				m_OptionId;		//オプションID
	int				m_ObjId;			//オブジェクトID
	YsVec3			m_Pos;				//座標
	YsVec3			m_Scale;			//拡大サイズ
	YsVec3			m_Angle;			//回転量

	BOOL			m_EditFlg;			//エディット用フラグ

	RECT			m_EditButton;	//エディット用のボタン座標

	YsModelObject	m_moEdit;		//升目状のメッシュ
	YsMatrix			m_mEdit;			//升目状のメッシュの行列

	YsVec3			pPos;						//プレイヤーの座標格納用
};

#define EW EditWorld::GetWorld()