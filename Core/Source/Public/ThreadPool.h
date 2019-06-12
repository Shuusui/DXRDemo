#pragma once
#pragma region Includes
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <atomic>
#pragma endregion //Includes


namespace Core
{
	namespace Util
	{
		class ThreadPool
		{
		public: 
			static void Create();
			static ThreadPool* GetHandle();
			static void Destroy();
			static void AddJob(class Job* job);
			static void Wait();
			~ThreadPool();
			void operator=(const ThreadPool&) = delete;
			ThreadPool(const ThreadPool&) = delete;
		private: 
			ThreadPool();
			std::vector<std::thread> m_threads;
			std::queue<class Job*> m_jobs;
			static ThreadPool* s_threadPool;
			void DoJob();
			void Abort();
			std::mutex m_mutex;
			std::atomic<size_t> m_numOfThreads;
			std::atomic<size_t> m_numOfWork;
			bool m_bIsRunning;
			std::condition_variable m_signal;
			void JoinAll();
		};
	}
}

namespace CUtil = Core::Util;
