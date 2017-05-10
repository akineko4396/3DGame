#pragma once

//===================================
// キャラクターの基底クラス
// 　キャラクターのクラスを管理する
//===================================
class CharacterBase :public BaseGameObj
{
public:

	//==================================
	// m_cList管理用関数
	//==================================
	//リストにオブジェクトを登録
	static void PushObject(SPtr<CharacterBase> _obj){ m_cList.push_back(_obj); }

	//オブジェクト全てを更新
	static void AllUpdate();

	//オブジェクト全てを描画
	static void AllDraw();

	//オブジェクト全てを解放
	static void FullClear();

	//キルフラグを確認
	static void CheckKillFlg();

	//リストのゲッター
	static std::vector<SPtr<CharacterBase>> & GetList(){ return m_cList; }

	//識別番号
	enum { PLAYER };

	//オブジェクト情報を返す
	static SPtr<CharacterBase>	GetThisCharacter(int _id);

	//===========
	// セッター
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
	// ゲッター
	//===========

	//行列を返す
	inline YsMatrix GetMatrix(){ return m_Mat; }

	//キルフラグの情報を返す
	inline int	GetKillFlg(){ return m_killFlg; }

	//個別IDを取得
	inline int	GetId(){ return m_Id; }


	//	指定されたクラスをインスタンス化してリストに格納する
	template <class T>
	inline SPtr<T> CreateCharacterTask()
	{
		SPtr<T> add(new T);
		PushObject(add);
		return add;
	}

protected:

	// モデルデータ
	SPtr<YsGameModel>		m_gmChara;

	// キャラの行列
	YsMatrix		m_mChara;

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
	static std::vector<SPtr<CharacterBase>> m_cList;

};