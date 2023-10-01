#include <stdio.h>
#include "testc.h"

#define TEST_MULTIPLIER 16
#define MAX_TEST_LENGTH 1024*TEST_MULTIPLIER

/* (*)_offsets saves the starting position of strings that gets stored in 
 * test_input and test_output */
static unsigned int input_offsets[MAX_TEST_LENGTH / TEST_MULTIPLIER] = {0};
static unsigned int output_offsets[MAX_TEST_LENGTH / TEST_MULTIPLIER] = {0};


static unsigned int max_tests = 0;

static char input_strings[MAX_TEST_LENGTH] = {'\0'};
static char output_strings[MAX_TEST_LENGTH] = {'\0'};

int add_test_string(char input[], char expected_output[])
{
	int i = 0, j = 0, offset_i = 0, offset_j = 0;

	if ( max_tests > 0 )
	{
		offset_i = input_offsets[max_tests];
		offset_j = output_offsets[max_tests];
	}

	while (input[i] != '\0')
	{
		input_strings[offset_i + i] = input[i];
		i += 1;
	}

	while (expected_output[j] != '\0')
	{
		output_strings[offset_j + j] = expected_output[j];
		j += 1;
	}

	input_strings[offset_i + i] = '\0';
	output_strings[offset_j + j] = '\0';
	
	max_tests += 1;

	/* Sets next offset to after '\0' */
	input_offsets[max_tests] = i + offset_i + 1;
	output_offsets[max_tests] = j + offset_j + 1;

	return max_tests;
}

static unsigned int current = -1;

int next_test_string()
{
	int i, offset;
	extern char test_input[];

	current += 1;

	offset = input_offsets[current];
	i = 0;

	while (input_strings[offset + i] != '\0')
	{
		test_input[i] = input_strings[offset + i];
		i += 1;
	}

	test_input[i] = '\0';

	return current < max_tests ? i : -1;
}

void test_string(char output[])
{
	int i, offset, match, ml_output;
	char s[MAX_LINE_LENGTH];


	i = match = ml_output = 0;

	offset = output_offsets[current];


	while (output_strings[offset + i] != '\0')
	{
		if (output_strings[offset + i] == output[i])
			match += 1;

		i += 1;
	}

	if (i > 20)
		ml_output = 1;

	if (match == i)
	{
		printf("[OK] %s\n", output);
	}
	else
	{
		/* A ugly hack we have to do because we cannot
		 * use pointers yet.
		 *
		 * It just copies the expected string
		 * to s.
		 */
		do
		{
			s[i] = output_strings[offset + i];
		} while(i-- >= 0);
		
		if (ml_output)
		{
			printf("[ERROR]\n");
			printf("------MULTILINE OUTPUT-----\n");
			printf("---BEGIN EXPECTED OUTPUT---\n");
			printf("%s\n", s);
			printf("----END EXPECTED OUTPUT----\n");
			printf("----BEGIN ACTUAL OUTPUT----\n");
			printf("%s\n", output);
			printf("-----END ACTUAL OUTPUT-----\n\n");
		}
		else
		{
			printf("[ERROR] Wanted %s but got %s\n", s, output);
		}
	}
}
