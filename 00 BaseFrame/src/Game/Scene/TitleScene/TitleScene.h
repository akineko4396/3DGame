#ifndef __TitleScene_h__
#define __TitleScene_h__

#include "Game/GameCamera.h"

//=========================================================
// �^�C�g���V�[���N���X
//=========================================================
class TitleScene : public BaseScene {
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
	TitleScene() {
	}
	// 
	virtual ~TitleScene() {
		Release();
	}

public:
	//=========================================================
	// ���̑��f�[�^
	//=========================================================

	// ���s����
	SPtr<DirLight>	m_DirLight;

	// �J����
	GameCamera		m_Cam;			// �J�����N���X

};


#endif