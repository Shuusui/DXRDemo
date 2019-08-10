#include "pch.h"
#include "CppUnitTest.h"
#include "MLString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	namespace Util
	{
		TEST_CLASS(MLCoreStringTest)
		{
		public:

			TEST_METHOD(InitializeString)
			{
				MLString string = MLString("cs");
				Assert::AreEqual(static_cast<int>(string.Len()), 2);
				string.Append("go");
				Assert::AreEqual(static_cast<int>(string.Len()), 4);
				const char* buffer = *string;
				Assert::AreEqual(buffer, "csgo");
			}
		};
	}
}
