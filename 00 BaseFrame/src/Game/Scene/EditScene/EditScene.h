#pragma once

#include "Game/GameCamera.h"

//=========================================================
// �Q�[���V�[���N���X
//=========================================================
class EditScene : public BaseScene {
public:

	// �����ݒ�֐�
	void Init();
	// ����֐�
	void Release();
	// �X�V����
	virtual int Update() override;
	// �`�揈��
	virtual void Draw() override;

	// 
	EditScene() {
	}
	// 
	virtual ~EditScene() {
		Release();
	}

public:
	//=========================================================
	// ���̑��f�[�^
	//=========================================================

	//=================
	//�@�J����
	//=================
	GameCamera		m_Cam;

	// ���s����
	SPtr<DirLight>	m_DirLight;

	// ���s�����̖��邳
	float			m_LightPower;


};