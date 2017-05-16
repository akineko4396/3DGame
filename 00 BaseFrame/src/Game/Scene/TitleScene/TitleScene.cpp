#include "main.h"
#include "TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../SampleScene/SampleScene.h"
#include "../EditScene/EditScene.h"

//=========================================
// 更新処理
//=========================================
int TitleScene::Update()
{
	// Spaceキー
	if(INPUT.KeyCheck_Enter(VK_SPACE)){
		// シーン切り替え
		SPtr<GameScene> gs(new GameScene());
		gs->Init();
		APP.m_NowScene = gs;

		return 1;
	}

	//Shiftキー
	if (INPUT.KeyCheck_Enter(VK_SHIFT)) {
		// シーン切り替え
		SPtr<EditScene> es(new EditScene());
		es->Init();
		APP.m_NowScene = es;

		return 1;
	}

	// Enter
	if(INPUT.KeyCheck_Enter(VK_RETURN)){
		// シーン切り替え
		SPtr<SampleScene> ss(new SampleScene());
		ss->Init();
		APP.m_NowScene = ss;

		return 1;
	}

	// Escapeキー
	if(INPUT.KeyCheck_Enter(VK_ESCAPE)){
		APP.ExitGame();
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

	
	//=========================================================
	// カメラ操作
	//=========================================================
	m_Cam.Update();

	//=========================================================
	// キャラ処理
	//=========================================================

	//---------------------------------------------
	// キャラ１
	//---------------------------------------------
	{

		if(INPUT.KeyCheck_Enter('Z')) {
			m_Chara.m_Anim.ChangeAnimeSmooth_FromName("ターン", 0, 0, true);
		}
		if(INPUT.KeyCheck_Enter('X')) {
			m_Chara.m_Anim.ChangeAnimeSmooth_FromName("立ち", 0, 10, true);
		}
		if(INPUT.KeyCheck_Enter('C')) {
			m_Chara.m_Anim.ChangeAnimeSmooth_FromName("歩き", 0, 10, true);
		}

		//-------------------------------------
		// 単純なアニメーションのみを行う方法
		//-------------------------------------
		/*
		// アニメーションを進める
		m_Chara.m_Anim.Animation(1.0);
		// 全ボーン、TransMatを使いWorldMatを更新
		m_Chara.m_Mo.CalcBoneMatrix(&m_Chara.m_Mat);
		*/

		//-------------------------------------
		// Rootボーンをキャラの移動用に使い、アニメーション＋移動を行う方法
		//-------------------------------------
		// アニメーションを進める
		// ※Rootボーンに変化量により、m_Chara.m_Matが変化する
		m_Chara.m_Anim.Animation(1.0, &m_Chara.m_Mat);
		// 全ボーン、TransMatを使いWorldMatを更新
		// ※Rootボーンは移動用として使ったので、無視する
		m_Chara.m_Mo.CalcBoneMatrix_SkipRoot(&m_Chara.m_Mat);

	}

	//---------------------------------------------
	// キャラ２
	//---------------------------------------------
	{
		// アニメ進行し、全ボーンのTransMatを更新
		// ※Rootボーンに変化量により、引数で指定した行列が変化する
		m_Chara2.m_Anim.Animation(1.0, &m_Chara2.m_Mat);
		
		// アニメ進行し、全ボーンのTransMatを更新
		// ※今回ここには、上半身のみのアニメを再生しているので、上半身だけが更新される！
		m_Chara2.m_Anim2.Animation(1.0);

		// 全ボーン、TransMatを使いWorldMatを更新
		m_Chara2.m_Mo.CalcBoneMatrix_SkipRoot(&m_Chara2.m_Mat);

	}

	//---------------------------------------------
	// 箱
	//---------------------------------------------
	for(int i=0;i<400;i++)
	{
		//-------------------------------------
		// 単純なアニメーションのみを行う方法
		//-------------------------------------
//		m_Box[i].m_Anim.Animation(1.0);
//		m_Box[i].m_Mo.CalcBoneMatrix(&m_Box[i].m_Mat);

		//-------------------------------------
		// Rootボーンをキャラの移動用に使い、アニメーション＋移動を行う方法
		//-------------------------------------
		m_Box[i].m_Anim.Animation(1.0, &m_Box[i].m_Mat);
		m_Box[i].m_Mo.CalcBoneMatrix_SkipRoot(&m_Box[i].m_Mat);
	}

	return 0;
}

//=========================================
// 描画処理
//=========================================
void TitleScene::Draw()
{
	//==========================================
	// クリア
	//==========================================
	// バックバッファをクリアする。
	YsDx.GetBackBuffer()->ClearRT(YsVec4(0.3f, 0.3f, 0.8f, 1));
	// Zバッファのクリア
	YsDx.GetDepthStencil()->ClearDepth(true, true);

	// 半透明モードに
	ShMgr.m_bsAlpha.SetState();


	//==========================================
	// カメラ設定
	//==========================================
	m_Cam.SetCamera();

	//==========================================
	// 描画直前にシェーダのフレーム単位データを更新する
	//==========================================
	ShMgr.UpdateBeforeDraw();


	// 描画などを書く


	//==========================================
	// [2D]背景描画
	//==========================================
	YsDx.GetSprite().Begin();
	{
		YsDx.GetSprite().Draw(*m_texBack, 0, 0, m_texBack->GetInfo().Width, m_texBack->GetInfo().Height);
	}
	YsDx.GetSprite().End();

	//==========================================
	// [3D]モデル描画
	//==========================================

	// 箱キャラ描画
	for (int i = 0; i < 400; i++) {
		ShMgr.m_Samp.DrawModel(m_Box[i].m_Mo, &m_Box[i].m_Mat);
	}

	// キャラ１描画
	ShMgr.m_Samp.DrawModel(m_Chara.m_Mo, &m_Chara.m_Mat);
	// 輪郭描画
	ShMgr.m_Samp.DrawModelOutline(m_Chara.m_Mo, &YsVec4(0.2f, 0.2f, 0.2f, 0.5f), &YsVec2(0.0005f, 0.015f));

	// キャラ２描画
	ShMgr.m_Es.DrawModel(m_Chara2.m_Mo, &m_Chara2.m_Mat);


	// 説明文字
	std::string text;
	text = "[タイトルシーン]\n";
	text += "Space:ゲームシーンへ\n";
	text += "Enter:サンプルシーンへ\n";
	text += "Alt+Enter:フルスクリーン切り替え\n";
	text += "Z、X、C:アニメーション変更\n";

	// 2D描画
	YsDx.GetSprite().Begin(true);
	{
		YsDx.GetSprite().DrawFont(text, 1, 1, &YsVec4(0, 0, 0, 1));
		YsDx.GetSprite().DrawFont(text, 0, 0, &YsVec4(1, 1, 1, 1));

	}
	YsDx.GetSprite().End();

}

//============================================================
// データ解放
//============================================================
void TitleScene::Release()
{
	// サウンド停止
	YsSndMgr.StopAll();


	Dw_Scroll(0, "タイトルシーン解放処理");
}

//============================================================
// 初期設定
//============================================================
void TitleScene::Init()
{
	Dw_Scroll(0, "タイトルシーン初期化");

	// 平行ライト作成
	m_DirLight = ShMgr.m_LightMgr.AddDirLight();

	// カメラデータ初期化
	m_Cam.Init(20, 130, -3);
	m_Cam.m_BaseMat.SetPos(0, 1.2f, 0);

	//--------------------------------------------------------
	// テクスチャ読み込み
	//--------------------------------------------------------
	m_texBack = APP.m_ResStg.LoadTexture("data/Texture/title_back.png");

	//--------------------------------------------------------
	//
	// モデル読み込み
	//  APP.m_ResStgの代わりに、YsDx.GetResStg()を使用してもいい(どっちも同じ)
	//
	//--------------------------------------------------------
	// 3Dモデルを読み込み、そのアドレスを記憶。
	SPtr<YsGameModel> gmChara = APP.m_ResStg.LoadMesh("data/model/Hackadoll_1/model.xed");
	SPtr<YsGameModel> gmBox = APP.m_ResStg.LoadMesh("data/model/box/box.x");


	//--------------------------------------------------------
	//
	// キャラ設定
	//
	//--------------------------------------------------------

	// キャラ１設定
	m_Chara.m_Mo.SetModel(gmChara);						// モデルをメッシュオブジェクトへセットし、使える状態にする
	m_Chara.m_Mat.CreateMove(0, 0, 0);						// 初期行列を設定

	m_Chara.m_Mo.InitAnimator(m_Chara.m_Anim);				// アニメーター設定　こいつでアニメーションができる
	m_Chara.m_Anim.ChangeAnime(1, true);					// アニメ変更

	// キャラ２設定
	m_Chara2.m_Mo.SetModel(gmChara);						// モデルをメッシュオブジェクトへセットし、使える状態にする
	m_Chara2.m_Mat.CreateMove(1, 0, 0);						// 初期行列を設定

	m_Chara2.m_Mo.InitAnimator(m_Chara2.m_Anim);			// アニメーター設定　こいつでアニメーションができる
	m_Chara2.m_Mo.InitAnimator(m_Chara2.m_Anim2);			// アニメーター設定　こいつでアニメーションができる

	m_Chara2.m_Anim.ChangeAnime(1, true);							// アニメ変更
	m_Chara2.m_Anim2.ChangeAnime_FromName("[特殊]魔法１", true);	// アニメ変更　アニメ名でも指定できる　今回は上半身だけのアニメを設定する

	// 箱キャラ設定 400個
	{

		// 全箱キャラ設定
		for (int i = 0; i < 400; i++) {
			// 座標
			float x = (i / 20 - 10) * 3.0f;
			float z = (i % 20 - 10) * 3.0f;

			m_Box[i].m_Mo.SetModel(gmBox);					// モデルをメッシュオブジェクトへセットし、使える状態にする
			m_Box[i].m_Mat.CreateMove(x, -1, z);				// 初期行列を設定

			m_Box[i].m_Mo.InitAnimator(m_Box[i].m_Anim);		// アニメーター設定　こいつでアニメーションができる
		}

		//---------------------------------
		// ※アニメを途中で追加する方法
		//---------------------------------

		// アニメを１つ読み込み追加登録する
		SPtr<YsAnimationSet> ani = std::make_shared<YsAnimationSet>();	// アニメデータ作成
		ani->LoadXMD("data/model/box/move2.xmd", "あにめ");				// アニメデータ読み込み
		m_Box[211].m_Anim.AddAnimation(ani);							// アニメータに途中でアニメを追加することもできる
			// 簡易的に、下記の１行の書き方でもOK
			//m_Box[211].m_Anim.AddAnimation("data/model/box/move.xmd", "あにめ");	// アニメを読み込み、追加

		m_Box[211].m_Anim.ChangeAnime_FromName("あにめ", true);		// アニメ変更
	}


}
