#include "pch.h"
#include "HashTable.h"
#include <vld.h>

TEST(TestCaseName, ConstrDefault) {
	HashTable A;
  EXPECT_TRUE(A.size() == 8);
}

TEST(TestCaseName, InsertAndOperAndAt)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	EXPECT_TRUE((A["Bill"].age == 19) && (A.at("Bill").weight == 83));
}

TEST(TestCaseName, ConstrParam)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	A.insert("John", { 20, 70 });
	HashTable B(A);
	EXPECT_TRUE((B["Bill"].age == 19) && (B["Bill"].weight == 83) && \
		(B["John"].age == 20) && (B["John"].weight == 70));
}

TEST(TestCaseName, ConstrParamAndChanged)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	HashTable B(A);
	B["Bill"].age = 20;
	EXPECT_TRUE((A["Bill"].age == 19) && (B["Bill"].age == 20));
}

TEST(TestCaseName, OperatorAndContains)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	HashTable B;
	B = A;
	EXPECT_TRUE(B.contains("Bill"));
}

TEST(TestCaseName, Clear)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	A.clear();
	EXPECT_TRUE(!A.contains("Bill"));
}

TEST(TestCaseName, ContainsEmpty)
{
	HashTable A;
	EXPECT_TRUE(!A.contains("Anybody"));
}

TEST(TestCaseName, OperWithEmpty)
{
	HashTable A;
	A["Bill"].age = 24;
	EXPECT_TRUE(A.at("Bill").age == 24);
}

TEST(TestCaseName, ConstAt)
{
	HashTable A;
	A.insert("John", { 19, 76 });
	const int w = A.at("John").weight;
	EXPECT_TRUE(w == 76);
}

TEST(TestCaseName, Swap)
{
	HashTable A, B;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	A.insert("Ann", { 18, 69 });
	B.insert("Andrew", { 20, 83 });
	B.insert("Finn", { 19, 80 });
	A.swap(B);
	EXPECT_TRUE(B.contains("Bill") && B.contains("John") && B.contains("Ann") && \
		A.contains("Andrew") && A.contains("Finn"));
}

TEST(TestCaseName, Erase)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	A.insert("Ann", { 18, 69 });
	A.erase("Bill");
	EXPECT_TRUE(A.contains("John") && A.contains("Ann") && !A.contains("Bill"));
}

TEST(TestCaseName, Empty)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	HashTable B;
	EXPECT_TRUE(B.empty() && !A.empty());
}

TEST(TestCaseName, Equal1)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	HashTable B;
	B.insert("John", { 18, 70 });
	B.insert("Bill", { 20, 75 });
	EXPECT_TRUE(A == B);
}

TEST(TestCaseName, Equal2)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	HashTable B;
	B.insert("James", { 18, 70 });
	B.insert("Bill", { 20, 75 });
	EXPECT_TRUE(!(A == B));
}

TEST(TestCaseName, Equal3)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	HashTable B;
	B.insert("John", { 18, 70 });
	B.insert("Bill", { 21, 76 });
	EXPECT_TRUE(A != B);
}

TEST(TestCaseName, Equal4)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	HashTable B;
	B.insert("John", { 18, 70 });
	B.insert("Bill", { 20, 75 });
	EXPECT_TRUE(!(A != B));
}

TEST(TestCaseName, Equal5)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	HashTable B;
	EXPECT_TRUE(A != B);
}

TEST(TestCaseName, Equal6)
{
	HashTable A;
	HashTable B;
	EXPECT_TRUE(A == B);
}

TEST(TestCaseName, ErrorInsert)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	EXPECT_TRUE(!A.insert("John", { 20, 50 }));
}

TEST(TestCaseName, CountAfterErase)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 19, 75 });
	A.erase("John");
	A.erase("Bill");
	EXPECT_TRUE(A.empty());
}

TEST(TestCaseName, IncreaseTable)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 19, 75 });
	A.insert("Wendy", { 19, 80 });
	A.insert("Dean", { 20, 81 });
	A.insert("Alastor", { 19, 82 });
	A.insert("Freddy", { 18, 83 });
	A.insert("Harry", { 21, 76 });
	A.insert("Alukard", { 26, 90 });
	A.insert("Aden", { 20, 81 });
	A.insert("Shrek", { 19, 78 });
	A.insert("Hayns", { 19, 80 });
	A.insert("Dendy", { 21, 76 });
	EXPECT_TRUE(A.size() == 16);
}

TEST(TestCaseName, Exception)
{
	HashTable A;
	int error = 0;
	try {
		A.at("Anybody");
	}
	catch (int) {
		error = 1;
	}
	EXPECT_TRUE(error == 1);
}

TEST(TestCaseName, ExceptionConst)
{
	HashTable A;
	int error = 0;
	try {
		const Value b = A.at("Anybody");
	}
	catch (int) {
		error = 1;
	}
	EXPECT_TRUE(error == 1);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	int j, i = RUN_ALL_TESTS();
	std::cin >> j;
	return i;
}
