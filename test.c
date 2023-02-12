#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include <malloc.h>

/* Success code */
#define SUCCESS 1

/* Fail code */
#define FAIL 0
#define INCORRECT_VALUE (-1)
#define TIMESTAMP_SIZE 3
#define TIMESTAMP_STRING_SIZE 8
#define HOUR 0
#define MINUTE 1
#define SECONDS 2


/*! \brief Check timestamp by valid values
 *
 *  \details Check timestamps values by valid values.
 *
 *  \param   hour               Hour values.
 *  \param   minute            Minute values.
 *  \param   second           Seconds value.
 *
 *  \return  Returns the flag whether the time values are valid
 */
int check_timestamp(int hour, int minute, int second) {
    int valid = 1;
    if(hour < 0 || hour >= 24) {
        valid = 0;
    }
    if(minute < 0 || minute > 60) {
        valid = 0;
    }
    if(second < 0 || second > 60) {
        valid = 0;
    }
    return valid;
}


/*! \brief Fills the array with temporary invalid values
 *
 *  \details Fills the array with temporary invalid values needed to store the current time value
 *
 *  \param   array            Timestamp array.
 *  \param   size            Timestamp size.
 *
 */
void init_array(int* array, size_t size) {
    for (int i = 0; i < size; ++i) {
        array[i] = INCORRECT_VALUE;
    }
}


/*! \brief Converts a timestamp to seconds
 *
 *  \param   timestamp            Timestamp array.
 *
 *  \return  Seconds value
 */
int timestamp_seconds(int* timestamp) {
    return (timestamp[0] * 60 * 60) + (timestamp[1] * 60) + (timestamp[0]);
}

/*! \brief Checks the string for compliance with the desired format
 *
 *  \details Checks the string for compliance with the desired format of the type HH.MM.SS
 *
 *  \param   p_string            Pointer to string.
 *
 *  \return  flag validation
 */
int validate(char** p_string) {
    char* string = *p_string;
    int numbers = 0;
    int dotes = 0;
    int valid = 0;
    for (int i = 0; i < TIMESTAMP_STRING_SIZE; ++i) {
        if(string[i] == '.'){
            dotes++;
            if(numbers != 2) return valid;
            numbers = 0;
        } else {
            numbers++;
        }

    }
    if(dotes != 2) return valid;
    valid = 1;
    return valid;
}

/*! \brief Collects a timestamp from a string
 *
 *  \details Parse a timestamp from a string into an array
 *
 *  \param   timestamp            Timestamp array
 *  \param   p_string            Pointer to string.
 *
 *  \return  flag validation
 */
void split(int* timestamp, char** p_string) {
    int counter = 0;
    char* string = *p_string;
    int sum = 0;
    int is_first = 1;
    int koef = 10;
    for (int i = 0; i <= 8; ++i) {
        if(string[i] == '.' || i == 8) {
            timestamp[counter] = sum;
            sum = 0;
            counter++;
            koef = 10;
            continue;
        }
        sum += (int)((string[i] - 48) * koef);
        koef = 1;
    }
}

/*! \brief Other unit test for init array. */
void test1(void) {
    size_t size1 = 10;
    int* array = (int*) malloc(size1 * sizeof array);
    init_array(array, size1);
    for (int i = 0; i < size1; ++i) {
        CU_ASSERT_EQUAL(array[i], -1);
    }

    size_t size2 = 1;
    int* array1 = (int*) malloc(size2 * sizeof array);
    init_array(array, size2);
    for (int i = 0; i < size2; ++i) {
        CU_ASSERT_EQUAL(array[i], -1);
    }

}

/*! \brief Other unit test for validate timestamp. */
void test2(void) {
    int* timestamp = (int*) malloc(TIMESTAMP_SIZE * sizeof timestamp);
    timestamp[HOUR] = 13; timestamp[MINUTE] = 4; timestamp[SECONDS] = 58;
    CU_ASSERT_EQUAL(check_timestamp(timestamp[HOUR], timestamp[MINUTE], timestamp[SECONDS]), SUCCESS);
    timestamp[HOUR] = 24; timestamp[MINUTE] = 25; timestamp[SECONDS] = 12;
    CU_ASSERT_EQUAL(check_timestamp(timestamp[HOUR], timestamp[MINUTE], timestamp[SECONDS]), FAIL);
    timestamp[HOUR] = 23; timestamp[MINUTE] = 61; timestamp[SECONDS] = 12;
    CU_ASSERT_EQUAL(check_timestamp(timestamp[HOUR], timestamp[MINUTE], timestamp[SECONDS]), FAIL);
    timestamp[HOUR] = 23; timestamp[MINUTE] = 53; timestamp[SECONDS] = 61;
    CU_ASSERT_EQUAL(check_timestamp(timestamp[HOUR], timestamp[MINUTE], timestamp[SECONDS]), FAIL);
}

void test3(void) {
    int* timestamp = (int*) malloc(TIMESTAMP_SIZE * sizeof timestamp);
    timestamp[HOUR] = 13; timestamp[MINUTE] = 4; timestamp[SECONDS] = 58;
    CU_ASSERT_EQUAL(timestamp_seconds(timestamp), 47818);
    timestamp[HOUR] = 0; timestamp[MINUTE] = 0; timestamp[SECONDS] = 0;
    CU_ASSERT_EQUAL(timestamp_seconds(timestamp), 0);
}

void test4(void) {
    // 12.01.52
    char* string1 = (char*) malloc(TIMESTAMP_STRING_SIZE * sizeof string1);
    // 432.23.1
    char* string2 = (char*) malloc(TIMESTAMP_STRING_SIZE * sizeof string2);
    // 42.124.5
    char* string3 = (char*) malloc(TIMESTAMP_STRING_SIZE * sizeof string3);
    string1[0] = '1'; string1[1] = '2'; string1[2] = '.'; string1[3] = '0';
    string1[4] = '1'; string1[5] = '.'; string1[6] = '5'; string1[7] = '2';

    string2[0] = '4'; string2[1] = '3'; string2[2] = '2'; string2[3] = '.';
    string2[4] = '2'; string2[5] = '3'; string2[6] = '.'; string2[7] = '1';

    string3[0] = '4'; string2[1] = '2'; string2[2] = '.'; string2[3] = '1';
    string2[4] = '2'; string2[5] = '4'; string2[6] = '.'; string2[7] = '1';

    CU_ASSERT_EQUAL(validate(&string1), SUCCESS);
    CU_ASSERT_EQUAL(validate(&string2), FAIL);
    CU_ASSERT_EQUAL(validate(&string3), FAIL);
}

void test5(void) {
    // 12.01.52
    char* string1 = (char*) malloc(TIMESTAMP_STRING_SIZE * sizeof string1);
    char* string2 = (char*) malloc(TIMESTAMP_STRING_SIZE * sizeof string1);

    int* timestamp = (int*) malloc(TIMESTAMP_SIZE * sizeof timestamp);

    string1[0] = '1'; string1[1] = '2'; string1[2] = '.'; string1[3] = '0';
    string1[4] = '1'; string1[5] = '.'; string1[6] = '5'; string1[7] = '2';

    string2[0] = '0'; string1[1] = '2'; string1[2] = '.'; string1[3] = '0';
    string1[4] = '1'; string1[5] = '.'; string1[6] = '0'; string1[7] = '2';

    split(timestamp, &string1);

    CU_ASSERT_EQUAL(timestamp[HOUR], 12);
    CU_ASSERT_EQUAL(timestamp[MINUTE], 1);
    CU_ASSERT_EQUAL(timestamp[SECONDS], 52);

    split(timestamp, &string2);

    CU_ASSERT_EQUAL(timestamp[HOUR], 2);
    CU_ASSERT_EQUAL(timestamp[MINUTE], 1);
    CU_ASSERT_EQUAL(timestamp[SECONDS], 2);


}
/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("main_suite", NULL, NULL);
    CU_ADD_TEST(suite, test1);
    CU_ADD_TEST(suite, test2);
    CU_ADD_TEST(suite, test3);
    CU_ADD_TEST(suite, test4);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
