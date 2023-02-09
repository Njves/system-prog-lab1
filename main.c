#include <stdio.h>
#include <malloc.h>
#include <locale.h>

#define INCORRECT_VALUE (-1)
#define TIMESTAMP_SIZE 3
#define TIMESTAMP_STRING_SIZE 8

void print_array(int* array, size_t size) {
    for (int i = 0; i < size; ++i) {
        printf("%d\n", array[i]);
    }
}

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

void init_array(int* array, size_t size) {
    for (int i = 0; i < 3; ++i) {
        array[i] = INCORRECT_VALUE;
    }
}

int timestamp_seconds(int* timestamp) {
    return (timestamp[0] * 60 * 60) + (timestamp[1] * 60) + (timestamp[0]);
}

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
            is_first = 1;
            koef = 10;
            continue;
        }
        sum += (int)((string[i] - 48) * koef);
        is_first = 0;
        koef = 1;
    }

}

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


    return 0;
}
