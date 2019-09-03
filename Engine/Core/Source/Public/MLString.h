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

			explicit MLString(const char* inString)
				:m_string(ConvertConstCharPtrToCharArray(inString))
			{
			}

			MLString SubStr(const uint32_t& inStartPos, const uint32_t& inEndPos)
			{
				if(inStartPos < 0 || inStartPos > Len() ||inEndPos <0 || inEndPos >Len())
				{
					return MLString();
				}
			}

			uint32_t Len() const
			{
				return m_string.Num()-1;
			}

			bool IsEmpty() const
			{
				return m_string.IsEmpty();
			}
			
			void Append(const char* inString)
			{
				DelEnd();
				MLArray<char> string = ConvertConstCharPtrToCharArray(inString);
				m_string += string;
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
			void DelEnd()
			{
				m_string.RemoveAt(m_string.Num()-1);
			}
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