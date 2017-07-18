#ifndef __THREADPOOL_H
#define __THREADPOLL_H

#include <vector>
#include <string>
#include <pthread.h>

using namespace std;

class ThreadTask{
	protected:
		string m_strName;
		void *m_ptrData;
	public:
		ThreadTask(){}
		ThreadTask(string taskName){
			m_strName = taskName;
			m_ptrData = NULL;
		}
		void setData(void* data);
		virtual int Run()=0;
		virtual ~ThreadTask(){}
};

class ThreadPool{
	private:
		static vector<ThreadTask*> m_vecTaskList;
		static bool isOver;
		int m_iThreadCount;
		pthread_t *pthread_id;
		static pthread_mutex_t m_pthreadMutex;
		static pthread_cond_t m_pthreadCond;

	protected:
		static void* runThreadPool(void *threadData);
		static int ToIdle(pthread_t tid);
		static int ToBusy(pthread_t tid);
		int createThreadPool;

	public:
		ThreadPool(int threadNum = 10);
		int AddTTask(ThreadTask* task);
		int stopThreadPool();
		int getThreadTaskCount();

};

#endif
