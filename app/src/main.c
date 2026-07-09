/*
main.c - главный модуль программы. 

Хаиров Егор Вадимович
МК-101
*/

#define WrongInput() printf("Неправильный формат ввода!\n")

#include "CReplace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[], char *envp[]) {

	if(argc == 2) {
		if(strcmp(argv[1], "--version") == 0) printf("You are using CReplace v1.0 by Ego.\n"); // Вывод версии
		else if(strcmp(argv[1], "--help") == 0) printf("\
			Использование: CReplace [input.txt] [output.txt] \"[TEXT TO REPLACE]\" \"[TEXT TO REPLACE WITH]\"\n\
			[input.txt] - путь к входному файлу.\n\
			[output.txt] - путь к выходному файлу.\n\
			[TEXT TO REPLACE] - фраза которую нужно заменить.\n\
			[TEXT TO REPLACE WITH] - фраза которой нужно заменить.\n"); // Помощь в использовании
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
			printf("Не удалось открыть файл!\n");
			return 1;
		}
		replace(inputFile, outputFile, argv[3], argv[4]);
		fclose(inputFile);
		fclose(outputFile);
		printf("Программа успешно завершила работу!\n");
	} else {
		WrongInput();
		return 1;
	}

	return 0;

}
