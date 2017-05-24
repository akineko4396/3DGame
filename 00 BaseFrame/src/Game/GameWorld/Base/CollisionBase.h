#pragma once

//========================================
// 衝突判定管理のスーパークラス
//========================================


/*ViewFrustum==============================

視錘台クラス

視錘台を作成する

=========================================*/
class ViewFrustum {

public:

	//視錘台作成
	void Create(YsMatrix _Proj, YsMatrix _View, YsMatrix _Cam);

	//カメラからの法線を返す
	inline YsVec3 GetNormal(int _i) { return m_vN[_i]; }

	//保存しているカメラの座標を返す
	inline YsVec3 GetCamPos() { return m_CamPos; }

private:

	//カメラの座標格納用
	YsVec3	m_CamPos;

	//	カメラから法線
	YsVec3	m_vN[4];

	//構造体
	struct CLONEVERTEX {
		YsVec3 Pos;
		YsVec3 Normal;
		YsVec2 Tex;
	};

public:

	//--------------------------
	//	シングルトンパターン生成
	//--------------------------
	static ViewFrustum& GetInstance()
	{
		static ViewFrustum Instance;
		return Instance;
	}

};

// 簡単にアクセスできるようにするためのマクロ
#define VF	ViewFrustum::GetInstance()

/*===============

template関数

===============*/

/*<template>CheckViewFrustum-------------------------------->

視錘台とキャラメッシュのスフィアとの判定

_MyData		:	自身のデータ

return true	:	視錘台内
return false:	視錘台外

<-----------------------------------------------------*/
template <class T>
inline BOOL CheckViewFrustum(SPtr<T>& _MyData, SPtr<YsMesh> _Mesh)
{

	//自身からカメラまでの距離格納用
	YsVec3 vTargetVec = _MyData->GetPos();

	//距離＝自身の座標ーカメラの座標
	vTargetVec = vTargetVec - VF.GetCamPos();

	for (int i = 0; i < 4; i++)
	{
		//内積を求める
		float Len = 0;

		//内積を返す
		Len = D3DXVec3Dot(&vTargetVec, &VF.GetNormal(i));

		//内積で求めた距離 > 自身のバウンディングスフィアの半径
		if (Len > _Mesh->GetBSRadius())
		{
			//描画しない
			return false;
		}
	}

	//描画する
	return true;
}