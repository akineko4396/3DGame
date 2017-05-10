#include "main.h"
#include "../TitleScene/TitleScene.h"
#include "GameScene.h"
#include "Game/GameWorld/GameWorld.h"


//============================================================
// 更新処理
//============================================================
int GameScene::Update()
{

	// Escapeキー
	if(INPUT.KeyCheck_Enter(VK_ESCAPE)){
		// シーン切り替え
		SPtr<TitleScene> ts(new TitleScene());
		ts->Init();
		APP.m_NowScene = ts;

		return 1;
	}

	//==========================================
	// ライト情報更新
	//	※この情報を各シェーダ内で使用します
	//==========================================
	// 平行光源
	m_DirLight->SetData(
		YsVec3(0.5f, -1, -0.2f),		// ライト方向
		YsVec4(0.8f, 0.8f, 0.8f, 1)		// 基本色(Diffuse)
		);

	// 環境色(Ambient)
	ShMgr.m_LightMgr.m_AmbientLight.Set(0.2f, 0.2f, 0.2f);

	// ゲームワールド更新
	GW.Update();





	return 0;
}

//============================================================
// 描画処理
//============================================================
void GameScene::Draw()
{
	//==========================================
	// クリア
	//==========================================
	// バックバッファをクリアする。
	YsDx.GetBackBuffer()->ClearRT(YsVec4(0.3f, 0.3f, 0.3f, 1));
	// Zバッファのクリア
	YsDx.GetDepthStencil()->ClearDepth(true, true);

	// 半透明モードに
	ShMgr.m_bsAlpha.SetState();


	// とりあえずXYZ線だけ描画しとく
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(1, 0, 0), &YsVec4(1, 0, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 1, 0), &YsVec4(0, 1, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 0, 1), &YsVec4(0, 0, 1, 1));


	// 描画などを書く

	// ゲームワールド描画
	GW.Draw();







}

//============================================================
// データ解放
//============================================================
void GameScene::Release()
{
	Dw_Scroll(0,"ゲームシーン解放処理");

	// ゲームワールド解放
	GW.Release();
	GameWorld::DeleteWorld();
}

//============================================================
// 初期設定
//============================================================
void GameScene::Init()
{
	Dw_Scroll(0,"ゲームシーン初期化");

	// 平行ライト作成
	m_DirLight = ShMgr.m_LightMgr.AddDirLight();

	//============================================================
	// データ読み込みなど
	//============================================================

	// ゲームワールド作成・初期化
	GameWorld::CreateWorld();
	GW.Init();
}


