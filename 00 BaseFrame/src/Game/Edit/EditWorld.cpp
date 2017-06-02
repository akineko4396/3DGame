#include "main.h"
#include "Data/DataManager.h"
#include "EditWorld.h"

//staticメンバ変数の本体
EditWorld* EditWorld::s_pInst = nullptr;

void EditWorld::Init(int _ObjNum)
{
	//現在のオブジェクト数を代入
	Obj_Num_Max = _ObjNum;

	//升目状のメッシュ読み込み
	SPtr<YsGameModel> m_gmEdit = YsDx.GetResStg()->LoadMesh("data/model/StageForEdit/stage.x");
	m_moEdit.SetModel(m_gmEdit);
	m_mEdit.CreateMove(YsVec3(0, 0, 0));
	m_mEdit.Scale_Local(YsVec3(0.01f, 0.01f, 0.01f));
}

void EditWorld::Release()
{

}

void EditWorld::Update()
{
	if (INPUT.KeyCheck_Enter('S')) {
		//外部のテキストファイルへ保存
		UPtr<DataManager> uDM(new DataManager);
		uDM->DataSave("data/txt/Object1.txt", Obj_Num_Max);
	}
}

void EditWorld::Draw()
{
	// 升目のように線を引いて区切る
	//static int cnt;
	//for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(-50 + cnt * 1, 0, 50), YsVec3(-50 + cnt * 1, 0, -50), &YsVec4(1, 1, 1, 1));
	//for (cnt = 0; cnt < 100; cnt++)ShMgr.m_Samp.DrawLine(YsVec3(50, 0, -50 + cnt * 1), YsVec3(-50, 0, -50 + cnt * 1), &YsVec4(1, 1, 1, 1));
	ShMgr.m_Samp.DrawModel(m_moEdit, &m_mEdit);

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