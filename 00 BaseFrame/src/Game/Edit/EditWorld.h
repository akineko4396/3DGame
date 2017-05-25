#pragma once

//==========================
// namespace
//==========================
namespace OPTION {

	enum ID {

		//�I�u�W�F�N�g
		OBJ = 0,

		//���W
		POS = 1,

		//�g��T�C�Y
		SCALE = 2,

		//��]��
		ANGLE = 3,

		//�ő吔
		MAX_NUM = 4,

	};

}


#include "Game/GameCamera.h"

//======================================================
//
//�G�f�B�b�g���[���h�N���X
//
//�@�Q�[���̐��E���쐬�����b�ƂȂ�N���X
//�@���݂̓Q�[���V�[�����̃J�����̊Ǘ���������ł���Ă���
//
//======================================================
class EditWorld {
public:
	//������
	void Init(int _ObjNum);

	//���
	void Release();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�v���C���[�̍��W�Z�b�g
	inline void SetPPos(YsVec3 _pos) { pPos = _pos; }

	//=================
	// ���̑�
	//=================
	bool	m_PauseFlag = false;	//�|�[�YON/OFF

	int	Obj_Num_Max = 0;	//�I�u�W�F�N�g�̐��i�[�p

	//=================
	//�@�J����
	//=================
	GameCamera m_Cam;


	//================================
	//�@�V���O���g���p�^�[��
	//================================
private:
	//�C���X�^���X�p
	static EditWorld*	s_pInst;

	//�O������C���X�^���X�������Ȃ�����private�R���X�g���N�^
	EditWorld() {
	}

public:
	//�Q�[�����[���h�폜
	static void DeleteWorld() {
		YsSafe_Delete(s_pInst);
	}

	//�Q�[�����[���h�쐬
	static void CreateWorld() {
		DeleteWorld();
		s_pInst = new EditWorld();
	}

	//�Q�[�����[���h�擾
	static EditWorld& GetWorld() {
		return *s_pInst;
	}

private:

	//=======================
	// �G�f�B�b�g�ɕK�v�ȕϐ�
	//=======================
	int				m_OptionId;		//�I�v�V����ID
	int				m_ObjId;			//�I�u�W�F�N�gID
	YsVec3			m_Pos;				//���W
	YsVec3			m_Scale;			//�g��T�C�Y
	YsVec3			m_Angle;			//��]��

	BOOL			m_EditFlg;			//�G�f�B�b�g�p�t���O

	RECT			m_EditButton;	//�G�f�B�b�g�p�̃{�^�����W

	YsModelObject	m_moEdit;		//���ڏ�̃��b�V��
	YsMatrix			m_mEdit;			//���ڏ�̃��b�V���̍s��

	YsVec3			pPos;						//�v���C���[�̍��W�i�[�p
};

#define EW EditWorld::GetWorld()