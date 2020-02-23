#include "fileops.h"
#include "util.h"





/* Get a filename. Basically clear the \n at the end of a string. Could use
 * a fget */
void flgetname (char* filename,size_t flnmsz) {
	printf ("Path: ");
	fgets(filename,flnmsz-1,stdin);
	int c;
	for ( c=0;c<flnmsz-1; c++ ) {
		if ( filename[c] == '\n' ) {
			filename[c]='\0';
		}
	}
}





/* Open a file and report if succeded or not. */
void flopen ( FILE** fl, char* filename, char* mode ) {
	if ( (*fl = fopen(filename,mode))== NULL ) {
		fprintf(stderr,"Failed to open file \"%s\"\n",filename);
		exit (EXIT_FAILURE);
	}
	printf("\"%s\" opened successfully\n\n",filename);
}




/* Copy a file into another up to a certain byte. */
void flbytecp (FILE* ffl,FILE* sfl,long end,long start ) {
	uint8_t data;
	if ( start>end  ) {
		printf ("Starting byte comes later than end byte. Try switching their values.");

	} else {
		rewind(ffl);
		rewind(sfl);
		while ( fread(&data,sizeof(uint8_t),1,ffl)==1 && (start)<=(end) ) {
			fwrite(&data,sizeof(uint8_t), 1,sfl);
			start++;
			fseek(ffl,start,SEEK_SET);
			fseek(sfl,start,SEEK_SET);
		}
	}
}





/* Print a matrix of the contents of a file in hex format and the size of the
 * file in bytes. */
void flvh (FILE* fl) {
	rewind(fl);
	long int sz=0;
	int x=0;
	int y;
	uint8_t dt;
	printf("        ");
	for ( y=0; y<16; y++  ) {
		printf(" x%X",y);
	}
	while (fread(&dt,sizeof(uint8_t),1,fl)==1){
		if ( sz%16==0) {
			printf("\n%07X", x);
			printf("x");
			x++;
		}
		printf(" %02hhX",dt);
		sz++;
	}
	printf("\n+------------------------------------------------------+");
	printf("\n|  Size of file is %8ld B                          |", sz);
	printf("\n+------------------------------------------------------+");
	puts("");
}





/* Get the size of file and print it in Bytes, Kilobytes, and Megabytes. */
void flsize (FILE* fl) {
	rewind(fl);
	long int sz=0;
	uint8_t dt;
	while (fread(&dt,sizeof(uint8_t),1,fl)==1){
		sz++;
	}
	printf("\n+------------------------------------------------------+");
	printf("\n|                     Size of file                     |");
	printf("\n+------------------------------------------------------+");
	printf("\n|  *    %8ld  B                                    |", sz);
	printf("\n|  *    %8ld KB                                    |", sz/1024);
	printf("\n|  *    %8ld MB                                    |", sz/1048576);
	printf("\n+------------------------------------------------------+");
	puts("");
}





/* View contents of file in ascii form. If full is 1, view the first 128 values
 * of a byte with their ascii prints or names. Else, print only the printable 
 * characters in non-hex form. */
void flh2c (FILE* fl,uint8_t full) {
	rewind(fl);
	long int sz=0;
	int x=0;
	int y;
	uint8_t dt;
	printf("        ");
	if (  full == 0  ) {
		for ( y=0; y<16; y++  ) {
			printf(" x%X",y);
		}
	} else {
		for ( y=0; y<16; y++  ) {
			printf(" xx%X",y);
		}
	}
	while (fread(&dt,sizeof(uint8_t),1,fl)==1){
		if ( sz%16==0) {
			printf("\n%07X", x);
			printf("x");
			x++;
		}
		if ( full == 0 ) {
			if ( (isgraph(dt)==0) ){
				printf(" %02hhX",dt);
			} else {
				printf("  %c",(unsigned char)dt);
			}
		} else {
			if ( dt == 0x00 ) {
				printf(" NUL");
			} else if ( dt == 0x01 ) {
				printf(" SOH");
			} else if ( dt == 0x02 ) {
				printf(" STX");
			} else if ( dt == 0x03 ) {
				printf(" ETX");
			} else if ( dt == 0x04 ) {
				printf(" EOT");
			} else if ( dt == 0x05 ) {
				printf(" ENQ");
			} else if ( dt == 0x06 ) {
				printf(" ACK");
			} else if ( dt == 0x07 ) {
				printf(" BEL");
			} else if ( dt == 0x08 ) {
				printf("  BS");
			} else if ( dt == 0x09 ) {
				printf(" TAB");
			} else if ( dt == 0x0A ) {
				printf("  LF");
			} else if ( dt == 0x0B ) {
				printf("  VT");
			} else if ( dt == 0x0C ) {
				printf("  FF");
			} else if ( dt == 0x0D ) {
				printf("  CR");
			} else if ( dt == 0x0E ) {
				printf("  SO");
			} else if ( dt == 0x0F ) {
				printf("  SI");
			} else if ( dt == 0x10 ) {
				printf(" DLE");
			} else if ( dt == 0x11 ) {
				printf(" DC1");
			} else if ( dt == 0x12 ) {
				printf(" DC2");
			} else if ( dt == 0x13 ) {
				printf(" DC3");
			} else if ( dt == 0x14 ) {
				printf(" DC4");
			} else if ( dt == 0x15 ) {
				printf(" NAK");
			} else if ( dt == 0x16 ) {
				printf(" SYN");
			} else if ( dt == 0x17 ) {
				printf(" ETB");
			} else if ( dt == 0x18 ) {
				printf(" CAN");
			} else if ( dt == 0x19 ) {
				printf("  EM");
			} else if ( dt == 0x1A ) {
				printf(" SUB");
			} else if ( dt == 0x1B ) {
				printf(" ESC");
			} else if ( dt == 0x1C ) {
				printf("  FS");
			} else if ( dt == 0x1D ) {
				printf("  GS");
			} else if ( dt == 0x1E ) {
				printf("  RS");
			} else if ( dt == 0x1F ) {
				printf("  US");
			} else if ( dt == 0x20 ) {
				printf("    ");
			} else if ( dt == 0x7F ) {
				printf(" DEL");
			} else if ( dt > 0x20 && dt < 0x7F ) {
				printf("   %c",(unsigned char)dt);
			}
		}
		sz++;
	}
	puts("");
}





/* Change the value of a byte in an open file, to a hexadecimal value. Loops,
 * everytime going to the next byte until the value of 0x0 is given and the 
 * client inputs 'n' to a yes or no prompt about wanting to continue editing.
 * If 'n', then the current byte isn't changed to 0 and the loop stops. If 'y',
 * the loop continues and the value of the current byte is changed to 0x0 */
void fleb (FILE* fl) {
	long byte;
	uint8_t dt;
	int yn=1;
	rewind(fl);
	printf("Byte address: ");
	scanf("%lx", &byte);
	flsh ();
	do {
		fseek(fl,byte,SEEK_SET);
		printf("New value for byte #%08lX: ",byte);
		scanf("%hhx", &dt);
		flsh ();
		if ( dt == 0  ) {
			printf("Do you want to change value of #%08lX to 0 ?",byte);
			yn=ynfun();
			if ( yn == 1 ) {
				fwrite(&dt,sizeof(uint8_t), 1,fl);
				flvh(fl);
			} 
		} else {
			fwrite(&dt,sizeof(uint8_t), 1,fl);
			flvh(fl);
		}
		byte++;
	} while ( yn == 1 );
}





/* Inserts a sequence of bytes, like in the above function, between two type adresses. */
void flib (FILE* fl) {
	long byte;
	long cyte=0;
	uint8_t dt;
	int yn=1;
	FILE* tmpfl;
	if ( (tmpfl = tmpfile())== NULL ) {
		fprintf(stderr,"Failed to open a temp file\n");
		exit (EXIT_FAILURE);
	}
	printf("Byte address: ");
	scanf("%lx", &byte);
	flsh ();
	rewind(fl);
	while ( fread(&dt,sizeof(uint8_t),1,fl)==1 && cyte<byte ) {
		fseek(tmpfl,cyte,SEEK_SET);
		fwrite(&dt,sizeof(uint8_t), 1,tmpfl);
		cyte++;
		fseek(fl,cyte,SEEK_SET);
	}
	fseek(fl,byte,SEEK_SET);
	do {
		fseek(tmpfl,cyte,SEEK_SET);
		printf("#%08lX: ",cyte);
		scanf("%hhx", &dt);
		flsh ();
		if ( dt == 0  ) {
			printf("Do you want to change value of #%08lX to 0 ?",cyte);
			yn=ynfun();
			if ( yn == 1 ) {
				fwrite(&dt,sizeof(uint8_t), 1,tmpfl);
				cyte++;
			} 
		} else {
			fwrite(&dt,sizeof(uint8_t), 1,tmpfl);
			cyte++;
		}
	} while ( yn == 1 );
	while ( fread(&dt,sizeof(uint8_t),1,fl)==1 ) {
		fseek(tmpfl,cyte,SEEK_SET);
		fwrite(&dt,sizeof(uint8_t), 1,tmpfl);
		cyte++;
		fseek(fl,byte,SEEK_SET);
		byte++;
	}
	cyte=0;
	rewind(tmpfl);
	rewind(fl);
	while ( fread(&dt,sizeof(uint8_t),1,tmpfl)==1 ) {
		fwrite(&dt,sizeof(uint8_t), 1,fl);
		cyte++;
		fseek(tmpfl,cyte,SEEK_SET);
		fseek(fl,cyte,SEEK_SET);
	}
	fclose(tmpfl);
}




/* Removes a single byte from a file, or all bytes from a point up until the EOF, depending on *flag* */
void fldb (FILE* fl,char* flnm, _Bool flag) {
	long byte;
	long cyte=0;
	uint8_t dt;
	FILE* tmpfl;

	if ( (tmpfl = tmpfile())== NULL ) {
		fprintf(stderr,"Failed to open a temp file\n");
		exit (EXIT_FAILURE);
	}
	printf("Byte address: ");
	scanf("%lx", &byte);
	flsh ();
	rewind(fl);
	rewind(tmpfl);
	while ( fread(&dt,sizeof(uint8_t),1,fl)==1 && cyte<byte ) {
		fwrite(&dt,sizeof(uint8_t), 1,tmpfl);
		cyte++;
		fseek(fl,cyte,SEEK_SET);
		fseek(tmpfl,cyte,SEEK_SET);
	}
	if ( flag == 0 ) {
		fseek(fl,++cyte,SEEK_SET);
		while ( fread(&dt,sizeof(uint8_t),1,fl)==1 ) {
			fwrite(&dt,sizeof(uint8_t), 1,tmpfl);
			fseek(tmpfl,cyte,SEEK_SET);
			cyte++;
			fseek(fl,cyte,SEEK_SET);
		}
	} else if ( flag == 1 ) {
	} else {
		printf("Illegal flag.");
		exit (EXIT_FAILURE);
	}
	freopen(flnm,"wb",fl);
	cyte=0;
	rewind(tmpfl);
	rewind(fl);
	while ( fread(&dt,sizeof(uint8_t),1,tmpfl)==1 ) {
		fwrite(&dt,sizeof(uint8_t), 1,fl);
		cyte++;
		fseek(tmpfl,cyte,SEEK_SET);
		fseek(fl,cyte,SEEK_SET);
	}
	fclose(tmpfl);
	freopen(flnm,"rb+",fl);
}
