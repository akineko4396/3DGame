#pragma once

//====================
// namespace
//====================
namespace OBJECT_LIST {

	enum ID {

		//プレイヤー
		PLAYER					=	0,

		//ボス
		BOSS						=	1,

		//スケルトン
		SKELETON				=	2,

		//デーモン
		DEMON					=	3,

		//ステージ
		GROUND				=	4,

		//拠点
		STRONGHOLD		=	5,

		//壁
		WALL					=	6,

		//投石器
		SLING					=	7,

		//大砲
		CANNON				=	8,

		//火炎放射器
		FLAMETHROWER	=	9,

		//プレス機
		PRESS					=	10,

		//アーム
		ARM						=	11,

		//ベルトコンベア
		BELTCONVEYOR		=	12,

		//ブリッジ
		BRIDGE					=	13,

		//オブジェクト最大数
		MAX_NUM,

		//初期化
		FREE				= -1,

	};

}

//===================================
// キャラクター基底クラス
// 　プレイヤーなどのクラスを管理する
//===================================
class CharacterBase :public BaseGameObj
{
public:

	//==================================
	// m_oList管理用関数
	//==================================
	//リストにオブジェクトを登録
	static void PushChara(SPtr<CharacterBase> _obj) { m_cList.push_back(_obj); }

	//オブジェクト全てを更新
	static void AllUpdate();

	//オブジェクト全てを描画
	static void AllDraw();

	//オブジェクト全てを解放
	static void FullClear();

	//キルフラグを確認
	static void CheckKillFlg();

	//リストのゲッター
	static std::vector<SPtr<CharacterBase>> & GetList() { return m_cList; }

	//カメラ処理
	virtual void SetCamera() {}

	//===========
	// ゲッター
	//===========

	//行列をセットする
	inline void SetMatrix(const YsMatrix _Mat) { m_mChara = _Mat; }

	//座標をセットする
	inline void SetPos(const YsVec3 _pos) { m_vPos = _pos; }

	//拡大サイズをセット
	inline void SetScale(const YsVec3 _scale) { m_vScale = _scale; }

	//回転量をセット
	inline void SetAngle(const YsVec3 _angle) { m_vAngle = _angle; }

	//キルフラグをセットする
	inline void SetKillFlg(const int _k) { m_killFlg = _k; }

	// 入力コントローラ(コンポーネント)をセット
	inline void SetInput(SPtr<GameInputComponent> p) {
		m_Controller = p;
	}

	//===========
	// セッター
	//===========

	//モデルデータを返す
	inline YsModelObject& GetModel() { return m_moChara; }

	//行列を返す
	inline YsMatrix GetMatrix() { return m_mChara; }

	//座標を返す
	inline YsVec3	GetPos() { return m_mChara.GetPos(); }

	//拡大サイズを返す
	inline YsVec3 GetScale() { return m_mChara.GetScale(); }

	//行列から回転量を返す
	inline YsVec3 GetAxis() { return YsVec3(m_mChara.GetXAxis().x, m_mChara.GetYAxis().y, m_mChara.GetZAxis().z); }

	//直接回転量を返す
	inline YsVec3 GetAngle() { return m_vAngle; }

	//キルフラグの情報を返す
	inline int	GetKillFlg() { return m_killFlg; }

	//オブジェクトIDを取得
	inline int	GetObjId() { return m_CharaId; }

	// 現在押されているキーを取得
	inline int GetKeys() { return m_Keys; }


	//	指定されたクラスをインスタンス化してリストに格納する
	template <class T>
	inline static SPtr<T> CreateCharaTask()
	{
		SPtr<T> add(new T);
		PushChara(add);
		return add;
	}

protected:

	//リスト
	static std::vector<SPtr<CharacterBase>> m_cList;
	
	//	モデルデータ
	YsModelObject		m_moChara;

	// 行列
	YsMatrix			m_mChara;

	// キャラの座標
	YsVec3			m_vPos;

	// キャラの拡大サイズ
	YsVec3			m_vScale;

	//キャラの回転量
	YsVec3			m_vAngle;

	//オブジェクトID
	int				m_CharaId;

	//キルフラグ
	int				m_killFlg;

	// 現在押下されてるキー このキー情報によりキャラを動かす(PlayerもAIも)
	// 各ビット(0～31)が各キーの状態
	int m_Keys = 0;

	// 入力コントローラ
	SPtr<GameInputComponent> m_Controller;
};