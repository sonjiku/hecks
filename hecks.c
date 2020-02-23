#include"util.h"
#include"fileops.h"

int main ( void ) {
	FILE* fl;
	FILE** flp=&fl;
	char flnm[50];
	char opt;
	int rn=0;
	printf("#############################################################################\n");
	printf("#############################################################################\n");
	printf("#############################################################################\n");
	printf("####### ######################################### ###########################\n");
	printf("####### ##############     #########     ######## ####  ########     ########\n");
	printf("####### #    ######## ##### ####### ##### ####### ##  ######### #############\n");
	printf("#######  #### #######       ####### #############   ############     ########\n");
	printf("####### ##### ####### ############# ##### ####### ##  ############### #######\n");
	printf("####### ##### ########     #########     ######## ####  ########     ########\n");
	printf("#############################################################################\n");
	printf("#############################################################################\n");
	printf("#############################################################################\n");
	printf("+---------------------------------------------------------------------------+\n");
	printf("|                            A Simple Hex Editor                            |\n");
	puts("+---------------------------------------------------------------------------+");
	puts("\nBEWARE! Any and all actions you take will take effect immediately!");
	puts("Be careful when editing important files, don't do anything you are not sure");
	puts("about, and always backup!");
	printf("\nEnter 'h' for help!");
	do {
		printf("\n\nOption: ");
		do{
			opt = getchar();
			if ( rn==0 && ( opt != '\n' && opt != 'N' && opt != 'o' && opt != 'O' && opt != 'q' && opt != 'Q' && opt != 'h' && opt != 'h' )) {
				fprintf(stderr,"You haven't opened a file yet.\a\n");
				printf("\n\nOption: ");
				opt='\n';
			} else if ( opt == 'q' || opt == 'Q' ) {
				printf("Exiting...\a\n");
				return 0;
			}
		} while ( opt == '\n');
		flsh ();
		if ( opt == 'c' ) {
			flh2c(fl, 0);
		} else if ( opt == 'C') {
			flh2c(fl, 1);
		} else if ( opt == 'd' ) {
			fldb(fl,flnm,0);
		} else if ( opt == 'D' ) {
			fldb(fl,flnm,1);
		} else if ( opt == 'e') {
			fleb(fl);
		} else if ( opt == 'E' ) {
			fleb(fl);
		} else if ( opt == 'h' || opt == 'H' ) {
			printf("Help\n");
			printf("------------------------------\n");
			printf("c: View the current file with the printable values in asci form.\n");
			printf("C: View the current file with all the values up to 128 in asci form.\n");
			printf("d: Remove a byte.\n");
			printf("D: Remove from byte.\n");
			printf("e: Edit the current file.\n");
			printf("h: View this help.\n");
			printf("i: Insert values after a certain byte.\n");
			printf("n: Create new file.\n");
			printf("o: Open file.\n");
			printf("q: Quit hecks.\n");
			printf("s: View the size of the current file.\n");
			printf("v: View the current file.\n");
		} else if ( opt == 'i' || opt == 'I' ) {
			flib(fl);
		} else if ( opt == 'n' || opt == 'N' ) {
			if ( rn != 0  ) {
				fclose(fl);
			}
			flgetname(flnm,sizeof flnm);
			flopen(flp,flnm,"wb");
			freopen(flnm,"rb+",fl);
			flvh(fl);
			rn++;
		} else if ( opt == 'o' || opt == 'O' ) {
			if ( rn != 0  ) {
				fclose(fl);
			}
			flgetname(flnm,sizeof flnm);
			flopen(flp,flnm,"rb+");
			flvh(fl);
			rn++;
		} else if ( opt == 'v' || opt == 'V' ) {
			flvh(fl);
		} else if ( opt == 'q' || opt == 'Q' ) {
			printf("Exiting...");
		} else if ( opt == 's' || opt == 'S' ) {
			flsize(fl);
		} else {
			fprintf(stderr,"Not valid option: %c", opt);
		}
	} while ( opt != 'q' && opt != 'Q' );
	fclose(fl);
	return 0;
}

