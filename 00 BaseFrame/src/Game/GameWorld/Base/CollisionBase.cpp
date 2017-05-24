#include "main.h"
#include "CollisionBase.h"

void ViewFrustum::Create(YsMatrix _Proj, YsMatrix _View, YsMatrix _Cam)
{

	//�ˉe�s��ƃr���[�s�������
	YsMatrix mVP = _View*_Proj;

	//�J�����̃��[���h���W�擾
	YsMatrix mInvV = _View;

	//�t�s��쐬
	mInvV.CreateInverse();

	//�J�������W�擾
	m_CamPos = _Cam.GetPos();

	//�t�s��ɂ���
	mVP.CreateInverse();

	//�����䒸�_��
	enum VERTEX
	{
		LeftTop = 0,
		RightTop = 1,
		LeftBottom = 2,
		RightBottom = 3,
		MAX,
	};

	//�����䒸�_�i�[�p
	YsVec3 vFrustumVertex[VERTEX::MAX] = {
		YsVec3(-1, 1, 1),	//LeftTop
		YsVec3(1, 1, 1),	//RightTop
		YsVec3(-1, -1, 1),//LeftBottom
		YsVec3(1, -1, 1)	//RightBottom
	};

	//���_�܂ł̋����i�[�p
	YsVec3 VertexLength[VERTEX::MAX] = {
		YsVec3(0, 0, 0),	//LeftTop�܂ł̋���
		YsVec3(0, 0, 0),	//RigthTop�܂ł̋���
		YsVec3(0, 0, 0),	//LeftBottom�܂ł̋���
		YsVec3(0, 0, 0)	//RightBottom�܂ł̋���
	};

	//���_�������[�v
	for (int i = 0; i < VERTEX::MAX; i++)
	{

		//���������s��Ǝ�����̒��_���������邽�߂̎ˉe�s��
		YsMatrix mPVertex;

		//���_�s�񉻗p
		YsMatrix mTransVertex;

		//2D���_���s��
		D3DXMatrixTranslation(&mTransVertex, vFrustumVertex[i].x, vFrustumVertex[i].y, vFrustumVertex[i].z);

		//3D��ԂƂ��ĕۊǂ���
		D3DXVec3TransformCoord(&vFrustumVertex[i], &vFrustumVertex[i], &mVP);

		//�J�����Ƃ̋������i�[
		VertexLength[i] = vFrustumVertex[i] - m_CamPos;
	}

	//���ꂼ��̒��_���m�����т��ꂼ��̖ʂɑ΂��Ă̊O�ς����߂�

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

	//���K��
	for (int i = 0; i < NVERTEX::NMAX; i++)
	{
		D3DXVec3Normalize(&m_vN[i], &m_vN[i]);
	}
}