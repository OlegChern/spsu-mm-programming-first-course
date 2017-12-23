//
// Created by rinsler on 23.12.17.
//

#ifndef TASK_9_MEMORY_MANAGER_MEMORY_MANAGER_H
#define TASK_9_MEMORY_MANAGER_MEMORY_MANAGER_H

typedef struct
{
    void *ptr;
    size_t size;
} Block;

void init(size_t size);
void terminate();

void *myMalloc(size_t size);
void *myCalloc(size_t cnt, size_t size);
void myFree(void *ptr);
void *myRealloc(void *ptr, size_t size);

void printFree();
void printTaken();

#endif //TASK_9_MEMORY_MANAGER_MEMORY_MANAGER_H
