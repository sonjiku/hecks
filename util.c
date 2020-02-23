#include "util.h"





/*Flush the input buffer*/
void flsh () {
	char t;
	do{
		t=getchar();
	} while ( t != '\n');
}





/*Get yes or no input*/
int ynfun () {
	char t;
	printf("(y/n) ");
	do{
		t=getchar();
		flsh ();
	} while ( t != 'y' && t != 'Y' && t != 'n' && t != 'N' );
	if ( t == 'n' || t == 'N' ) {
		return 0;
	} else if ( t == 'y' || t == 'y' ) {
		return 1;
	} else {
		puts("Weird thing happened. Now you are gonna die.");
		return 2;
	}
}
