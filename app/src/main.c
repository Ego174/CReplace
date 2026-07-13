/*
main.c - главный модуль программы. 

Хаиров Егор Вадимович
МК-101
*/

#define WrongInput() printf("Wrong input format!\n")

#include "CReplace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {

	if(argc == 2) {
		if(strcmp(argv[1], "--version") == 0) printf("You are using CReplace v1.0 by Ego.\n"); // Вывод версии
		else if(strcmp(argv[1], "--help") == 0) printf("\
Usage: replace [input.txt] [output.txt] \"[BYTES TO REPLACE]\" \"[BYES TO REPLACE WITH]\"\n\
[input.txt] - input file path.\n\
[output.txt] - output file path.\n\
[BYTES TO REPLACE] - bytes to replace.\n\
[BYTES TO REPLACE WITH] - bytes to replace with.\n\
Bytes must be entered in hex format.\n"); // Помощь в использовании
		else {
			WrongInput();
			return 1;
		}
	} else if(argc == 5) {
		FILE *inputFile = fopen(argv[1], "r"); // Запуск основного функционала
		FILE *outputFile = fopen(argv[2], "w");
		if(!inputFile | !outputFile) {
			if(inputFile) fclose(inputFile);
			if(outputFile) fclose(outputFile);
			printf("Can't open file!\n");
			return 1;
		}
		replace(inputFile, outputFile, argv[3], argv[4]);
		fclose(inputFile);
		fclose(outputFile);
		printf("Success!\n");
	} else {
		WrongInput();
		return 1;
	}

	return 0;

}
