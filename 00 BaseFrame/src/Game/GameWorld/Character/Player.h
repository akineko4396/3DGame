#pragma once

//====================================
// �v���C���[�N���X
//====================================
class Player :public ObjectBase
{
public: 

	//�������ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// ���f���I�u�W�F�N�^�i�L�����N�^�j
	YsModelObject	m_moPla;

	// �A�j���[�^�[
	YsAnimator		m_aniPla;

};