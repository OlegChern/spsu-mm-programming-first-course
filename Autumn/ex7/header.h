//
// Created by olchern on 07.11.17.
//

#ifndef EX7_HEADER_H
#define EX7_HEADER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct list;
struct hash_t;

struct hash_t* initialize(int size, struct hash_t*);

int listAddToEnd(int, int, struct list *);

void listValueRemove(int, struct list *);

bool listSearch(int, struct list *, int *);

void listPrint(struct list *);

void listDelete(struct list *);

void hashDelete(struct hash_t *);

void hashAdd(struct hash_t *, int, int);

int hashFunc(int, struct hash_t *);

void hashResize(struct hash_t *);

bool hashSearch(struct hash_t *, int, int *);

void hashRemove(struct hash_t *, int);

void hashPrint(struct hash_t *);

#endif //EX7_HEADER_H
