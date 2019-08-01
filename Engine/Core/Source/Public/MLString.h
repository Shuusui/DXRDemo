#pragma once
#pragma region Includes
#include "MLArray.h"
#include "MLDefines.h"
#pragma endregion //Includes


namespace Core
{
	namespace Util
	{
		/**
		* Basic MLString implementation
		*/
		class MLString
		{
		public: 
			/**
			* Default constructor
			*/
			MLString() = default;
			/**
			 * Initializer list constructor which will initialize the string with a char initializer list
			 */
			MLString(const std::initializer_list<char>& initializerList)
				:m_string(initializerList)
			{
				if(!this->EndsWith(NULL_TERMINATOR))
				{
					m_string.Add(NULL_TERMINATOR);
				}
			}
			MLString(const char* inString)
				:m_string(ConvertConstCharPtrToCharArray(inString))
			{
			}
			uint32_t Len() const
			{
				return m_string.Num()-1;
			}
			void Append(const char* inString)
			{
				m_string += ConvertConstCharPtrToCharArray(inString);
			}
			const char* operator *() const
			{
				return m_string.GetData();
			}
			bool EndsWith(const char& inChar) const
			{
				return (m_string[m_string.Num()] == inChar);
			}
			/**
			* Default destructor
			*/
			~MLString() = default;
		private:
			static MLArray<char> ConvertConstCharPtrToCharArray(const char* inString)
			{
				MLArray<char> outArray = {};
				for(size_t i = 0; i < strlen(inString); i++)
				{
					outArray.Add(inString[i]);
				}
				outArray.Add(NULL_TERMINATOR);
				return outArray;
			}
			MLArray<char> m_string;
		};
	}
}