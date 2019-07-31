#include "pch.h"
#include "CppUnitTest.h"
#include "MLArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	namespace Util
	{
		TEST_CLASS(CoreArrayTest)
		{
		public:

			TEST_METHOD(ArrayNumTest)
			{
				const MLArray<int> Array = MLArray<int>{ 0,2,3 };
				Assert::AreEqual(3, Array.Num());
			}
			TEST_METHOD(ArrayAddTest)
			{
				MLArray<int> Array = MLArray<int>();
				Array.Add(6);
				Assert::AreEqual(1, Array.Num());
				Assert::AreEqual(6, Array[0]);
			}
		};
	}
}
