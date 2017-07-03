#include "main.h"
#include "../GameWorld.h"
#include "../Base/CollisionBase.h"

std::vector<SPtr<CharacterBase>> CharacterBase::m_cList;

// �S�Ă̕`����s��
void CharacterBase::AllUpdate()
{
	for (UINT ec = 0; ec < m_cList.size(); ec++)
	{
		m_cList[ec]->Update();
	}
}

// �S�Ă̕`����s��
void CharacterBase::AllDraw()
{
	for (UINT ec = 0; ec < m_cList.size(); ec++)
	{
		//���b�V�����Ԃ񃋁[�v
		for (UINT i = 0; i < m_cList[ec]->GetModel().GetGameModel()->GetModelTbl().size(); i++) {
			//YsSingleModel���烁�b�V�����擾
			SPtr<YsSingleModel> model = m_cList[ec]->GetModel().GetGameModel()->GetModelTbl()[i];
			SPtr<YsMesh> mesh = model->GetMesh();

			//������ŕ`�攻��
			if (CheckViewFrustum(m_cList[ec], mesh)) {
				m_cList[ec]->Draw();
			}
		}
	}
}

void CharacterBase::FullClear()
{
	m_cList.clear();
}

// �L���t���O�𒲂ׂė����Ă����烊�X�g�������
void CharacterBase::CheckKillFlg()
{
	std::vector<SPtr<CharacterBase>>::iterator it = m_cList.begin();
	while (it != m_cList.end())
	{
		if ((*it)->GetKillFlg() == 1)
		{
			*it = nullptr;
			it = m_cList.erase(it);
		}
		else{
			it++;
		}
	}
}