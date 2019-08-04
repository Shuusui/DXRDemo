#include "pch.h"
#include "CppUnitTest.h"
#include "MLArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	namespace Util
	{
		TEST_CLASS(MLCoreArrayTest)
		{
		public:

			TEST_METHOD(ArrayNumTest)
			{
				const MLArray<int> array = MLArray<int>{ 0,2,3 };
				Assert::AreEqual(3, array.Num());
			}
			TEST_METHOD(ArrayAddTest)
			{
				MLArray<int> array = MLArray<int>();
				array.Add(6);
				Assert::AreEqual(1, array.Num());
				Assert::AreEqual(6, array[0]);
				const MLArray<int> secArray = MLArray<int>{ 3,5,7 };
				const MLArray<int> resultArray = array + secArray;
				Assert::AreEqual(4, resultArray.Num());
				Assert::AreEqual(6, resultArray[0]);
				Assert::AreEqual(3, resultArray[1]);
				Assert::AreEqual(5, resultArray[2]);
				Assert::AreEqual(7, resultArray[3]);
			}
			TEST_METHOD(ArrayOperatorOverloadTest)
			{
				MLArray<int> array = MLArray<int>{ 2,3,5 };
				Assert::AreEqual(static_cast<int>(array.Num()), 3);
				Assert::AreEqual(2, array[0]);
				Assert::AreEqual(3, array[1]);
				Assert::AreEqual(5, array[2]);
				MLArray<int> appendingArray = MLArray<int>{ 7,3,6 };
				Assert::AreEqual(7, appendingArray[0]);
				Assert::AreEqual(3, appendingArray[1]);
				Assert::AreEqual(6, appendingArray[2]);
				array += appendingArray;
				Assert::AreEqual(static_cast<int>(array.Num()), 6);
				Assert::AreEqual(7, array[3]);
				Assert::AreEqual(3, array[4]);
				Assert::AreEqual(6, array[5]);
				Assert::IsFalse(array == appendingArray);
				Assert::IsTrue(array != appendingArray);
				const MLArray<int> sameArray = MLArray<int>(array);
				Assert::IsTrue(array == sameArray);
				Assert::IsFalse(array != sameArray);
			}
		};
	}
}
