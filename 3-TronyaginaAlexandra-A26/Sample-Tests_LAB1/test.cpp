#include "pch.h"
#include "LAB_A26.h"
#define  _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

TEST(dateComparison, comparisonEarlyWLaterDate) {
	char date_1[] = "2020-11-3";
	char date_2[] = "2020-11-16";

	EXPECT_EQ(1, dateComparison(date_1,date_2));
}

TEST(dateComparison, comparisonTheSameDates) {
	char date_1[] = "2020-11-16";
	char date_2[] = "2020-11-16";

	EXPECT_EQ(0, dateComparison(date_1, date_2));
}
TEST(dateComparison, comparisonDatesWDifferentYears) {
	char date_1[] = "2002-6-1";
	char date_2[] = "2020-11-16";

	EXPECT_EQ(1, dateComparison(date_1, date_2));
}

TEST(dateComparison, comparisonDatesWSameYears) {
	char date_1[] = "2020-12-1";
	char date_2[] = "2020-9-8";

	EXPECT_EQ(0, dateComparison(date_1, date_2));
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

	EXPECT_EQ(head->ptr->temp, 20);
	EXPECT_STREQ(head->ptr->date, "2001-12-3");

	free(head->ptr);
	free(head);
}

TEST(push,sortByDTemperature) {
	list* head = NULL;
	head = push(head, "2018-9-11", 15);
	head = push(head, "2002-9-2", -10);
	head = push(head, "2003-9-1", 25);

	EXPECT_TRUE(head->temp < head->ptr->temp);
	EXPECT_EQ(head->temp, -10);
	EXPECT_STREQ(head->date, "2002-9-2");

	EXPECT_TRUE(head->ptr->temp < head->ptr->ptr->temp);
	EXPECT_EQ(head->ptr->temp, 15);
	EXPECT_STREQ(head->ptr->date, "2018-9-11");

	EXPECT_EQ(head->ptr->ptr->temp, 25);
	EXPECT_STREQ(head->ptr->ptr->date, "2003-9-1");

	free(head->ptr->ptr);
	free(head->ptr);
	free(head);
}

TEST(push, sortByDate) {
	list* head = NULL;

	head = push(head, "2018-10-11", -20);
	head = push(head, "2003-9-2", -20);
	head = push(head, "2003-9-1", -20);

	EXPECT_EQ(head->temp, head->ptr->temp);
	EXPECT_EQ(head->temp, head->ptr->ptr->temp);

	EXPECT_STREQ(head->date, "2003-9-1");
	EXPECT_STREQ(head->ptr->date, "2003-9-2");
	EXPECT_STREQ(head->ptr->ptr->date, "2018-10-11");

	free(head->ptr->ptr);
	free(head->ptr);
	free(head);
}


TEST(weatherBelowZero, findElementsWWeatherBelowZero) {
	list list_1, list_2, list_3;
	list_1 = { "2003-1-4", -15 };
	list_2 = { "2004-5-6", -10 };
	list_3 = { "2014-3-11", 10 };
	list_2.ptr = &list_3;
	list_1.ptr = &list_2;

	EXPECT_EQ(weatherBelowZero(&list_1), 2);
}

TEST(weatherBelowZero, noElementsWWeatherBelowZero) {
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

	ASSERT_FALSE(head == NULL);
	EXPECT_EQ(head->temp, -10);
	EXPECT_STREQ(head->date, "2020-12-1");

	ASSERT_FALSE(head->ptr == NULL);
	EXPECT_EQ(head->ptr->temp, 0);
	EXPECT_STREQ(head->ptr->date, "2020-3-4");

	ASSERT_FALSE(head->ptr->ptr == NULL);
	EXPECT_EQ(head->ptr->ptr->temp,25);
	EXPECT_STREQ(head->ptr->ptr->date, "2020-6-1");

	free(head->ptr->ptr);
	free(head->ptr);
	free(head);
}

TEST(averageTemperatureSearch, findTwoElementsWAverageTemperature) {
	list list_1, list_2, list_3;

	list_1 = { "2003-1-4", 0 };
	list_2 = { "2004-5-6", 0 };
	list_3 = { "2014-3-11", 10 };

	list_2.ptr = &list_3;
	list_1.ptr = &list_2;

	EXPECT_EQ(averageTemperatureSearch(&list_1, 0), 2);
}

TEST(averageTemperatureSearch, findThreeElementsWAverageTemperature) {
	list list_1, list_2, list_3;

	list_1 = { "2003-1-4", 10 };
	list_2 = { "2004-5-6", 10 };
	list_3 = { "2014-3-11", 10 };

	list_2.ptr = &list_3;
	list_1.ptr = &list_2;

	EXPECT_EQ(averageTemperatureSearch(&list_1, 10), 3);
}

TEST(averageTemperatureSearch, noElementsWAverageTemperature) {
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

	return RUN_ALL_TESTS();
}
