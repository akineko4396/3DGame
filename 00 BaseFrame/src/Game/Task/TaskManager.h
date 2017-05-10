//===============================================
//
// タスク関連
//
//===============================================
#ifndef __TaskManager_h__
#define __TaskManager_h__

class BaseTask;

//===================================================================
//
// タスク管理クラス
//  タスクをリストで管理し、各タスクの関数を実行、削除などを管理する
//	タスクへの追加は、AddTask関数、CreateTask関数で行うこと。
//
//===================================================================
class TaskManager{
public:
	// タスクリスト取得
	std::list< SPtr<BaseTask> >&		GetList(){return m_List;}

	//======================================================================
	// 全タスクのRun関数を実行
	//  削除フラグがONになってるタスクがあれば、タスクリストから削除。
	//======================================================================
	int UpdateTask();

	//======================================================================
	// 全タスクのDraw関数を実行
	//======================================================================
	void DrawTask();

	//======================================================================
	// 指定メンバ関数実行(戻り値void 引数なし限定)
	// ※Debugビルド時はdynamic_castを使って型を厳密にチェックしているためパフォーマンスはよくないですが、バグを放置するよりマシなので我慢してね。
	//  pFunc:実行したいメンバ関数ポインタ(例: &BaseTask::Draw)
	//======================================================================
	template<typename T>
	void ExecTask( void (T::*pFunc)() ){
		auto it = m_List.begin();
		while(it != m_List.end()){
#ifdef _DEBUG
			// ダウンキャストで指定型かどうかチェック
			T* test = dynamic_cast<T*>((*it).get());
			if(test == nullptr){
				_ASSERT(test == nullptr &&  "ダウンキャスト失敗！(TaskManagerクラスのExecTask関数)");
			}
#endif
			T* p = static_cast<T*>((*it).get());
			// 指定関数実行
			(p->*pFunc)();

			// 次へ
			++it;
		}
	}

	//======================================================================
	// 解放
	//======================================================================
	void Release(){
		// リスト削除
		m_List.clear();
	}


	//=============================================================
	// 指定タスクをリストに追加
	//=============================================================
	void AddTask(SPtr<BaseTask> task);

	//=============================================================
	// 指定タスクをリストから外す
	//=============================================================
	void RemoveTask(SPtr<BaseTask> task);

	//=============================================================
	// タスク作成＆追加関数
	//=============================================================
	// タスク作成(make_shared()とAddTask()を呼んでるだけ)
	template<class T>
	SPtr<T> CreateTask(){
		// インスタンス作成
		SPtr<T> add = std::make_shared<T>();
		AddTask(add);

		return add;
	}

	//=============================================================
	// 指定した型と一致(派生クラスもOK)する型のタスクを検索し、すべて返す
	// ※dynamic_castを使用してるので非効率です　パフォーマンスを上げたい場合はいろいろ工夫してね
	//=============================================================
	template<typename T>
	std::vector<SPtr<T>> GetTasks(){
		std::vector<SPtr<T>> found;
		for(auto task : m_List){
			// 型変換できるか調べる
			SPtr<T> ret = SPtr_dynamic_cast<T>(task);
			if(ret){	// 一致した！
				found.push_back(ret);
			}
		}
		return std::move(found);	// C++11では、vectorはムーブで高速returnできます
	}

	// 
	TaskManager(){
		_sp = std::make_shared<SP>(*this);
	}

	// 
	virtual ~TaskManager()
	{
		Release();
	}


protected:
	//======================================================================
	// タスクリスト
	//======================================================================
	std::list< SPtr<BaseTask> >		m_List;


// TaskManager自体がshared_ptrで用意されていなくても、weak_ptrで破棄判定ができるように工夫したもの
public:
	struct SP{
		SP(TaskManager& taskmgr) : m_refMgr(taskmgr){}
		TaskManager& m_refMgr;
	};
private:
	SPtr<SP>	_sp;
};


//===============================================
// タスク用基本クラス
//  std::enable_shared_from_thisを継承することで、生ポインタからshared_ptrへ変換可能になる(ただし条件有り)
//===============================================
class BaseTask : public std::enable_shared_from_this<BaseTask> {
	friend class TaskManager;
public:

	// タスク削除指示。削除フラグをONにする。
	void	TaskDelete(){ m_TaskDeleteFlag = 1; }

	// 削除フラグが立っているか？
	int		TaskIsDelete(){ return m_TaskDeleteFlag; }

	// 自分の所属しているTaskManagerへのアドレスを返す
	TaskManager* TaskGetOwnerMgr(){
		if(m_pOwnerTaskMgr.expired())return nullptr;
		return &m_pOwnerTaskMgr._Get()->m_refMgr;
	}

	// 自分の所属しているTaskManagerから解除する
	void TaskRemoveFromMgr(){
		TaskManager* mgr = TaskGetOwnerMgr();
		if(mgr){
			mgr->RemoveTask(YsToSPtr(this));
		}
	}

	// 各処理関数
	virtual void Update(){}			// 処理関数
	virtual void Draw(){}						// 描画関数

	// タスク名取得
	virtual std::string TaskGetName(){ return "No Name"; }

	// 
	BaseTask(){
	}

	// 
	virtual ~BaseTask(){}


private:
	// 削除フラグ
	int				m_TaskDeleteFlag = 0;

	// 自分の所属しているTaskManager　正確にはTaskManagerのメンバ変数である_sp(shared_ptr型)のweak_ptrを憶えておく
	WPtr<TaskManager::SP>	m_pOwnerTaskMgr;
	//	TaskManager*	m_pOwnerTaskMgr = nullptr;	← 生ポインタだと、本体のTaskManagerが消えたときマズいから非推奨
};


#endif
