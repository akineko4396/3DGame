#ifndef __GameScene_h__
#define __GameScene_h__

#include "Game/GameCamera.h"

//=========================================================
// �Q�[���V�[���N���X
//=========================================================
class GameScene : public BaseScene{
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
	GameScene() {
	}
	// 
	virtual ~GameScene() {
		Release();
	}

public:
	//=========================================================
	// ���̑��f�[�^
	//=========================================================

	// ���s����
	SPtr<DirLight>	m_DirLight;

	// ���s�����̖��邳
	float			m_LightPower;


};

#endif