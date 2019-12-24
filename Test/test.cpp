#include "pch.h"
#include "../Task_4/Metro.h"

TEST(TestCaseName, TestName) {
	Metro::System MosMetro("MosMetro");
	Metro::System MosMetro("MosMetro");
	MosMetro.addLine("Blue");
	MosMetro.addLine("Black");
	MosMetro.addLine("Green");
	try { MosMetro.findLine("Red"); }
	catch (...) { std::cout << "Nope"; }
	Metro::Line buf = MosMetro.findLine("Blue");
	EXPECT_EQ(buf, "Blue");
	MosMetro.addLine("Red");
	buf = MosMetro.findLine("Red");
	EXPECT_EQ(buf, "Black");


	//EXPECT_TRUE(true);
}