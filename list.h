#ifndef _LIST_H_INCL
#define _LIST_H_INCL

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct{
	char* fmt;
	char* list;
	unsigned int Lsize;
	unsigned int size;
}list;

list lcreate(const char* fmt, ...)
{
	const char* M_ERR="ERROR : COULD NOT ALLOCATE MEMORY FOR LIST\n";
	va_list va;
	list lst;
	lst.Lsize = 0;
	lst.size = 0;
	lst.list = malloc(1);
	if(lst.list==NULL){
		printf("%s\n",M_ERR);
		exit(10);
	}
	lst.fmt = malloc(1);
	if(lst.fmt==NULL){
		free(lst.list);
		printf("%s\n",M_ERR);
		exit(10);
	}
	va_start(va,fmt);
	void* vtmp;
	for (int i = 0; i < strlen(fmt); ++i)
	{
		// allocating fmt to +1 because a new element is there!
		lst.size++;
		char* ftmp = malloc(lst.size-1);
		if(ftmp==NULL){
			free(lst.fmt);
			free(lst.list);
			printf("%s\n",M_ERR);
			exit(10);
		}
		strcpy(ftmp,lst.fmt);
		vtmp = realloc(lst.fmt,lst.size);
		if(vtmp==NULL){
			free(ftmp);
			free(lst.fmt);
			free(lst.list);
			printf("%s\n",M_ERR);
			exit(10);
		}
		strcpy(lst.fmt,vtmp);
		free(ftmp); // avoid memory leaks! \[o_X]/
		if(fmt[i]=='i'||fmt[i]=='I')
		{
			// integer size adding and reallocating to push elements
			lst.Lsize+=sizeof(int);
			
			char* ltmp = malloc(lst.Lsize-sizeof(int));
			if(ltmp==NULL){
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-sizeof(int); ++i)
			{
				ltmp[i]=lst.list[i];
			}
			vtmp = realloc(lst.list,lst.Lsize);
			if(vtmp==NULL){
				free(ltmp);
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-sizeof(int); ++i)
			{
				lst.list[i]=ltmp[i];
			}
			free(ltmp); // Avoid memory leaks \[o_X]/
			// integer to n-byte charachter conversion to store in lst
			// where n is size of integer
			lst.fmt[lst.size-1]='i';
			int tmpp = va_arg(va,int);
			int* tmp = &tmpp;
			void* tmp2 = tmp;
			char* tmp3 = tmp2;
			//after conversion, append the n byte charachters to the list!
			for (int i = sizeof(int); i>0; i--)
			{
				lst.list[lst.Lsize-i]=*(tmp3+sizeof(int)-i);
			}

		}else if(fmt[i]=='c'||fmt[i]=='C'){
			// For charachters its ezy because out list string lst
			// is contained of charachters so just make the format to charachter
			// and normally interprete as str
			// despite you need to reallocate the list size!
			lst.Lsize++;
			char* ltmp = malloc(lst.Lsize-1);
			if(ltmp==NULL){
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-1; ++i)
			{
				ltmp[i]=lst.list[i];
			}
			vtmp = realloc(lst.list,lst.Lsize);
			if(vtmp==NULL){
				free(ltmp);
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-1; ++i)
			{
				lst.list[i]=ltmp[i];
			}
			free(ltmp); // Avoid memory leaks \[o_X]/
			lst.fmt[lst.size-1]='c';
			lst.list[lst.Lsize-1] = (char)va_arg(va,int);
		}else if(fmt[i]=='s'||fmt[i]=='S'){
			//first get the actual string!
			char* st = va_arg(va,char*);
			//find out the size of string, using strlen! [we know 1 char = 1 byte!]
			// so size of string = no of charachters!
			size_t len = strlen(st);
			lst.Lsize+=len+1;
			char* ltmp = malloc(lst.Lsize-len-1);
			if(ltmp==NULL){
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-len-1; ++i)
			{
				ltmp[i]=lst.list[i];
			}
			vtmp = realloc(lst.list,lst.Lsize);
			if(vtmp==NULL){
				free(ltmp);
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-len-1; ++i)
			{
				lst.list[i]=ltmp[i];
			}
			free(ltmp); // Avoid memory leaks \[o_X]/
			strncpy(lst.list+lst.Lsize-len-1,st,strlen(st));
			lst.list[lst.Lsize-1] = '\0';
			lst.fmt[lst.size-1]='s';
		}else if(fmt[i]=='f'||fmt[i]=='F'){
			// float are not accurate
			// when converted from doule,
			// so treat them as double!
			lst.Lsize+=sizeof(double);
			char* ltmp = malloc(lst.Lsize-sizeof(double));
			if(ltmp==NULL){
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-sizeof(double); ++i)
			{
				ltmp[i]=lst.list[i];
			}
			vtmp = realloc(lst.list,lst.Lsize);
			if(vtmp==NULL){
				free(ltmp);
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-sizeof(double); ++i)
			{
				lst.list[i]=ltmp[i];
			}
			free(ltmp); // Avoid memory leaks \[o_X]/
			// double to n-byte conversion!
			lst.fmt[lst.size-1]='f';
			double tmpp = va_arg(va,double);
			double* tmp = &tmpp;
			void* tmp2 = tmp;
			char* tmp3 = tmp2;
			//after conversion, append the n byte charachters to the list!
			for (int i = sizeof(double); i>0; i--)
			{
				lst.list[lst.Lsize-i]=tmp3[sizeof(double)-i];
			}
		}else if(fmt[i]=='d'||fmt[i]=='D'){
			// double size adding and reallocating to push elements
			lst.Lsize+=sizeof(double);
			char* ltmp = malloc(lst.Lsize-sizeof(double));
			if(ltmp==NULL){
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-sizeof(double); ++i)
			{
				ltmp[i]=lst.list[i];
			}
			vtmp = realloc(lst.list,lst.Lsize);
			if(vtmp==NULL){
				free(ltmp);
				free(lst.fmt);
				free(lst.list);
				printf("%s\n",M_ERR);
				exit(10);
			}
			for (int i = 0; i < lst.Lsize-sizeof(double); ++i)
			{
				lst.list[i]=ltmp[i];
			}
			free(ltmp); // Avoid memory leaks \[o_X]/
			// double to n-byte conversion!
			lst.fmt[lst.size-1]='d';
			double tmpp = va_arg(va,double);
			double* tmp = &tmpp;
			void* tmp2 = tmp;
			char* tmp3 = tmp2;
			//after conversion, append the n byte charachters to the list!
			for (int i = sizeof(double); i>0; i--)
			{
				lst.list[lst.Lsize-i]=tmp3[sizeof(double)-i];
			}
			
		}
	}
	va_end(va);
	return lst;
}

void* lget(list a, unsigned int elem)
{
	int pos=0;
	for (int i=0; i < elem; ++i)
	{
		if(pos>=a.Lsize){
			return NULL;
		}

		if(a.fmt[i]=='i'){
			pos+=sizeof(int);
		}else if(a.fmt[i]=='f'){
			pos+=sizeof(double);
		}else if(a.fmt[i]=='d'){
			pos+=sizeof(double);
		}else if(a.fmt[i]=='s'){
			pos+=strlen(a.list+pos)+1;
		}
	}
	return a.list+pos;
}

list lpush(list a, char type, ...)
{
	va_list va;
	va_start(va,type);
	const char* M_ERR="ERROR : COULD NOT ALLOCATE MEMORY FOR LIST\n";
	list lst;
	lst.Lsize = a.Lsize;
	lst.size = a.size;
	if(type=='i'||type=='I'){
		lst.Lsize += sizeof(int);
		lst.size++;
		lst.list = malloc(lst.Lsize);
		if(lst.list==NULL)
		{
			printf("%s\n",M_ERR);
			exit(10);
		}
		lst.fmt = malloc(lst.size);
		if(lst.fmt==NULL)
		{
			free(lst.list);
			printf("%s\n",M_ERR);
			exit(10);
		}
		strcpy(lst.fmt,a.fmt);
		for (int i = 0; i < a.Lsize; ++i)
		{
			lst.list[i]=a.list[i];
		}
		free(a.list);
		free(a.fmt);
		int ival = va_arg(va,int);
		void* vp = &ival;
		char* cp = vp;
		for (int i = sizeof(int); i > 0; --i)
		{
			lst.list[lst.Lsize-i]=cp[sizeof(int)-i];
		}
		lst.fmt[lst.size-1]='i';
		return lst;
	}else if(type=='s'||type=='S'){
		char* s = va_arg(va,char*);
		size_t len = strlen(s);
		lst.Lsize += len+1;
		lst.size++;
		lst.list = malloc(lst.Lsize);
		if(lst.list==NULL)
		{
			printf("%s\n",M_ERR);
			exit(10);
		}
		lst.fmt = malloc(lst.size);
		if(lst.fmt==NULL)
		{
			free(lst.list);
			printf("%s\n",M_ERR);
			exit(10);
		}
		strcpy(lst.fmt,a.fmt);
		for (int i = 0; i < a.Lsize; ++i)
		{
			lst.list[i]=a.list[i];
		}
		free(a.list);
		free(a.fmt);
		strncpy(lst.list+lst.Lsize-len-1,s,len);
		lst.list[lst.Lsize-1]='\0';
		lst.fmt[lst.size-1]='s';
		return lst;
	}else if(type=='d'||type=='D'){
		lst.Lsize += sizeof(double);
		lst.size++;
		lst.list = malloc(lst.Lsize);
		if(lst.list==NULL)
		{
			printf("%s\n",M_ERR);
			exit(10);
		}
		lst.fmt = malloc(lst.size);
		if(lst.fmt==NULL)
		{
			free(lst.list);
			printf("%s\n",M_ERR);
			exit(10);
		}
		strcpy(lst.fmt,a.fmt);
		for (int i = 0; i < a.Lsize; ++i)
		{
			lst.list[i]=a.list[i];
		}
		free(a.list);
		free(a.fmt);
		double ival = va_arg(va,double);
		void* vp = &ival;
		char* cp = vp;
		for (int i = sizeof(double); i > 0; --i)
		{
			lst.list[lst.Lsize-i]=cp[sizeof(double)-i];
		}
		lst.fmt[lst.size-1]='d';
		return lst;
	}else if(type=='f'){
		lst.Lsize += sizeof(double);
		lst.size++;
		lst.list = malloc(lst.Lsize);
		if(lst.list==NULL)
		{
			printf("%s\n",M_ERR);
			exit(10);
		}
		lst.fmt = malloc(lst.size);
		if(lst.fmt==NULL)
		{
			free(lst.list);
			printf("%s\n",M_ERR);
			exit(10);
		}
		strcpy(lst.fmt,a.fmt);
		for (int i = 0; i < a.Lsize; ++i)
		{
			lst.list[i]=a.list[i];
		}
		free(a.list);
		free(a.fmt);
		double ival = va_arg(va,double);
		void* vp = &ival;
		char* cp = vp;
		for (int i = sizeof(double); i > 0; --i)
		{
			lst.list[lst.Lsize-i]=cp[sizeof(double)-i];
		}
		lst.fmt[lst.size-1]='f';
		return lst;
	}else if(type=='c'){
		lst.Lsize++;
		lst.size++;
		lst.list = malloc(lst.Lsize);
		if(lst.list==NULL)
		{
			printf("%s\n",M_ERR);
			exit(10);
		}
		lst.fmt = malloc(lst.size);
		if(lst.fmt==NULL)
		{
			free(lst.list);
			printf("%s\n",M_ERR);
			exit(10);
		}
		strcpy(lst.fmt,a.fmt);
		for (int i = 0; i < a.Lsize; ++i)
		{
			lst.list[i]=a.list[i];
		}
		free(a.list);
		free(a.fmt);
		lst.list[lst.Lsize-1]=(char)va_arg(va,int);
		lst.fmt[lst.size-1]='c';
	}
	return a;
	va_end(va);
}

list lset(list a, int elem, char type, ...)
{
	list lst;
	lst.Lsize = 0;
	lst.size = 0;
	va_list va;
	va_start(va,type);
	if(a.size<elem){
		return a;
	}
	if(type=='i'||type=='I'){

	}
	va_end(va);
}

// getType functions for direct use!
// use lget() for more efficiency!

int getInt(list a, int elem)
{
	return *(int*)lget(a,elem);
}

double getDbl(list a, int elem)
{
	return *(double*)lget(a,elem);
}

float getFlt(list a,int elem)
{
	return getDbl(a,elem);
}

char* getStr(list a, unsigned int elem)
{
	return (char*)lget(a,elem);
}

char getChr(list a, int elem)
{
	return *(char*)lget(a,elem);
}

#endif