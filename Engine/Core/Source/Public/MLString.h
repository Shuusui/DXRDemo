#pragma once
#pragma region Includes
#include "MLArray.h"
#pragma endregion //Includes


namespace Core
{
	namespace Util
	{
		/**
		* Basic MLString implementation
		*/
		class MLString : public MLArray<char>
		{
		public: 
			/**
			* Default constructor
			*/
			MLString();
			/**
			* Default destructor
			*/
			~MLString();
		private: 

		};
		inline MLString::MLString()
		{

		}
		inline MLString ::~MLString()
		{

		}
	}
}