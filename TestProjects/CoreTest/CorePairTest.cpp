#include "pch.h"
#include "CppUnitTest.h"
#include "MLPair.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	namespace Util
	{
		TEST_CLASS(MLCorePairTest)
		{
		public:

			TEST_METHOD(InitializePair)
			{
				MLPair<int, int> pair = {};
				pair = MLPair<int, int>{ 1,2 };
				const MLPair<int, int> secPair = MLPair<int, int>{ 5,3 };
				pair = secPair;
			}
		};
	}
}
