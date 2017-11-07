//
// Created by olchern on 07.11.17.
//

#ifndef EX7_HEADER_H
#define EX7_HEADER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct list;
struct hash_t;

void list_AddToEnd (int, int, struct list*);

void list_ValueRemove (int, struct list*);

bool list_Search (int, struct list*, int*);

void list_Print (struct list*);

void list_Delete (struct list*);

void hash_Delete (struct hash_t*);

void hash_Add(struct hash_t*, int, int);

int hash_func (int, struct hash_t*);

void hash_Resize (struct hash_t*);

bool hash_Search (struct hash_t*, int, int*);

void hash_Remove (struct hash_t*, int);

void hash_Print (struct hash_t*);

#endif //EX7_HEADER_H
