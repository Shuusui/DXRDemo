#include "../Public/MLThreadPool.h"
#include "../Public/MLJob.h"

Core::Util::MLThreadPool* Core::Util::MLThreadPool::s_MLThreadPool = nullptr;

void Core::Util::MLThreadPool::Create()
{
	if (!s_MLThreadPool)
	{
		s_MLThreadPool = new MLThreadPool();
	}
}

Core::Util::MLThreadPool* Core::Util::MLThreadPool::GetHandle()
{
	return s_MLThreadPool;
}

void Core::Util::MLThreadPool::Destroy()
{
	s_MLThreadPool->~MLThreadPool();
}

void Core::Util::MLThreadPool::AddMLJob(MLJob* job)
{
	s_MLThreadPool->m_mutex.lock();
	s_MLThreadPool->m_jobs.push(job);
	s_MLThreadPool->m_numOfWork++;
	s_MLThreadPool->m_mutex.unlock();
}

void Core::Util::MLThreadPool::Wait()
{
	while (s_MLThreadPool->m_numOfWork.load() > 0)
	{
		std::this_thread::yield();
	}
}

Core::Util::MLThreadPool::~MLThreadPool()
{
	Abort();
	delete s_MLThreadPool;
	s_MLThreadPool = nullptr;
}

Core::Util::MLThreadPool::MLThreadPool()
	:m_numOfThreads(std::thread::hardware_concurrency())
	,m_bIsRunning(true)
{
	m_threads.reserve(m_numOfThreads);
	for (size_t i = 0; i < std::thread::hardware_concurrency(); i++)
	{

	}
}

void Core::Util::MLThreadPool::DoMLJob()
{
	std::unique_lock<std::mutex> ul(m_mutex);
	while (m_bIsRunning)
	{
		if (!m_jobs.empty())
		{
			CUtil::MLJob* MLJob = m_jobs.front();
			m_jobs.pop();
			ul.unlock();
			MLJob->Work();
			ul.lock();
			m_numOfWork--;
			continue;
		}
		m_mutex.unlock();
		std::this_thread::yield();
	}
}

void Core::Util::MLThreadPool::Abort()
{
	m_signal.notify_all();
	
}

void Core::Util::MLThreadPool::JoinAll()
{
	for (std::thread& thread : m_threads)
	{
		thread.join();
	}
}
