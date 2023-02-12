#include <stdio.h>
#include <malloc.h>
#include <locale.h>

#define INCORRECT_VALUE (-1)
#define TIMESTAMP_SIZE 3
#define TIMESTAMP_STRING_SIZE 8

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

/*! \brief Main function
 *
 *  \details Control unit testing via console/terminal
 *
 *  \return 0, upon exit success
 */
int main() {
    char* first_string = (char*) malloc(TIMESTAMP_STRING_SIZE * sizeof first_string);
    char* second_string = (char*) malloc(TIMESTAMP_STRING_SIZE * sizeof second_string);
    scanf("%8s", first_string);
    if(validate(&first_string) == 0) {
        printf("Not valid");
        return 0;
    }
    scanf("%8s", second_string);
    if(validate(&second_string) == 0) {
        printf("Not valid");
        return 0;
    }
    int* first_timestamp = (int*) malloc(TIMESTAMP_SIZE * sizeof first_timestamp);
    int* second_timestamp = (int*) malloc(TIMESTAMP_SIZE * sizeof first_timestamp);
    init_array(first_timestamp, TIMESTAMP_SIZE);
    init_array(second_timestamp, TIMESTAMP_SIZE);
    split(first_timestamp, &first_string);
    split(second_timestamp, &second_string);
    int validation_first = check_timestamp(first_timestamp[0], first_timestamp[1], first_timestamp[2]);
    int validation_second = check_timestamp(second_timestamp[0], second_timestamp[1], second_timestamp[2]);
    if(validation_first == 0 || validation_second == 0) {
        printf("Not valid ");
        return 0;
    }
    printf("%d seconds\n", timestamp_seconds(second_timestamp) - timestamp_seconds(first_timestamp));
    free(first_timestamp);
    free(second_timestamp);
    free(first_string);
    free(second_string);

    return 0;
}
