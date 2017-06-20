#include "main.h"
#include "../GameWorld.h"
#include "../Base/CollisionBase.h"

std::vector<SPtr<ObjectBase>> ObjectBase::m_oList;

// �S�Ă̕`����s��
void ObjectBase::AllUpdate()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		m_oList[ec]->Update();
	}
}

// �S�Ă̕`����s��
void ObjectBase::AllDraw()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		//���b�V�����Ԃ񃋁[�v
		for (UINT i = 0; i < m_oList[ec]->GetModel()->GetModelTbl().size(); i++) {
			//YsSingleModel���烁�b�V�����擾
			SPtr<YsSingleModel> model = m_oList[ec]->GetModel()->GetModelTbl()[i];
			SPtr<YsMesh> mesh = model->GetMesh();

			//������ŕ`�攻��
			if (CheckViewFrustum(m_oList[ec], mesh)) {
				m_oList[ec]->Draw();
			}
		}
	}
}

void ObjectBase::FullClear()
{
	m_oList.clear();
}

// �L���t���O�𒲂ׂė����Ă����烊�X�g�������
void ObjectBase::CheckKillFlg()
{
	std::vector<SPtr<ObjectBase>>::iterator it = m_oList.begin();
	while (it != m_oList.end())
	{
		if ((*it)->GetKillFlg() == 1)
		{
			*it = NULL;
			it = m_oList.erase(it);
		}
		else{
			it++;
		}
	}
}

//�I�u�W�F�N�g����Ԃ�
SPtr<ObjectBase> ObjectBase::GetThisObject(int _Num, int _id)
{
	//�I�u�W�F�N�g�̌�����
	for (UINT ec = 0; ec < m_oList.size(); ec++){

		//�w�肳��ĂȂ��ꍇ
		if (_id == OBJECT_LIST::ID::FREE) {
			//�w��̃I�u�W�F�N�g�o�^�ԍ�
			if (m_oList[ec]->GetNum() == _Num)
			{
				return m_oList[ec];
			}
		}
		//�w�肪����ꍇ
		else {
			//�w��̃I�u�W�F�N�gID
			if (m_oList[ec]->GetObjId() == _id) {
				//�w��̃I�u�W�F�N�g�o�^�ԍ�
				if (m_oList[ec]->GetNum() == _Num)
				{
					return m_oList[ec];
				}

			}
		}

	}

	return nullptr;

}