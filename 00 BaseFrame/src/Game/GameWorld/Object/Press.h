#pragma once

//=======================================
// �v���X�@�N���X
//=======================================
class Press :public CharacterBase
{
public:

	//�����ݒ�
	void Init(YsMatrix& _m, SPtr<YsGameModel>& _gm);

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

	//�J��������
	virtual void SetCamera() override {};
};