#include "main.h"
#include "../TitleScene/TitleScene.h"
#include "EditScene.h"


//============================================================
// 更新処理
//============================================================
int EditScene::Update()
{

	// Escapeキー
	if (INPUT.KeyCheck_Enter(VK_ESCAPE)) {
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

	//=======================================
	// カメラ操作
	//=======================================
	m_Cam.Update();



	return 0;
}

//============================================================
// 描画処理
//============================================================
void EditScene::Draw()
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

	//=======================================
	// カメラ設定
	//=======================================
	m_Cam.SetCamera();

	// 升目のように線を引いて区切る
	static int cnt;
	for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(-50 + cnt * 1, 0, 50), YsVec3(-50 + cnt * 1, 0, -50), &YsVec4(1, 1, 1, 1));
	for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(50, 0, -50 + cnt * 1), YsVec3(-50, 0, -50 + cnt * 1), &YsVec4(1, 1, 1, 1));

	// とりあえずXYZ線だけ描画しとく
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(1, 0, 0), &YsVec4(1, 0, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 1, 0), &YsVec4(0, 1, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 0, 1), &YsVec4(0, 0, 1, 1));


	// 描画などを書く




}

//============================================================
// データ解放
//============================================================
void EditScene::Release()
{
	Dw_Scroll(0, "エディットシーン解放処理");

}

//============================================================
// 初期設定
//============================================================
void EditScene::Init()
{
	Dw_Scroll(0, "エディットシーン初期化");

	// 平行ライト作成
	m_DirLight = ShMgr.m_LightMgr.AddDirLight();

	//カメラの初期化
	m_Cam.Init(20, 130, -3);
	m_Cam.m_BaseMat.SetPos(0, 1.2f, 0);

	//============================================================
	// データ読み込みなど
	//============================================================


}


