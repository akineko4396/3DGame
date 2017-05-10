#pragma once

//===================================
// オブジェクトの基底クラス
// 　オブジェクトのクラスを管理する
//===================================
class ObjectBase :public BaseGameObj
{
public:

	//==================================
	// m_oList管理用関数
	//==================================
	//リストにオブジェクトを登録
	static void PushObject(SPtr<ObjectBase> _obj){ m_oList.push_back(_obj); }

	//オブジェクト全てを更新
	static void AllUpdate();

	//オブジェクト全てを描画
	static void AllDraw();

	//オブジェクト全てを解放
	static void FullClear();

	//キルフラグを確認
	static void CheckKillFlg();

	//リストのゲッター
	static std::vector<SPtr<ObjectBase>> & GetList(){ return m_oList; }

	enum { GROUND };

	//オブジェクト情報を返す
	static SPtr<ObjectBase>	GetThisObject(int _id);

	//===========
	// ゲッター
	//===========

	//座標をセットする
	inline void SetPos(const YsVec3 _pos){ m_vPos = _pos; }

	//拡大サイズをセット
	inline void SetScale(const YsVec3 _scale){ m_vScale = _scale; }

	//回転量をセット
	inline void SetAngle(const YsVec3 _angle){ m_vAngle = _angle; }

	//キルフラグをセットする
	inline void SetKillFlg(const int _k){ m_killFlg = _k; }

	//個別IDをセット
	inline void SetId(const int _n){ m_Id = _n; }

	//===========
	// セッター
	//===========

	//キルフラグの情報を返す
	inline int	GetKillFlg(){ return m_killFlg; }

	//個別IDを取得
	inline int	GetId(){ return m_Id; }

protected:

	// モデルデータ
	SPtr<YsGameModel>	m_gmObj;

	// 行列
	YsMatrix			m_mObj;

	// キャラの座標
	YsVec3			m_vPos;

	// キャラの拡大サイズ
	YsVec3			m_vScale;

	//キャラの回転量
	YsVec3			m_vAngle;

	//モデルID
	int				m_Id;

	//キルフラグ
	int				m_killFlg;

	//リスト
	static std::vector<SPtr<ObjectBase>> m_oList;
};