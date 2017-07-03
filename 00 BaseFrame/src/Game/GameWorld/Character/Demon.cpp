#include "main.h"
#include "../GameWorld.h"

void Demon::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//�@���f���f�[�^���Z�b�g
	m_moChara.SetModel(_gm);
	//�@�����̍s��ݒ�
	m_mChara = _m;

	//�@�A�j���[�^��������
	m_moChara.InitAnimator(m_aniDe);
	//�@�����A�j��
	m_aniDe.ChangeAnime_FromName("����", true);

	//ID�ݒ�
	m_CharaId = OBJECT_LIST::ID::DEMON;
}

void Demon::Update()
{
	// �S�g��WorldMat���Z�o
	m_moChara.CalcBoneMatrix_SkipRoot(&m_mChara);

	static int cnt = 0;

	switch (cnt) {
	case 200:
		m_aniDe.ChangeAnimeSmooth_FromName("�U��1", 0, 10, true);
		break;
	case 400:
		m_aniDe.ChangeAnimeSmooth_FromName("�U��2", 0, 10, true);
		break;
	case 600:
		m_aniDe.ChangeAnimeSmooth_FromName("����", 0, 10, true);
		cnt = 0;
		break;
	}
	cnt++;

	//�A�j���[�V������i�߂�
	// ���m�ɂ́A�A�j���[�V�����������ƂɁA�S�{�[���́uTransMat�v���X�V����
	m_aniDe.Animation(1.0);

	//�S�{�[���́uWorldMat�v���uTransMat�v�����ƂɎZ�o����
	// ���ۂɕ`��ȂǂŕK�v�Ȃ̂�����WorldMat�ł�
	m_moChara.CalcBoneMatrix(&m_mChara);
}

void Demon::Draw()
{
	// SampleShader�N���X�ŕ`�悷��
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}