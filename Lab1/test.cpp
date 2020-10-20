#include "pch.h"
#include "HashTable.h"
#include <vld.h>

TEST(TestCaseName, ConstrDefault) {
	HashTable A;
	EXPECT_EQ(A.size(), 8);
}

TEST(TestCaseName, InsertAndOperAndAt)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	EXPECT_EQ(A["Bill"].age, 19);
	EXPECT_EQ(A.at("Bill").weight, 83);
}

TEST(TestCaseName, ConstrParam)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	A.insert("John", { 20, 70 });
	HashTable B(A);
	EXPECT_EQ(B["Bill"].age, 19);
	EXPECT_EQ(B["Bill"].weight, 83);
	EXPECT_EQ(B["John"].age, 20);
	EXPECT_EQ(B["John"].weight, 70);
}

TEST(TestCaseName, ConstrParamAndChanged)
{
	HashTable A;
	A.insert("Bill", { 19, 83 });
	HashTable B(A);
	B["Bill"].age = 20;
	EXPECT_EQ(A["Bill"].age, 19);
	EXPECT_EQ(B["Bill"].age, 20);
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
	EXPECT_EQ(A.at("Bill").age, 24);
}

TEST(TestCaseName, ConstAt)
{
	HashTable A;
	A.insert("John", { 19, 76 });
	const HashTable B = A;
	EXPECT_EQ(B.at("John").weight, 76);
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
	EXPECT_TRUE(B.contains("Bill"));
	EXPECT_TRUE(B.contains("John"));
	EXPECT_TRUE(B.contains("Ann"));
	EXPECT_TRUE(A.contains("Andrew"));
	EXPECT_TRUE(A.contains("Finn"));
}

TEST(TestCaseName, Erase)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	A.insert("Ann", { 18, 69 });
	A.erase("Bill");
	EXPECT_TRUE(A.contains("John"));
	EXPECT_TRUE(A.contains("Ann"));
	EXPECT_TRUE(!A.contains("Bill"));
}

TEST(TestCaseName, EraseNothing)
{
	HashTable A;
	EXPECT_TRUE(!A.erase("Bill"));
}

TEST(TestCaseName, Empty)
{
	HashTable A;
	A.insert("John", { 18, 70 });
	A.insert("Bill", { 20, 75 });
	HashTable B;
	EXPECT_TRUE(B.empty());
	EXPECT_TRUE(!A.empty());
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
	EXPECT_EQ(A.size(), 16);
	EXPECT_TRUE(A.contains("John"));
	EXPECT_TRUE(A.contains("Bill"));
	EXPECT_TRUE(A.contains("Wendy"));
	EXPECT_TRUE(A.contains("Dean"));
	EXPECT_TRUE(A.contains("Alastor"));
	EXPECT_TRUE(A.contains("Freddy"));
	EXPECT_TRUE(A.contains("Harry"));
	EXPECT_TRUE(A.contains("Alukard"));
	EXPECT_TRUE(A.contains("Aden"));
	EXPECT_TRUE(A.contains("Shrek"));
	EXPECT_TRUE(A.contains("Hayns"));
	EXPECT_TRUE(A.contains("Dendy"));
}

TEST(TestCaseName, CopyBigTable)
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
	HashTable B = A;
	EXPECT_TRUE(B.contains("John"));
	EXPECT_TRUE(B.contains("Bill"));
	EXPECT_TRUE(B.contains("Wendy"));
	EXPECT_TRUE(B.contains("Dean"));
	EXPECT_TRUE(B.contains("Alastor"));
	EXPECT_TRUE(B.contains("Freddy"));
	EXPECT_TRUE(B.contains("Harry"));
	EXPECT_TRUE(B.contains("Alukard"));
	EXPECT_TRUE(B.contains("Aden"));
	EXPECT_TRUE(B.contains("Shrek"));
	EXPECT_TRUE(B.contains("Hayns"));
	EXPECT_TRUE(B.contains("Dendy"));
	EXPECT_TRUE(A == B);
}

TEST(TestCaseName, CompareBigTables)
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
	HashTable B;
	B.insert("John", { 18, 70 });
	B.insert("Bill", { 19, 75 });
	B.insert("Wendy", { 19, 80 });
	B.insert("Dean", { 20, 81 });
	B.insert("Alastor", { 19, 82 });
	B.insert("Freddy", { 18, 83 });
	B.insert("Harry", { 21, 76 });
	B.insert("Alukard", { 26, 90 });
	B.insert("Aden", { 20, 81 });
	B.insert("Shrek", { 19, 78 });
	B.insert("Hayns", { 19, 80 });
	B.insert("Dendy", { 21, 76 });
	EXPECT_TRUE(A == B);
}

TEST(TestCaseName, EraseChain)
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
	A.erase("Dendy");
	A.erase("Hayns");
	A.erase("Shrek");
	A.erase("Aden");
	A.erase("Alukard");
	A.erase("Harry");
	A.erase("Freddy");
	A.erase("Alastor");
	A.erase("Dean");
	A.erase("Wendy");
	A.erase("Bill");
	A.erase("John");
	EXPECT_EQ(A.size(), 16);
	EXPECT_TRUE(A.empty());
}

TEST(TestCaseName, GetAmongMany)
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
	EXPECT_EQ(A.at("Dendy").weight, 76);
}

TEST(TestCaseName, GetConstAmongMany)
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
	const HashTable B = A;
	EXPECT_EQ(B.at("Dendy").weight, 76);
	EXPECT_EQ(B.size(), 16);
}

TEST(TestCaseName, Exception)
{
	HashTable A;
	EXPECT_ANY_THROW(A.at("Anybody"));
}

TEST(TestCaseName, ExceptionConst)
{
	const HashTable A;
	EXPECT_ANY_THROW(A.at("Anybody"));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	int j, i = RUN_ALL_TESTS();
	return i;
}
