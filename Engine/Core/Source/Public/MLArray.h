#pragma once
#pragma region Includes
#include <vector>
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		/**
		* Basic MLArray implementation
		*/
		template <typename T>
		class MLArray
		{
		public:
			/**
			 * default Constructor which will initialize everything with default
			 */
			MLArray() = default;
			/**
			 * constructor with initializer list which will initialize the array with an initializer list
			 * @param inInitializerList The list which will initialize the array
			 */
			explicit MLArray(const std::initializer_list<T>& inInitializerList)
				:m_container(inInitializerList)
			{
				
			}
			/**
			 * Function to add an element at the end of the array
			 */
			void Add(const T& inNewElement)
			{
				m_container.push_back(inNewElement);
			}
			/**
			 * Removes the element at the desired position
			 * @param inIndex Desired position of the element
			 */
			void RemoveAt(const int32_t& inIndex)
			{
				m_container.erase(inIndex);
			}
			/**
			 * Removes all elements with the incoming value
			 * @param inRemovableElement The value to remove from the container
			 */
			void RemoveAll(const T& inRemovableElement) 
			{
				std::remove(m_container[0], m_container[m_container.size()], inRemovableElement);
			}
			/**
			 * Returns the current size of the container
			 * @return The size of the container in int32_t
			 */
			int32_t Num() const
			{
				return m_container.size();
			}

		private: 
			std::vector<T> m_container;
		};
		
	}
}