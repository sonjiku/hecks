#ifndef __FILEOPSH__
#define __FILEOPSH__
							/* P R E P R O C E S S O R */
									/* HEADERS */
/*Compiler Includes*/
#include<stdio.h>
#include<ctype.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
									/* HEADERS END */
						/* P R E P R O C E S S O R   E N D */

						/* F U N C T I O N   P R O T O T Y P E S */
void flgetname (char* filename,size_t flnmsz) ;
void flopen ( FILE** fl, char* filename, char* mode ) ;
void flbytecp (FILE* ffl,FILE* sfl,long end,long start ) ;
void flvh (FILE* fl) ;
void flh2c (FILE* fl,uint8_t lit) ;
void flsize (FILE* fl) ;
void fleb (FILE* fl) ;
void flib (FILE* fl) ;
void fldb (FILE* fl,char* flnm,_Bool flag) ;
					/* F U N C T I O N   P R O T O T Y P E S   E N D */
#endif 
