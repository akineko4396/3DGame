#pragma once

//=======================================
// ���̒n�`���b�V���N���X
//=======================================
class Ground :public ObjectBase
{
public:

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moMap;
};