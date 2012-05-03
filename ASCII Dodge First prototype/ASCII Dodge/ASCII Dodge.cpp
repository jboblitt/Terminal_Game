#include "ASCII Dodge.h"

// 0 is a space, 1 is for a star and 2 for an X
void print_line( int* line)
{
	for(int i=0;i<80;i++)
	{
		if(line[i]==0) cout<<" "; 
		if(line[i]==1) cout<<"*";
		if(line[i]==2) cout<<"X";
	}
}