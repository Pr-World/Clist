#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	// "Prakash\0[][][][91]BLABLALOLO\0[][][][12.5]"

	// -------- REMOVING ELEMENT ---------
	// The way to do this is to pull the second elements to the elementDeletePos++for loop
	// "[][][][91]BLABLALOLO\0[][][][12.5]\0\0\0\0\0\0\0"
	// REALLOC TO totalSize - theElementSize [realloc deletes the backpart so no worries!]
	// "[][][][91]BLABLALOLO\0[][12.5]"

	// -------- ADDING ELEMENT -----------
	
	// if adding to last [i.e] pushing, ITS EZY
	// realloc to + the new size
	// continue adding from last size

	// if adding not to last [i.e] something like lst = lst[:n] + [data] + lst[n:] in python
	// realloc to + the sizeOfElement to add
	// move all elements from the oldSizeBack till the position you want to add
	// by position it is refferring to the position of already existing element's position
	// STORE already existing element's position in a variable [like alrE]
	// NOTE: already existing element should also be pushed towards back 'n' times
	// where 'n' is the sizeOfElement to add

	// now from alrE position, store the element in bytewise manner in lst!

	// --------- EDITING ELEMENT ----------
	// EZ EZ EZ EZ PZ LEMON SQUIZZY
	// Delete the element!
	// Add the new toBeEdited element in the pos!
	char* bro;
	void* a = realloc(bro,20);
	if(a==NULL){
		printf("Could not reallocate :(\n");
		exit(10);
	}
	strcpy(bro,"HEY BRO!!!");
	printf("%s\n",bro);
}