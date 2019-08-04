#include "pch.h"
#include "CppUnitTest.h"
#include "MLGuid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	namespace Util
	{
		TEST_CLASS(MLCoreGuidTest)
		{
		public:

			TEST_METHOD(InitializeNewGuid)
			{
				MLGuid guid = {};
				Assert::AreEqual(static_cast<int>(guid.GetG()), 0);
				Assert::AreEqual(static_cast<int>(guid.GetU()), 0);
				Assert::AreEqual(static_cast<int>(guid.GetI()), 0);
				Assert::AreEqual(static_cast<int>(guid.GetD()), 0);
				Assert::IsTrue(guid.IsNull());
				guid = MLGuid::NewMLGuid();
				Assert::AreNotEqual(static_cast<int>(guid.GetG()), 0);
				Assert::AreNotEqual(static_cast<int>(guid.GetU()), 0);
				Assert::AreNotEqual(static_cast<int>(guid.GetI()), 0);
				Assert::AreNotEqual(static_cast<int>(guid.GetD()), 0);
				Assert::IsFalse(guid.IsNull());
			}
			TEST_METHOD(OperatorOverload)
			{
				const MLGuid guid = MLGuid::NewMLGuid();
				const MLGuid sameGuid = MLGuid{ guid };
				const MLGuid secGuid = MLGuid::NewMLGuid();
				Assert::IsTrue(guid == sameGuid);
				Assert::IsFalse(guid != sameGuid);
				Assert::IsTrue(guid != secGuid);
				Assert::IsFalse(guid == secGuid);
				Assert::IsTrue(guid.GetCombinedNum() == sameGuid.GetCombinedNum());
				Assert::IsFalse(guid.GetCombinedNum() != sameGuid.GetCombinedNum());
				Assert::IsTrue(guid.GetCombinedNum() != secGuid.GetCombinedNum());
				Assert::IsFalse(guid.GetCombinedNum() == secGuid.GetCombinedNum());
			}
		};
	}
}
