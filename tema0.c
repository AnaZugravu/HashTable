//Mihai Neacsu 331CA
//SO Tema 0

#include "list.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define MAXLINE 20000

void readFromStream(Hash H, FILE *stream){
	char line[MAXLINE];
	char *token, *token2, *foutName;
	FILE *fout;
	unsigned int bucketIndex;

	memset(line, '\0', MAXLINE);

	while (fgets(line, MAXLINE, stream)){
		foutName = NULL;
		token = NULL;
		token2 = NULL;
		fout = NULL;
		bucketIndex = 0;

		//ca sa nu mai parsam in tokenuri si '\n' 
		//se inlocuieste cu '\0'
		line[strcspn(line, "\n")] = '\0';

		//sarim peste sirurile goale
		if (line[0] == '\0')
			continue;

		token = strtok(line, " \n");
		
		if (strcmp(token, "add") == 0)
			add_Hash(H, strtok(NULL, " \n"));
		else if (strcmp(token, "remove") == 0)
			remove_Hash(H, strtok(NULL, " \n"));
		else if (strcmp(token, "clear") == 0)
			clear_Hash(H);
		else if (strcmp(token, "resize") == 0){
			token = strtok(NULL, " \n");
			
			if (strcmp(token, "double") == 0)
				resizeDouble_Hash(&H);
			else
				resizeHalve_Hash(&H);
		}
		else if (strcmp(token, "print") == 0){
			foutName = strtok(NULL, " \n");

			fout = stdout;
			if (foutName){
				fout = fopen(foutName, "a");
				assert(fout);
			}
			
			print_Hash(H, fout);

			if (foutName)
				fclose(fout); 
		}
		else{
			token2 = strtok(NULL, " \n"),
			foutName = strtok(NULL, " \n");

			fout = stdout;
			if (foutName){
				fout = fopen(foutName, "a");
				assert(fout);
			}

			if (strcmp(token, "find") == 0){
				if (find_Hash(H, token2))
					fputs("True\n", fout);
				else
					fputs("False\n", fout);
			}
			else if (strcmp(token, "print_bucket") == 0){
				bucketIndex = atoi(token2);

				printBucket_Hash(H, bucketIndex, fout);
			}
			else{
				fputs("Wrong op  buddy: ", stderr);
				fputs(token, stderr);
				fputs("\n", stderr);
			}
		}

		memset(line, '\0', MAXLINE);
	}

	delete_Hash(H);
}

int main(int argc, char *argv[]){
	unsigned int hashSize;
	Hash h;
	FILE *stream;

	if (argc < 2){
		fputs("Not enough args, buddy\n", stderr);

		return 1;
	}

	hashSize = atoi(argv[1]);
	h = new_Hash(hashSize);

	if (argc == 2)
		readFromStream(h, stdin);	
	else{
		int i;
		for (i = 3; i <= argc; ++i){
			stream = fopen(argv[i - 1], "r");
			assert(stream);

			readFromStream(h, stream);
			fclose(stream);
		}
	}

	return 0;
}
