#pragma once

//====================
// namespace
//====================
namespace OBJECT_LIST {

	enum ID {

		//プレイヤー
		PLAYER			= 0,

		//敵
		ENEMY			= 1,

		//ステージ
		GROUND		= 2,

		//アーム
		ARM				= 3,

		//ベルトコンベア
		BELT				= 4,

		//オブジェクト最大数
		MAX_NUM,

		//初期化
		FREE				= -1,

	};

}

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

	//オブジェクト情報を返す
	static SPtr<ObjectBase>	GetThisObject(int _Num);

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
	inline void SetNum(const int _n){ m_Num = _n; }

	//===========
	// セッター
	//===========

	//行列を返す
	inline YsMatrix GetMatrix() { return m_Mat; }

	//座標を返す
	inline YsVec3	GetPos() { return m_vPos; }

	//拡大サイズを返す
	inline YsVec3 GetScale() { return m_vScale; }

	//回転量を返す
	inline YsVec3 GetAngle() { return m_vAngle; }

	//キルフラグの情報を返す
	inline int	GetKillFlg(){ return m_killFlg; }

	//オブジェクトIDを取得
	inline int	GetObjId() { return m_ObjId; }

	//個別IDを取得
	inline int	GetNum(){ return m_Num; }


	//	指定されたクラスをインスタンス化してリストに格納する
	template <class T>
	inline static SPtr<T> CreateObjectTask()
	{
		SPtr<T> add(new T);
		PushObject(add);
		return add;
	}

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

	//オブジェクトID
	int				m_ObjId;

	//個体ナンバー
	int				m_Num;

	//キルフラグ
	int				m_killFlg;

	//リスト
	static std::vector<SPtr<ObjectBase>> m_oList;
};