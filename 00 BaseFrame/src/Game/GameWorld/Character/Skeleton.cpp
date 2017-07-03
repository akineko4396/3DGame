#include "main.h"
#include "../GameWorld.h"

void Skeleton::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//�@���f���f�[�^���Z�b�g
	m_moChara.SetModel(_gm);
	//�@�����̍s��ݒ�
	m_mChara = _m;

	//�@�A�j���[�^��������
	m_moChara.InitAnimator(m_aniSke);
	//�@�����A�j��
	m_aniSke.ChangeAnime_FromName("�ҋ@", true);

	//ID�ݒ�
	m_CharaId = OBJECT_LIST::ID::SKELETON;
}

void Skeleton::Update()
{
	// �S�g��WorldMat���Z�o
	m_moChara.CalcBoneMatrix_SkipRoot(&m_mChara);

	//�A�j���[�V������i�߂�
	// ���m�ɂ́A�A�j���[�V�����������ƂɁA�S�{�[���́uTransMat�v���X�V����
	m_aniSke.Animation(1.0);

	//�S�{�[���́uWorldMat�v���uTransMat�v�����ƂɎZ�o����
	// ���ۂɕ`��ȂǂŕK�v�Ȃ̂�����WorldMat�ł�
	m_moChara.CalcBoneMatrix(&m_mChara);
}

void Skeleton::Draw()
{
	// SampleShader�N���X�ŕ`�悷��
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}