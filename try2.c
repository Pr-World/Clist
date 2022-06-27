#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int _sc( const char* a, const char* b )
{
	return (strcmp(a,b)==0);
}

void List_Create ( size_t n , ... )
{
	size_t i;
	char* pvt;

	va_list va, vac;
	va_start(va, n);

	// for vprintf for check
	va_copy(vac, va);
	for (i = 0; i < n*2; ++i)
	{
		int check;
		// check for format types
		if (i%2)
		{
			// we just want it to check for format
			char tmp[9];
			if ( _sc(pvt, "d") )
				// integer
				check = vsnprintf(tmp, 9, "%d", vac);
			else if ( _sc(pvt, "u") )
				// unsigned 
				check = vsnprintf(tmp, 9, "%u", vac);
			else if ( _sc(pvt, "li") )
				// long int
				check = vsnprintf(tmp, 9, "%li", vac);
			else if ( _sc(pvt, "lu") )
				// long unsigned
				check = vsnprintf(tmp, 9, "%lu", vac);
			else if ( _sc(pvt, "f") )
				// float
				check = vsnprintf(tmp, 9, "%f", vac);
			else if ( _sc(pvt, "lf") )
				// double
				check = vsnprintf(tmp, 9, "%lf", vac);
			else if ( _sc(pvt, "c") )
				// character
				check = vsnprintf(tmp, 9, "%c", vac);
			else if ( _sc(pvt, "s") )
				// string
				check = vsnprintf(tmp, 9, "%s", vac);
			else if ( _sc(pvt, "lli") )
				// long long int
				check = vsnprintf(tmp, 9, "%lli", vac);
			else if ( _sc(pvt, "llu") )
				// long long unsigned
				check = vsnprintf(tmp, 9, "%llu", vac);
		}
		else
		{
			// we just want it to check for format
			char tmp[9];
			check = vsnprintf(tmp, 9, "%s", vac);

			pvt = va_arg(va, char*);
		}
		printf("CHECK: %d\n",check);
	}
	va_end(va);
}

int main()
{
	List_Create(1, "i", 5);
}