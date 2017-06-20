#pragma once

#include "Game\GameWorld\Base\ObjectBase.h"

class Helper {
public:

	/*オブジェクトごとのゲッター-----------------------------------------

	それぞれのゲッターの引数に
	　そのオブジェクトのIDと登録番号を入れることで
	 　そのオブジェクトの情報が返る

	---------------------------------------------------------------------------*/
	//プレイヤー
	inline SPtr<ObjectBase> GetObject_Player() { return ObjectBase::GetThisObject(0, OBJECT_LIST::ID::PLAYER); }

	//エネミー
	inline SPtr<ObjectBase> GetObject_Enemy(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::ENEMY); }

	//マップ
	inline SPtr<ObjectBase> GetObject_Ground() { return ObjectBase::GetThisObject(0, OBJECT_LIST::ID::GROUND); }

	//拠点
	inline SPtr<ObjectBase> GetObject_Stronghold() { return ObjectBase::GetThisObject(0, OBJECT_LIST::ID::STRONGHOLD); }

	//壁
	inline SPtr<ObjectBase> GetObject_Wall(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::WALL); }

	//投石器
	inline SPtr<ObjectBase> GetObject_SLING(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::SLING); }

	//大砲
	inline SPtr<ObjectBase> GetObject_Cannon(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::CANNON); }

	//火炎放射器
	inline SPtr<ObjectBase> GetObject_Flamethrower(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::FLAMETHROWER); }

	//プレス機
	inline SPtr<ObjectBase> GetObject_Press(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::PRESS); }

	//アーム
	inline SPtr<ObjectBase> GetObject_Arm(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::ARM); }

	//ベルトコンベア
	inline SPtr<ObjectBase> GetObject_BeltConveyor(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::BELTCONVEYOR); }

	//ブリッジ
	inline SPtr<ObjectBase> GetObject_Bridge(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::BRIDGE); }

	//全てのオブジェクト
	inline SPtr<ObjectBase> GetObject_All(int _num) { return ObjectBase::GetThisObject(_num); }

	//------------------------------------------------------------------
	// シングルトン
private:
	Helper() {}
public:
	static Helper& GetInstance()
	{
		static Helper instance;
		return instance;
	}
	//------------------------------------------------------------------
};

#define HELP Helper::GetInstance()