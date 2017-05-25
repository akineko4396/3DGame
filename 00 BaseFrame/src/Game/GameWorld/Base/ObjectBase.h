#pragma once

//====================
// namespace
//====================
namespace OBJECT_LIST {

	enum ID {

		//プレイヤー
		PLAYER					=	0,

		//敵
		ENEMY					=	1,

		//ステージ
		GROUND				=	2,

		//拠点
		STRONGHOLD		=	3,

		//壁
		WALL					=	4,

		//投石器
		SLING					=	5,

		//大砲
		CANNON				=	6,

		//火炎放射器
		FLAMETHROWER	=	7,

		//プレス機
		PRESS					=	8,

		//アーム
		ARM						=	9,

		//ベルトコンベア
		BELTCONVEYOR		=	10,

		//ブリッジ
		BRIDGE					=	11,

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

	// 入力コントローラ(コンポーネント)をセット
	inline void SetInput(SPtr<GameInputComponent> p) {
		m_Controller = p;
	}

	//===========
	// セッター
	//===========

	//モデルデータを返す
	inline SPtr<YsGameModel> GetModel() { return m_gmObj; }

	//行列を返す
	inline YsMatrix GetMatrix() { return m_mObj; }

	//座標を返す
	inline YsVec3	GetPos() { return m_mObj.GetPos(); }

	//拡大サイズを返す
	inline YsVec3 GetScale() { return m_mObj.GetScale(); }

	//回転量を返す
	inline YsVec3 GetAngle() { return YsVec3(m_mObj.GetXAxis().x, m_mObj.GetYAxis().y, m_mObj.GetZAxis().z); }

	//キルフラグの情報を返す
	inline int	GetKillFlg(){ return m_killFlg; }

	//オブジェクトIDを取得
	inline int	GetObjId() { return m_ObjId; }

	//個別IDを取得
	inline int	GetNum(){ return m_Num; }

	// 現在押されているキーを取得
	inline int GetKeys() { return m_Keys; }


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

	// 現在押下されてるキー このキー情報によりキャラを動かす(PlayerもAIも)
	// 各ビット(0～31)が各キーの状態
	int m_Keys = 0;

	// 入力コントローラ
	SPtr<GameInputComponent> m_Controller;
};