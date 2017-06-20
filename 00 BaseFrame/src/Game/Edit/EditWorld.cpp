#include "main.h"
#include "Data/DataManager.h"
#include "Game\GameWorld\GameWorld.h"
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
		uDM->CsvDataSave("data/txt/Object.csv", Obj_Num_Max);
	}

}

void EditWorld::Draw()
{
	YsVec3 Vec;
	Vec.Transform(m_Cam.mCam);
	YsVec3 MousePos = YsVec3(INPUT.GetMousePos()->x, INPUT.GetMousePos()->y, 0);
	m_Cam.Convert2Dto3D(MousePos, MousePos);
	ShMgr.m_Samp.DrawLine(MousePos, YsVec3(0,0,0), &YsVec4(1, 1, 1, 1));

	Dw_Static(11, "Pos(%.2f, %.2f, %.2f)", (float)MousePos.x, (float)MousePos.y, Vec.z);
	Dw_Static(12, "CamPos(%.2f, %.2f, %.2f)", Vec.x, Vec.y, Vec.z);

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