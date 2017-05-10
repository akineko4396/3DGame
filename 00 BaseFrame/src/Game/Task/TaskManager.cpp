#include "main.h"
#include "TaskManager.h"

//======================================================================
// �S�^�X�N��Run�֐������s
//  �폜�t���O��ON�ɂȂ��Ă�^�X�N������΁A�^�X�N���X�g����폜�B
//======================================================================
int TaskManager::UpdateTask()
{
	if(m_List.empty())return 0;

	// �������s
	auto it = m_List.begin();
	while(it != m_List.end()){

		if((*it)->TaskIsDelete() == 0){		// �폜�t���O��OFF�̎�
			// �������s
			(*it)->Update();

			++it;
		}
		// �폜�t���O�������Ă�Ƃ��́A�^�X�N���X�g����폜
		else{
			it = m_List.erase(it);	// ���X�g�̃m�[�h���폜���A���ցB(�V�F�A�[�h�|�C���^�̃J�E���g���O�ɂȂ�����A�f�[�^������A�܂�delete�����)
		}
	}

	return 0;
}

//======================================================================
// �S�^�X�N��Draw�֐������s
//======================================================================
void TaskManager::DrawTask()
{
	auto it = m_List.begin();
	while(it != m_List.end()){

		// �`����s
		(*it)->Draw();

		// ����
		++it;
	}
}

//=============================================================
// �w��^�X�N�����X�g�ɒǉ�
//=============================================================
void TaskManager::AddTask(SPtr<BaseTask> task){
	m_List.push_back(task);
	task->m_pOwnerTaskMgr = _sp;
}

//=============================================================
// �w��^�X�N�����X�g����O��
//=============================================================
void TaskManager::RemoveTask(SPtr<BaseTask> task){
	auto it = m_List.begin();
	while(it != m_List.end()){
		if((*it).get() == task.get()){

			task->m_pOwnerTaskMgr.reset();

			// ���X�g�������
			m_List.erase(it);
			return;
		}
		++it;
	}
}
