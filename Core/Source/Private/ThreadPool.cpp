#include "../Public/ThreadPool.h"
#include "../Public/Job.h"

Core::Util::ThreadPool* Core::Util::ThreadPool::s_threadPool = nullptr;

void Core::Util::ThreadPool::Create()
{
	if (!s_threadPool)
	{
		s_threadPool = new ThreadPool();
	}
}

Core::Util::ThreadPool* Core::Util::ThreadPool::GetHandle()
{
	return s_threadPool;
}

void Core::Util::ThreadPool::Destroy()
{
	s_threadPool->~ThreadPool();
}

void Core::Util::ThreadPool::AddJob(Job* job)
{
	s_threadPool->m_mutex.lock();
	s_threadPool->m_jobs.push(job);
	s_threadPool->m_numOfWork++;
	s_threadPool->m_mutex.unlock();
}

void Core::Util::ThreadPool::Wait()
{
	while (s_threadPool->m_numOfWork.load() > 0)
	{
		std::this_thread::yield();
	}
}

Core::Util::ThreadPool::~ThreadPool()
{
	Abort();
	delete s_threadPool;
	s_threadPool = nullptr;
}

Core::Util::ThreadPool::ThreadPool()
	:m_numOfThreads(std::thread::hardware_concurrency())
	,m_bIsRunning(true)
{
	m_threads.reserve(m_numOfThreads);
	for (size_t i = 0; i < std::thread::hardware_concurrency(); i++)
	{

	}
}

void Core::Util::ThreadPool::DoJob()
{
	std::unique_lock<std::mutex> ul(m_mutex);
	while (m_bIsRunning)
	{
		if (!m_jobs.empty())
		{
			CUtil::Job* job = m_jobs.front();
			m_jobs.pop();
			ul.unlock();
			job->Work();
			ul.lock();
			m_numOfWork--;
			continue;
		}
		m_mutex.unlock();
		std::this_thread::yield();
	}
}

void Core::Util::ThreadPool::Abort()
{
	m_signal.notify_all();
	
}

void Core::Util::ThreadPool::JoinAll()
{
	for (std::thread& thread : m_threads)
	{
		thread.join();
	}
}
