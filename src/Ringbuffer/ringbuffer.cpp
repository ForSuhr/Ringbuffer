#include "ringbuffer.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <iostream>

int16_t ringbuffer_data_len(ringbuffer_ptr ptr) {
    switch (ringbuffer_state_get(ptr))
    {
    case ringbuffer_EMPTY:
        return 0;
    case ringbuffer_FULL:
        return ptr->size;
    case ringbuffer_HALFFULL:
        if (ptr->read_mirror == ptr->write_mirror) {
            return ptr->write_pos - ptr->read_pos;
        }
        else {
            return ptr->size + (ptr->read_pos - ptr->write_pos);
        }
    }
};

int32_t ringbuffer_put(ringbuffer_ptr ptr, int16_t* element) {
    assert(ptr != NULL); //If the pointer is not null, the execution continues normally, otherwise an error is raised

    if (!ringbuffer_data_space_len(ptr)) { //The available buffer size is 0, which means the buffer is full, return 0
        // full buffer
        return 0;
    }

    ((int16_t*)ptr->buffer_ptr)[ptr->write_pos] = *element; //Convert the buffer pointer in the struct to an integer pointer, and write the elements to the buffer according to the write pointer index

    if (ptr->write_pos == ptr->size - 1) { //If writing to the end of the buffer
        ptr->write_mirror = ~ptr->write_mirror; //reverse the mirror indicator bit
        ptr->write_pos = 0; //Write pointer back to the beginning of the buffer
    }
    else {
        ptr->write_pos++; //Otherwise the write pointer is moved to the next index
    }

    return 1; //Successful writing
};

int32_t ringbuffer_get(ringbuffer_ptr ptr, int16_t* element) {
    assert(ptr != NULL);

    if (!ringbuffer_data_len(ptr)) {
        // empty buffer
        return 0;
    }

    *element = ((int16_t*)ptr->buffer_ptr)[ptr->read_pos];

    if (ptr->read_pos == ptr->size - 1) {
        ptr->read_mirror = ~ptr->read_mirror;
        ptr->read_pos = 0;
    }
    else {
        ptr->read_pos++;
    }

    return 1; //Successful reading
};