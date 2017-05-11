#include "main.h"
#include "Data/DataManager.h"
#include "GameWorld.h"

//staticメンバ変数の本体
GameWorld*	GameWorld::s_pInst = nullptr;

void GameWorld::Init()
{
	//外部からゲームオブジェクトを読み込み
	UPtr<DataManager> uDM(new DataManager);
	uDM->DataLoad("data/txt/Object1.txt");

	//カメラの初期化
	m_Cam.Init(20, 180, 0, false, true);
}

void GameWorld::Release()
{
	//=======================================
	// タスク描画　全タスクのRelease実行
	//=======================================
	//m_EffectTaskMgr.Release();

	ObjectBase::FullClear();
}

void GameWorld::Update()
{
	//=======================================
	// ポーズON/OFF
	//=======================================
	if (INPUT.KeyCheck_Enter('P')){
		m_PauseFlag = !m_PauseFlag;
	}

	//=======================================
	// カメラ操作
	//=======================================
	m_Cam.Update();

	// 移動
	if (INPUT.KeyCheck('W')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetZAxis() * 0.03f);
	}
	if (INPUT.KeyCheck('S')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetZAxis() * -0.03f);
	}
	if (INPUT.KeyCheck('A')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetXAxis() * -0.03f);
	}
	if (INPUT.KeyCheck('D')) {
		m_Cam.m_BaseMat.Move(m_Cam.mCam.GetXAxis() * 0.03f);
	}

	//=======================================
	// タスク動作　全エフェクトのUpdate実行
	//=======================================
	//m_EffectTaskMgr.UpdateTask();

	ObjectBase::AllUpdate();
}

void GameWorld::Draw()
{
	//=======================================
	// カメラ設定
	//=======================================
	m_Cam.SetCamera();

	//=======================================
	// 描画直前にシェーダのフレーム単位データを更新する
	//=======================================
	ShMgr.UpdateBeforeDraw();

	//=======================================
	// タスク描画　全タスクのDraw実行
	//=======================================
	//YsDx.DS_ZSetting(true, false);	//Z書き込みはOFF
	//m_EffectTaskMgr.DrawTask();
	//YsDx.DS_ZSetting(true, true);	//Z書き込みをONに戻す

	ObjectBase::AllDraw();
}