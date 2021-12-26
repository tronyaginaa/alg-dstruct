#include "pch.h"
#include "LabF.h"


TEST(FunctionalTest, kMin_Even) {
	FILE* input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output_even.txt", "w");
	ASSERT_TRUE(output);
	sol(input, output, 6);
	fclose(input);
	fclose(output);
	int keyExpected, keyOutput;
	int i = 1;
	FILE* expected = fopen("expected_even.txt", "r");
	ASSERT_TRUE(expected);
	output = fopen("output_even.txt", "r");
	ASSERT_TRUE(output);
	fseek(output, 0, SEEK_END);
	fseek(expected, 0, SEEK_END);
	EXPECT_EQ(ftell(output), ftell(expected));
	fseek(output, 0, SEEK_SET);
	fseek(expected, 0, SEEK_SET);
	while (fscanf(output, "%i", &keyOutput) != EOF && fscanf(expected, "%i", &keyExpected) != EOF)
		EXPECT_EQ(keyExpected, keyOutput);
	fclose(output);
	fclose(expected);
}

TEST(FunctionalTest, kMin_Odd) {
	FILE* input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output_odd.txt", "w");
	ASSERT_TRUE(output);
	sol(input, output, 7);
	fclose(input);
	fclose(output);
	int key;
	int i = 0;
	output = fopen("output_odd.txt", "r");
	ASSERT_TRUE(output);
	fseek(output, 0, SEEK_END);
	i = ftell(output);
	EXPECT_EQ(i, 1);
	fseek(output, 0, SEEK_SET);
	fscanf(output, "%i", &key);
	EXPECT_EQ(9, key);
	fclose(output);
}

TEST(FunctionalTest, notFound) {
	FILE* input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output_notFound.txt", "w");
	ASSERT_TRUE(output);
	sol(input, output, 10);
	fclose(input);
	fclose(output);
	int key;
	int i = 0;
	output = fopen("output_notFound.txt", "r");
	ASSERT_TRUE(output);
	fseek(output, 0, SEEK_END);
	i = ftell(output);
	EXPECT_EQ(i, 0);
	fclose(output);
}