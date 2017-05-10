//===============================================
//
// �^�X�N�֘A
//
//===============================================
#ifndef __TaskManager_h__
#define __TaskManager_h__

class BaseTask;

//===================================================================
//
// �^�X�N�Ǘ��N���X
//  �^�X�N�����X�g�ŊǗ����A�e�^�X�N�̊֐������s�A�폜�Ȃǂ��Ǘ�����
//	�^�X�N�ւ̒ǉ��́AAddTask�֐��ACreateTask�֐��ōs�����ƁB
//
//===================================================================
class TaskManager{
public:
	// �^�X�N���X�g�擾
	std::list< SPtr<BaseTask> >&		GetList(){return m_List;}

	//======================================================================
	// �S�^�X�N��Run�֐������s
	//  �폜�t���O��ON�ɂȂ��Ă�^�X�N������΁A�^�X�N���X�g����폜�B
	//======================================================================
	int UpdateTask();

	//======================================================================
	// �S�^�X�N��Draw�֐������s
	//======================================================================
	void DrawTask();

	//======================================================================
	// �w�胁���o�֐����s(�߂�lvoid �����Ȃ�����)
	// ��Debug�r���h����dynamic_cast���g���Č^�������Ƀ`�F�b�N���Ă��邽�߃p�t�H�[�}���X�͂悭�Ȃ��ł����A�o�O����u������}�V�Ȃ̂ŉ䖝���ĂˁB
	//  pFunc:���s�����������o�֐��|�C���^(��: &BaseTask::Draw)
	//======================================================================
	template<typename T>
	void ExecTask( void (T::*pFunc)() ){
		auto it = m_List.begin();
		while(it != m_List.end()){
#ifdef _DEBUG
			// �_�E���L���X�g�Ŏw��^���ǂ����`�F�b�N
			T* test = dynamic_cast<T*>((*it).get());
			if(test == nullptr){
				_ASSERT(test == nullptr &&  "�_�E���L���X�g���s�I(TaskManager�N���X��ExecTask�֐�)");
			}
#endif
			T* p = static_cast<T*>((*it).get());
			// �w��֐����s
			(p->*pFunc)();

			// ����
			++it;
		}
	}

	//======================================================================
	// ���
	//======================================================================
	void Release(){
		// ���X�g�폜
		m_List.clear();
	}


	//=============================================================
	// �w��^�X�N�����X�g�ɒǉ�
	//=============================================================
	void AddTask(SPtr<BaseTask> task);

	//=============================================================
	// �w��^�X�N�����X�g����O��
	//=============================================================
	void RemoveTask(SPtr<BaseTask> task);

	//=============================================================
	// �^�X�N�쐬���ǉ��֐�
	//=============================================================
	// �^�X�N�쐬(make_shared()��AddTask()���Ă�ł邾��)
	template<class T>
	SPtr<T> CreateTask(){
		// �C���X�^���X�쐬
		SPtr<T> add = std::make_shared<T>();
		AddTask(add);

		return add;
	}

	//=============================================================
	// �w�肵���^�ƈ�v(�h���N���X��OK)����^�̃^�X�N���������A���ׂĕԂ�
	// ��dynamic_cast���g�p���Ă�̂Ŕ�����ł��@�p�t�H�[�}���X���グ�����ꍇ�͂��낢��H�v���Ă�
	//=============================================================
	template<typename T>
	std::vector<SPtr<T>> GetTasks(){
		std::vector<SPtr<T>> found;
		for(auto task : m_List){
			// �^�ϊ��ł��邩���ׂ�
			SPtr<T> ret = SPtr_dynamic_cast<T>(task);
			if(ret){	// ��v�����I
				found.push_back(ret);
			}
		}
		return std::move(found);	// C++11�ł́Avector�̓��[�u�ō���return�ł��܂�
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
	// �^�X�N���X�g
	//======================================================================
	std::list< SPtr<BaseTask> >		m_List;


// TaskManager���̂�shared_ptr�ŗp�ӂ���Ă��Ȃ��Ă��Aweak_ptr�Ŕj�����肪�ł���悤�ɍH�v��������
public:
	struct SP{
		SP(TaskManager& taskmgr) : m_refMgr(taskmgr){}
		TaskManager& m_refMgr;
	};
private:
	SPtr<SP>	_sp;
};


//===============================================
// �^�X�N�p��{�N���X
//  std::enable_shared_from_this���p�����邱�ƂŁA���|�C���^����shared_ptr�֕ϊ��\�ɂȂ�(�����������L��)
//===============================================
class BaseTask : public std::enable_shared_from_this<BaseTask> {
	friend class TaskManager;
public:

	// �^�X�N�폜�w���B�폜�t���O��ON�ɂ���B
	void	TaskDelete(){ m_TaskDeleteFlag = 1; }

	// �폜�t���O�������Ă��邩�H
	int		TaskIsDelete(){ return m_TaskDeleteFlag; }

	// �����̏������Ă���TaskManager�ւ̃A�h���X��Ԃ�
	TaskManager* TaskGetOwnerMgr(){
		if(m_pOwnerTaskMgr.expired())return nullptr;
		return &m_pOwnerTaskMgr._Get()->m_refMgr;
	}

	// �����̏������Ă���TaskManager�����������
	void TaskRemoveFromMgr(){
		TaskManager* mgr = TaskGetOwnerMgr();
		if(mgr){
			mgr->RemoveTask(YsToSPtr(this));
		}
	}

	// �e�����֐�
	virtual void Update(){}			// �����֐�
	virtual void Draw(){}						// �`��֐�

	// �^�X�N���擾
	virtual std::string TaskGetName(){ return "No Name"; }

	// 
	BaseTask(){
	}

	// 
	virtual ~BaseTask(){}


private:
	// �폜�t���O
	int				m_TaskDeleteFlag = 0;

	// �����̏������Ă���TaskManager�@���m�ɂ�TaskManager�̃����o�ϐ��ł���_sp(shared_ptr�^)��weak_ptr�������Ă���
	WPtr<TaskManager::SP>	m_pOwnerTaskMgr;
	//	TaskManager*	m_pOwnerTaskMgr = nullptr;	�� ���|�C���^���ƁA�{�̂�TaskManager���������Ƃ��}�Y������񐄏�
};


#endif
