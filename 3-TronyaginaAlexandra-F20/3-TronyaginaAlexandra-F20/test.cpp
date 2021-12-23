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
	int key;
	int i = 1;
	int expected[6] = { 2, 3, 4, 5, 7, 8 };
	int* result = (int*)malloc(sizeof(int));
	output = fopen("output_even.txt", "r");
	ASSERT_TRUE(output);
	fseek(output, 0, SEEK_END);
	i = ftell(output);
	EXPECT_TRUE(i > 0);
	fscanf(output, "%i", key);
	result[0] = key;
	i = 1;
	while (fscanf(output, "%i", key) != EOF) {
		result =(int*) realloc(result, sizeof(int));
		result[i] = key;
		i++;
	}
	EXPECT_EQ(i, 6);
	for ( i = 0; i < 6; i++)
		EXPECT_EQ(result[i], expected[i]);
}

TEST(FunctionalTest, kMin_Odd) {
	FILE* input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output_even.txt", "w");
	ASSERT_TRUE(output);
	sol(input, output, 6);
	fclose(input);
	fclose(output);
	int key;
	int i = 0;
	output = fopen("output_even.txt", "r");
	ASSERT_TRUE(output);
	fseek(output, 0, SEEK_END);
	i = ftell(output);
	EXPECT_EQ(i, 1);
	fscanf(output, "%i", key);
	EXPECT_EQ(9, key);
}

TEST(FunctionalTest, notFound) {
	FILE* input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output_even.txt", "w");
	ASSERT_TRUE(output);
	sol(input, output, 6);
	fclose(input);
	fclose(output);
	int key;
	int i = 0;
	output = fopen("output_even.txt", "r");
	ASSERT_TRUE(output);
	fseek(output, 0, SEEK_END);
	i = ftell(output);
	EXPECT_EQ(i, 0);
}