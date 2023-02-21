#pragma once
#ifndef _ringbuffer_
#define _ringbuffer_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

    struct ringbuffer {
        void* buffer_ptr; //A void pointer to the buffer
        int16_t size; //size of buffer
        uint16_t read_mirror : 1; //Mirror indicator bit for read operation,0 means the read pointer is in the preimage space, 1 means the read pointer is in the mirror space
        uint16_t read_pos : 15; 
        uint16_t write_mirror : 1; //Mirror indicator bit for write operation, 0 means the write pointer is in the preimage space, 1 means the write pointer is in the mirror space
        uint16_t write_pos : 15;
    };
    typedef struct ringbuffer* ringbuffer_ptr; //Defines a struct pointer type ringbufferer_ptr

#define ringbuffer_EMPTY      0
#define ringbuffer_FULL       1
#define ringbuffer_HALFFULL   2

    static inline int32_t ringbuffer_state_get(ringbuffer_ptr ptr) { //Get buffer status
        if (ptr->read_pos == ptr->write_pos) { //If the read and write pointers are the same, the buffer is empty or full
            if (ptr->read_mirror == ptr->write_mirror)
                return ringbuffer_EMPTY; //If the read and write pointers are in the same memory space, the buffer is considered empty.
            else
                return ringbuffer_FULL; //Otherwise, the buffer is considered full
        }
        else
            return ringbuffer_HALFFULL; //Otherwise it is halffull
    }

#define ringbuffer_data_space_len(ptr) ((ptr)->size - ringbuffer_data_len(ptr)) //The buffer size minus the buffer data size is the available buffer size

    int16_t ringbuffer_data_len(ringbuffer_ptr ptr);
    int32_t ringbuffer_put(ringbuffer_ptr ptr, int16_t* element);
    int32_t ringbuffer_get(ringbuffer_ptr ptr, int16_t* element);

#ifdef __cplusplus
}
#endif

#endif