#pragma once
#pragma region Includes
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		class MLJob
		{
		public:
			MLJob() = default; 
			virtual void Work() = 0;
			~MLJob() = default;
		};
	}
}