#ifndef LIST_H_INCL
#define LIST_H_INCL

#include <stdlib.h>

typedef struct mtype
{
	void* val;
	unsigned int type;
}mtype;


// linked list
typedef struct __internal_list
{
	mtype val;
	struct __internal_list* next;
}

typedef struct list
{
	__internal_list __list;
	size_t size;
}list;

typedef struct listType
{
	list (* create ) ( size_t n, ... );
	list (* append ) ( list, unsigned int type , ... );
	list (* append_other ) ( list, unsigned int type, void * var, size_t size );
	mtype (* get ) ( list, size_t elem );
}listType;

#define LIST_INTERNAL_SIZE sizeof(__internal_list)
#define LIST_SIZE sizeof(list)

listType lst;

#endif