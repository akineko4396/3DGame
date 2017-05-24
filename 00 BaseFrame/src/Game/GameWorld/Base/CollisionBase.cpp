#include "main.h"
#include "CollisionBase.h"

void ViewFrustum::Create(YsMatrix _Proj, YsMatrix _View, YsMatrix _Cam)
{

	//射影行列とビュー行列を合成
	YsMatrix mVP = _View*_Proj;

	//カメラのワールド座標取得
	YsMatrix mInvV = _View;

	//逆行列作成
	mInvV.CreateInverse();

	//カメラ座標取得
	m_CamPos = _Cam.GetPos();

	//逆行列にする
	mVP.CreateInverse();

	//視錘台頂点名
	enum VERTEX
	{
		LeftTop = 0,
		RightTop = 1,
		LeftBottom = 2,
		RightBottom = 3,
		MAX,
	};

	//視錘台頂点格納用
	YsVec3 vFrustumVertex[VERTEX::MAX] = {
		YsVec3(-1, 1, 1),	//LeftTop
		YsVec3(1, 1, 1),	//RightTop
		YsVec3(-1, -1, 1),//LeftBottom
		YsVec3(1, -1, 1)	//RightBottom
	};

	//頂点までの距離格納用
	YsVec3 VertexLength[VERTEX::MAX] = {
		YsVec3(0, 0, 0),	//LeftTopまでの距離
		YsVec3(0, 0, 0),	//RigthTopまでの距離
		YsVec3(0, 0, 0),	//LeftBottomまでの距離
		YsVec3(0, 0, 0)	//RightBottomまでの距離
	};

	//頂点数分ループ
	for (int i = 0; i < VERTEX::MAX; i++)
	{

		//合成した行列と視錘台の頂点を合成するための射影行列
		YsMatrix mPVertex;

		//頂点行列化用
		YsMatrix mTransVertex;

		//2D頂点を行列化
		D3DXMatrixTranslation(&mTransVertex, vFrustumVertex[i].x, vFrustumVertex[i].y, vFrustumVertex[i].z);

		//3D空間として保管する
		D3DXVec3TransformCoord(&vFrustumVertex[i], &vFrustumVertex[i], &mVP);

		//カメラとの距離を格納
		VertexLength[i] = vFrustumVertex[i] - m_CamPos;
	}

	//それぞれの頂点同士を結びそれぞれの面に対しての外積を求める

	enum NVERTEX
	{
		NLeft = 0,
		NTop = 1,
		NRight = 2,
		NBottom = 3,
		NMAX
	};

	YsVec3 Cross[NVERTEX::NMAX];

	//NLeft
	D3DXVec3Cross(&m_vN[NVERTEX::NLeft], &vFrustumVertex[VERTEX::LeftBottom], &VertexLength[VERTEX::LeftTop]);

	//NTop
	D3DXVec3Cross(&m_vN[NVERTEX::NTop], &vFrustumVertex[VERTEX::LeftTop], &VertexLength[VERTEX::RightTop]);

	//NRight
	D3DXVec3Cross(&m_vN[NVERTEX::NRight], &vFrustumVertex[VERTEX::RightTop], &VertexLength[VERTEX::RightBottom]);

	//NButtom
	D3DXVec3Cross(&m_vN[NVERTEX::NBottom], &vFrustumVertex[VERTEX::RightBottom], &VertexLength[VERTEX::LeftBottom]);

	//正規化
	for (int i = 0; i < NVERTEX::NMAX; i++)
	{
		D3DXVec3Normalize(&m_vN[i], &m_vN[i]);
	}
}