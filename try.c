#include<stdio.h>
#include "list.h"

/*
i = int
c = char
s = string [ char* ]
d = double
f = float [but is stored as double for precise value]
*/

int main()
{
	list a = lcreate("si","Prakash Niroula",896);
	printf("Value in 0 index is of type: %c!\n",a.fmt[0]);

	return 0;
}