#include "pch.h"
#include "LAB_A26.h"
#define  _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

TEST(dateComparison, Test1) {
	char date_1[] = "2020-11-6";
	char date_2[] = "2020-11-15";
	EXPECT_EQ(1, dateComparison(date_1,date_2));
}

TEST(listInitialization, addFirstElement) {
	list* head = NULL;
	head = listInitialization("2010-6-15", 10);
	EXPECT_EQ(head->temp, 10);
	EXPECT_STREQ(head->date, "2010-6-15");
	free(head);
}

TEST(push, addNewElement) {
	list* head = NULL;
	head = push(head, "2018-9-11", 15);
	head = push(head, "2001-12-3", 20);
	EXPECT_EQ(head->temp, 15);
	EXPECT_STREQ(head->date, "2018-9-11");
	head = head->ptr;
	EXPECT_EQ(head->temp, 20);
	EXPECT_STREQ(head->date, "2001-12-3");
	deleteList(head);
}

TEST(push,sortByDTemperature) {
	list* head = NULL;
	head = push(head, "2018-9-11", 15);
	head = push(head, "2002-9-2", -10);
	head = push(head, "2003-9-1", 25);
	EXPECT_TRUE(head->temp < head->ptr->temp);
	head = head->ptr;
	EXPECT_TRUE(head->temp < head->ptr->temp);
	deleteList(head);
}

TEST(push, sortByDate) {
	list* head = NULL;
	head = push(head, "2018-10-11", -20);
	head = push(head, "2003-9-2", -20);
	head = push(head, "2003-9-1", -20);
	EXPECT_STREQ(head->date, "2003-9-1");
	EXPECT_STREQ(head->ptr->date, "2003-9-2");
	EXPECT_STREQ(head->ptr->ptr->date, "2018-10-11");
	deleteList(head);
}


TEST(weatherBelowZero, findDaysWWeatherBelowZero) {
	list list_1, list_2, list_3;
	list_1 = { "2003-1-4", -15 };
	list_2 = { "2004-5-6", -10 };
	list_3 = { "2014-3-11", 10 };
	list_2.ptr = &list_3;
	list_1.ptr = &list_2;
	EXPECT_EQ(weatherBelowZero(&list_1), 2);
}

TEST(weatherBelowZero, notDaysWWeatherBelowZero) {
	list list_1, list_2, list_3;
	list_1 = { "2003-1-4", 10 };
	list_2 = { "2004-5-6", 15 };
	list_1.ptr = &list_2;
	EXPECT_EQ(weatherBelowZero(&list_1), 0);
}

TEST(readFile, notExistingFile) {
	char file[] = "C:\\Users\\trony\\Desktop\\LAB1_Tronyagina_A26\\test_nonexist.txt";
	list* head = readFile(file);
	EXPECT_TRUE(head == NULL);
	free(head);
}

TEST(readFile, emptyFile) {
	char file[] = "C:\\Users\\trony\\Desktop\\LAB1_Tronyagina_A26\\test_empty.txt";
	list* head = readFile(file);
	EXPECT_TRUE(head == NULL);
	free(head);
}

TEST(readFile, normalFileFor3Elements) {
	char file[] = "C:\\Users\\trony\\Desktop\\LAB1_Tronyagina_A26\\test.txt";
	list* head = readFile(file);
	EXPECT_FALSE(head == NULL);
	EXPECT_EQ(head->temp, -10);
	EXPECT_STREQ(head->date, "2020-12-1");
	head = head->ptr;
	EXPECT_FALSE(head == NULL);
	EXPECT_EQ(head->temp, 0);
	EXPECT_STREQ(head->date, "2020-3-4");
	head = head->ptr;
	EXPECT_FALSE(head == NULL);
	EXPECT_EQ(head->temp,25);
	EXPECT_STREQ(head->date, "2020-6-1");
	deleteList(head);
}

TEST(averageTemperatureSearch, TestName9) {
	list list_1, list_2, list_3;
	list_1 = { "2003-1-4", 0 };
	list_2 = { "2004-5-6", 0 };
	list_3 = { "2014-3-11", 10 };
	list_2.ptr = &list_3;
	list_1.ptr = &list_2;
	EXPECT_EQ(averageTemperatureSearch(&list_1, 0), 2);
}

TEST(averageTemperatureSearch, TestName8) {
	list list_1, list_2, list_3;
	list_1 = { "2003-1-4", -15};
	list_2 = { "2004-5-6", -10};
	list_3 = { "2014-3-11", 10 };
	list_2.ptr = &list_3;
	list_1.ptr = &list_2;
	EXPECT_EQ(averageTemperatureSearch(&list_1, 0), 0);
}


int main(void) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	RUN_ALL_TESTS();
	return 0;
}
