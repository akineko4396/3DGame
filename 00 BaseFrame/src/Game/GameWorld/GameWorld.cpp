#include "main.h"
#include "Data/DataManager.h"
#include "GameWorld.h"
#include "Game/Edit/EditWorld.h"

//staticメンバ変数の本体
GameWorld*	GameWorld::s_pInst = nullptr;

void GameWorld::Init()
{
	//外部からゲームオブジェクトを読み込み
	UPtr<DataManager> uDM(new DataManager);
	Obj_Num_Max = uDM->DataLoad("data/txt/Object1.txt");

	// エディットワールド作成・初期化
	EditWorld::CreateWorld();
	EW.Init(Obj_Num_Max);
}

void GameWorld::Release()
{

	//外部のテキストファイルへ保存
	UPtr<DataManager> uDM(new DataManager);
	uDM->DataSave("data/txt/Object1.txt", Obj_Num_Max);

	//全オブジェクト解放
	ObjectBase::FullClear();

	//エディットモード解放
	EW.Release();
	EditWorld::DeleteWorld();
}

void GameWorld::Update()
{
	//=======================================
	// ポーズON/OFF
	//=======================================
	if (INPUT.KeyCheck_Enter('P')){
		m_PauseFlag = !m_PauseFlag;
	}

	//全オブジェクト更新
	ObjectBase::AllUpdate();

	//エディットモード更新
	EW.Update();
}

void GameWorld::Draw()
{

	//=======================================
	// 描画直前にシェーダのフレーム単位データを更新する
	//=======================================
	ShMgr.UpdateBeforeDraw();

	//全オブジェクト描画
	ObjectBase::AllDraw();

	//エディットモード描画
	EW.Draw();
}