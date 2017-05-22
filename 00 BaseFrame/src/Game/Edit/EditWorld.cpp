#include "main.h"
#include "Data/DataManager.h"
#include "EditWorld.h"

//staticメンバ変数の本体
EditWorld* EditWorld::s_pInst = nullptr;

void EditWorld::Init(int _ObjNum)
{
	//カメラの初期化
	m_Cam.Init(20, 180, 0, false, true);

	//現在のオブジェクト数を代入
	Obj_Num_Max = _ObjNum;

	//エディットフラグ初期値
	m_EditFlg = FALSE;

}

void EditWorld::Release()
{

}

void EditWorld::Update()
{

	//=======================================
	// カメラ操作
	//=======================================
	m_Cam.Update();

	//エディットモードの時
	if (m_EditFlg) {

		if (INPUT.KeyCheck_Enter('S')) {
			//外部のテキストファイルへ保存
			UPtr<DataManager> uDM(new DataManager);
			uDM->DataSave("data/txt/Object1.txt", Obj_Num_Max);
		}

	}
	//ゲームの時
	else if (!m_EditFlg) {
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
	}

	//エディットモードへ
	if (INPUT.KeyCheck_Enter('N') && !m_EditFlg) {
		//カメラの初期化
		m_Cam.Init(20, 180, 0);

		//フラグON
		m_EditFlg = TRUE;
	}
	//ゲームへ
	if (INPUT.KeyCheck_Enter('M') && m_EditFlg) {
		//カメラの初期化
		m_Cam.Init(20, 180, 0, false, true);

		//フラグOFF
		m_EditFlg = FALSE;
	}

}

void EditWorld::Draw()
{
	//=======================================
	// カメラ設定
	//=======================================
	m_Cam.SetCamera();

	//エディットモードの時
	if (m_EditFlg) {

		// 升目のように線を引いて区切る
		static int cnt;
		for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(-50 + cnt * 1, 0, 50), YsVec3(-50 + cnt * 1, 0, -50), &YsVec4(1, 1, 1, 1));
		for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(50, 0, -50 + cnt * 1), YsVec3(-50, 0, -50 + cnt * 1), &YsVec4(1, 1, 1, 1));

		// とりあえずXYZ線だけ描画しとく
		ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(1, 0, 0), &YsVec4(1, 0, 0, 1));
		ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 1, 0), &YsVec4(0, 1, 0, 1));
		ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 0, 1), &YsVec4(0, 0, 1, 1));

		// 説明文字
		std::string text;
		text = "[エディットモード]\n";
		text += "M:ゲームシーンへ\n";
		text += "S:セーブ\n";

		// 2D描画(文字)
		YsDx.GetSprite().Begin(true);
		{
			YsDx.GetSprite().DrawFont(text, 1, 1, &YsVec4(0, 0, 0, 1));
			YsDx.GetSprite().DrawFont(text, 0, 0, &YsVec4(1, 1, 1, 1));
		}
		YsDx.GetSprite().End();
		
	}
	//ゲームの時
	else if(!m_EditFlg){

	}
}