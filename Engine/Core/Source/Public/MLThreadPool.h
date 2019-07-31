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
		class MLThreadPool
		{
		public: 
			static void Create();
			static MLThreadPool* GetHandle();
			static void Destroy();
			static void AddMLJob(class MLJob* job);
			static void Wait();
			~MLThreadPool();
			void operator=(const MLThreadPool&) = delete;
			MLThreadPool(const MLThreadPool&) = delete;
		private: 
			MLThreadPool();
			std::vector<std::thread> m_threads;
			std::queue<class MLJob*> m_jobs;
			static MLThreadPool* s_MLThreadPool;
			void DoMLJob();
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
