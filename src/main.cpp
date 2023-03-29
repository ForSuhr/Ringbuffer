/*
This ring buffer implementation is written by referring to the ring buffer algorithm in ringbuffer.c and ringbuffer.h of RTOS.
@Author: Jiandong Zhao
@Date: 2022-09-08
*/

#include <stdio.h>
#include <string.h>
#include "ringbuffer.h"
#include <iostream>
using namespace std;

int16_t a = 1;
int16_t b = 2;
int16_t c = 3;
int16_t d = 4;
int16_t e = 5;
int16_t f = 6;
int16_t g = 7;
int16_t h = 8;
int16_t data_array[] = {a, b, c, d, e, f, g, h};

int main(void) {
    struct ringbuffer test_ringbuffer = {
        &data_array,
        sizeof(data_array),
        0,
        0,
        0,
        0
    };

    int i = 2; //loop two times
    while (i--) {

        for (int i = 0; i < sizeof(data_array) / 2; i++) {
            ringbuffer_put(&test_ringbuffer, &data_array[i]);
        }

        int16_t receive_array[sizeof(data_array) / 2];

        for (int i = 0; i < sizeof(receive_array) / 2; i++) {
            ringbuffer_get(&test_ringbuffer, &receive_array[i]);
        }

        for (int i = 0; i < sizeof(receive_array) / 2; i++) {
            cout << receive_array[i] << endl;
        }

    }
}