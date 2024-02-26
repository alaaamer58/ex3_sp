#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _StrList {
    char **data;
    size_t size;
    size_t capacity;
};

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (list == NULL) {
        return NULL;
    }
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
    return list;
}

void StrList_free(StrList* StrList) {
    if (StrList == NULL) {
        return;
    }
    for (size_t i = 0; i < StrList->size; ++i) {
        free(StrList->data[i]);
    }
    free(StrList->data);
    free(StrList);
}

size_t StrList_size(const StrList* StrList) {
    return StrList == NULL ? 0 : StrList->size;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if (StrList == NULL) {
        return;
    }
    if (StrList->size >= StrList->capacity) {
        size_t new_capacity = StrList->capacity == 0 ? 1 : StrList->capacity * 2;
        char** new_data = (char**)realloc(StrList->data, new_capacity * sizeof(char*));
        if (new_data == NULL) {
            return;
        }
        StrList->data = new_data;
        StrList->capacity = new_capacity;
    }
    StrList->data[StrList->size] = strdup(data);
    ++StrList->size;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (StrList == NULL || index < 0 || index > StrList->size) {
        return;
    }
    if (index == StrList->size) {
        StrList_insertLast(StrList, data);
        return;
    }
    if (StrList->size >= StrList->capacity) {
        size_t new_capacity = StrList->capacity == 0 ? 1 : StrList->capacity * 2;
        char** new_data = (char**)realloc(StrList->data, new_capacity * sizeof(char*));
        if (new_data == NULL) {
            return;
        }
        StrList->data = new_data;
        StrList->capacity = new_capacity;
    }
    memmove(&StrList->data[index + 1], &StrList->data[index], (StrList->size - index) * sizeof(char*));
    StrList->data[index] = strdup(data);
    ++StrList->size;
}

char* StrList_firstData(const StrList* StrList) {
    if (StrList == NULL || StrList->size == 0) {
        return NULL;
    }
    return StrList->data[0];
}

void StrList_print(const StrList* StrList) {
    if (StrList == NULL) {
        return;
    }
    for (size_t i = 0; i < StrList->size; ++i) {
        printf("%s ", StrList->data[i]);
    }
    printf("\n");
}

void StrList_printAt(const StrList* Strlist,int index){
    if(Strlist == NULL || index < 0 || index >= Strlist->size){
        return;
    }
    printf("%s\n",Strlist->data[index]);
}

int StrList_printLen(const StrList* Strlist){
    if(Strlist == NULL){
        return -1;
    }
    int len = 0;
    for(size_t i = 0; i < Strlist->size; i++){
        len += strlen(Strlist->data[i]);
    }
    return len;
}

int StrList_count(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) {
        return 0;
    }
    int count = 0;
    for (size_t i = 0; i < StrList->size; ++i) {
        if (strcmp(StrList->data[i], data) == 0) {
            ++count;
        }
    }
    return count;
}

void StrList_remove(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) {
        return;
    }
    size_t write_index = 0;
    for (size_t read_index = 0; read_index < StrList->size; ++read_index) {
        if (strcmp(StrList->data[read_index], data) != 0) {
            StrList->data[write_index] = StrList->data[read_index];
            ++write_index;
        } else {
            free(StrList->data[read_index]);
        }
    }
    StrList->size = write_index;
}

void StrList_removeAt(StrList* StrList, int index) {
    if (StrList == NULL || index < 0 || index >= StrList->size) {
        return;
    }
    free(StrList->data[index]);
    memmove(&StrList->data[index], &StrList->data[index + 1], (StrList->size - index - 1) * sizeof(char*));
    --StrList->size;
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {
    if (StrList1 == NULL || StrList2 == NULL || StrList1->size != StrList2->size) {
        return 0;
    }
    for (size_t i = 0; i < StrList1->size; ++i) {
        if (strcmp(StrList1->data[i], StrList2->data[i]) != 0) {
            return 0;
        }
    }
    return 1;
}

StrList* StrList_clone(const StrList* StrList) {
    if (StrList == NULL) {
        return NULL;
    }
    StrList* clone = StrList_alloc();
    if (clone == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < StrList->size; ++i) {
        StrList_insertLast(clone, StrList->data[i]);
    }
    return clone;
}

void StrList_reverse(StrList* StrList) {
    if (StrList == NULL) {
        return;
    }
    for (size_t i = 0, j = StrList->size - 1; i < j; ++i, --j) {
        char* temp = StrList->data[i];
        StrList->data[i] = StrList->data[j];
        StrList->data[j] = temp;
    }
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL) {
        return;
    }
    qsort(StrList->data, StrList->size, sizeof(char*), cmpfunc);
}

int cmpfunc(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->size <= 1) {
        return 1;
    }
    for (size_t i = 1; i < StrList->size; ++i) {
        if (strcmp(StrList->data[i - 1], StrList->data[i]) > 0) {
            return 0;
        }
    }
    return 1;
}
