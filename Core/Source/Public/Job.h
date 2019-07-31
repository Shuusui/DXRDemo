#pragma once
#pragma region Includes
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		class Job
		{
		public:
			Job() = default; 
			virtual void Work() = 0;
			~Job() = default;
		private:
		};
	}
}