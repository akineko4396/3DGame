#include "main.h"
#include "TaskManager.h"

//======================================================================
// 全タスクのRun関数を実行
//  削除フラグがONになってるタスクがあれば、タスクリストから削除。
//======================================================================
int TaskManager::UpdateTask()
{
	if(m_List.empty())return 0;

	// 処理実行
	auto it = m_List.begin();
	while(it != m_List.end()){

		if((*it)->TaskIsDelete() == 0){		// 削除フラグがOFFの時
			// 処理実行
			(*it)->Update();

			++it;
		}
		// 削除フラグが立ってるときは、タスクリストから削除
		else{
			it = m_List.erase(it);	// リストのノードを削除し、次へ。(シェアードポインタのカウントが０になったら、データも解放、つまりdeleteされる)
		}
	}

	return 0;
}

//======================================================================
// 全タスクのDraw関数を実行
//======================================================================
void TaskManager::DrawTask()
{
	auto it = m_List.begin();
	while(it != m_List.end()){

		// 描画実行
		(*it)->Draw();

		// 次へ
		++it;
	}
}

//=============================================================
// 指定タスクをリストに追加
//=============================================================
void TaskManager::AddTask(SPtr<BaseTask> task){
	m_List.push_back(task);
	task->m_pOwnerTaskMgr = _sp;
}

//=============================================================
// 指定タスクをリストから外す
//=============================================================
void TaskManager::RemoveTask(SPtr<BaseTask> task){
	auto it = m_List.begin();
	while(it != m_List.end()){
		if((*it).get() == task.get()){

			task->m_pOwnerTaskMgr.reset();

			// リストから解除
			m_List.erase(it);
			return;
		}
		++it;
	}
}
