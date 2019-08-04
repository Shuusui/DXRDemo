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
			MLArray(const MLArray<T>& other)
				:m_container(other.m_container)
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
				m_container.erase(m_container.begin()+inIndex);
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
				return static_cast<int32_t>(m_container.size());
			}
			/**
			 * Empties the array
			 */
			void Empty() const
			{
				m_container.clear();
			}
			const T* GetData() const
			{
				return m_container.data();
			}
			/**
			 * operator overload for [] operation
			 */
			T operator[](const int32_t& inIndex) const
			{
				return m_container.at(inIndex);
			}

			T At(const int32_t& inIndex) const
			{
				return m_container.at(inIndex);
			}

			void operator+=(MLArray<T>& other)
			{
				m_container.insert(m_container.end(), std::make_move_iterator(other.m_container.begin()), std::make_move_iterator(other.m_container.end()));
			}

			MLArray<T> operator+(const MLArray<T>& other)
			{
				MLArray<T> tempContainer(*this);
				tempContainer.m_container.insert(tempContainer.m_container.end(), other.m_container.begin(), other.m_container.end());
				return tempContainer;
			}

			bool operator==(const MLArray<T>& other)
			{
				if(this->Num() != other.Num())
				{
					return false;
				}
				for(size_t i = 0; i < this->Num(); i++)
				{
					if(this->At(i) != other.At(i))
					{
						return false;
					}
				}
				return true;
			}

			bool operator!=(const MLArray<T>& other)
			{
				if(this->Num() != other.Num())
				{
					return true;
				}
				size_t count = 0;
				for(size_t i = 0; i < this->Num()-1; i++)
				{
					if(this->At(i) == other.At(i))
					{
						count++;
					}
				}
				return count == this->Num();
			}
		private: 
			std::vector<T> m_container;
		};
		
	}
}