#include "list.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int _sc( const char* a, const char* b )
{
	return (strcmp(a,b)==0);
}

list List_Create ( size_t n , ... )
{
	list lst;
	lst.size = n;

	// varargs
	va_list va;
	va_start(va, n);

	// loop variable
	size_t i;

	// this list
	__internal_list* this_list = &lst.__list;

	// We expect char* type, _VAR in varargs and just elemNo in size_t n
	for (i = 0; i < n; ++i)
	{
		char * fmt = va_arg(va, char*);
		if (fmt == "d")
		{
			this_list -> val = malloc(sizeof(int));
			
		}
		this_list = this_list -> next
		if ( this_list == NULL )
		{
			this_list = malloc(sizeof(__internal_list));
			if ( this_list == NULL )
			{
				printf("Clist Error: List can't be created malloc() returned NULL\n");
				exit(10);
			}
		}
	}

	va_end(va);
}