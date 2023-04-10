#include "pch.h"
#include "CppUnitTest.h"
#include "../Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest93
{
	TEST_CLASS(UnitTest93)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int N = 3;
			Route p[N] = { {"a", "b", 3}, {"b", "c", 2}, {"c", "a", 1}};

			Route expectedSorted[N] = { {"c", "a", 1}, {"b", "c", 2}, {"a", "b", 3}};

			Sort(p, N);

			for (int i = 0; i < N; i++)
			{
				Assert::IsTrue(p[i].startPoint == expectedSorted[i].startPoint &&
					p[i].endPoint == expectedSorted[i].endPoint &&
					p[i].numberOfRoute == expectedSorted[i].numberOfRoute);
			}
		}
	};
}
