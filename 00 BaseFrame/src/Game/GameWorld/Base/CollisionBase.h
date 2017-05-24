#pragma once

//========================================
// �Փ˔���Ǘ��̃X�[�p�[�N���X
//========================================


/*ViewFrustum==============================

������N���X

��������쐬����

=========================================*/
class ViewFrustum {

public:

	//������쐬
	void Create(YsMatrix _Proj, YsMatrix _View, YsMatrix _Cam);

	//�J��������̖@����Ԃ�
	inline YsVec3 GetNormal(int _i) { return m_vN[_i]; }

	//�ۑ����Ă���J�����̍��W��Ԃ�
	inline YsVec3 GetCamPos() { return m_CamPos; }

private:

	//�J�����̍��W�i�[�p
	YsVec3	m_CamPos;

	//	�J��������@��
	YsVec3	m_vN[4];

	//�\����
	struct CLONEVERTEX {
		YsVec3 Pos;
		YsVec3 Normal;
		YsVec2 Tex;
	};

public:

	//--------------------------
	//	�V���O���g���p�^�[������
	//--------------------------
	static ViewFrustum& GetInstance()
	{
		static ViewFrustum Instance;
		return Instance;
	}

};

// �ȒP�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃}�N��
#define VF	ViewFrustum::GetInstance()

/*===============

template�֐�

===============*/

/*<template>CheckViewFrustum-------------------------------->

������ƃL�������b�V���̃X�t�B�A�Ƃ̔���

_MyData		:	���g�̃f�[�^

return true	:	�������
return false:	������O

<-----------------------------------------------------*/
template <class T>
inline BOOL CheckViewFrustum(SPtr<T>& _MyData, SPtr<YsMesh> _Mesh)
{

	//���g����J�����܂ł̋����i�[�p
	YsVec3 vTargetVec = _MyData->GetPos();

	//���������g�̍��W�[�J�����̍��W
	vTargetVec = vTargetVec - VF.GetCamPos();

	for (int i = 0; i < 4; i++)
	{
		//���ς����߂�
		float Len = 0;

		//���ς�Ԃ�
		Len = D3DXVec3Dot(&vTargetVec, &VF.GetNormal(i));

		//���ςŋ��߂����� > ���g�̃o�E���f�B���O�X�t�B�A�̔��a
		if (Len > _Mesh->GetBSRadius())
		{
			//�`�悵�Ȃ�
			return false;
		}
	}

	//�`�悷��
	return true;
}