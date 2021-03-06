#include "main.h"
#include "Data/DataManager.h"
#include "GameWorld.h"
#include "Game/Edit/EditWorld.h"

//staticメンバ変数の本体
GameWorld*	GameWorld::s_pInst = nullptr;

void GameWorld::Init()
{
	//カメラの初期化
	m_gwCam.Init(20, 180, 0, false, true);
	m_ewCam.Init(20, 180, 0);

	//エディットフラグ初期値
	m_EditFlg = FALSE;

	//外部からゲームオブジェクトを読み込み
	UPtr<DataManager> uDM(new DataManager);
	// カメラ視点キャラとして記憶
	m_wpCamera = uDM->CsvDataLoad("data/txt/Object.csv");
	// プレイヤーとして記憶
	m_wpPlayer = m_wpCamera;

	// エディットワールド作成・初期化
	EditWorld::CreateWorld();
	EW.Init();
}

void GameWorld::Release()
{

	//外部のテキストファイルへ保存
	UPtr<DataManager> uDM(new DataManager);
	uDM->CsvDataSave("data/txt/Object.csv");

	//エディットモード解放
	EW.Release();
	EditWorld::DeleteWorld();

	CharacterBase::FullClear();

	m_wpCamera.reset();
	m_wpPlayer.reset();
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
	//エディットモード
	//=======================================
	//エディットモード
	if (INPUT.KeyCheck_Enter('N') && !m_EditFlg) {
		//フラグON
		m_EditFlg = TRUE;
	}
	//ゲーム
	if (INPUT.KeyCheck_Enter('M') && m_EditFlg) {
		//フラグOFF
		m_EditFlg = FALSE;
	}
	if (m_EditFlg) {
		// カメラ操作
		m_ewCam.Update(m_wpCamera.lock().get()->GetPos());
		//エディットモード更新
		EW.SetCam(m_ewCam);
		EW.Update();
	}
	else {
		//全オブジェクト更新
		CharacterBase::AllUpdate();
		// カメラ操作
		m_gwCam.Update(m_wpCamera.lock().get()->GetPos());
	}

	// Player座標デバッグ表示
	auto player = m_wpPlayer.lock();
	if (player) {
		Dw_Static(10, "pos(%.2f, %.2f, %.2f)", player->GetPos().x, player->GetPos().y, player->GetPos().z);
	}
}

void GameWorld::Draw()
{
	//==========================================
	// カメラ設定
	//==========================================
	// ポーズ中でないなら、カメラ視点に設定しているキャラの、カメラ処理を実行
	/*if (m_PauseFlag == false) {
		if (m_wpCamera.expired() == false) {
			m_wpCamera.lock()->SetCamera();
		}
	}*/
	// ポーズ中なら、GameWorldのカメラを使用
	//else {
		if (m_EditFlg) {
			m_ewCam.SetCamera();
			//エディットモード描画
			EW.Draw();
		}
		else if (!m_EditFlg) {
			m_gwCam.SetCamera(m_wpCamera.lock().get()->GetPos());
		}
	//}

	//=======================================
	// 描画直前にシェーダのフレーム単位データを更新する
	//=======================================
	ShMgr.UpdateBeforeDraw();

	//全オブジェクト描画
	CharacterBase::AllDraw();
}