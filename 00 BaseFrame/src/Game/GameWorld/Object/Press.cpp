#include "main.h"
#include "../GameWorld.h"


void Press::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//メッシュ読み込み
	//m_gmChara = YsDx.GetResStg()->LoadMesh("data/model/box/box.x");

	// ステージマップをセット
	m_moChara.SetModel(_gm);

	//　初期の行列設定
	m_mChara = _m;

	//ID設定
	m_CharaId = OBJECT_LIST::ID::PRESS;
}

void Press::Update()
{

}

void Press::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}
