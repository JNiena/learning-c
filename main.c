#include <stdio.h>
#include <stdlib.h>

void printString(char* string);
void printCharacter(char character);
void printStringLine(char* string);
char* concatenate(char* firstString, char* secondString);
char* substring(char* string, size_t start, size_t end);
size_t stringLength(char* string);
size_t trueStringLength(char* string);

int main() {
  char firstString[] = "The first string. ";
  char secondString[] = "The second string.";
  char* thirdString = concatenate(firstString, secondString);
  printStringLine(thirdString);
	char* fourthString = substring(thirdString, 0, 14);
	printStringLine(fourthString);
	free(thirdString);
	free(fourthString);
}

void printString(char* string) {
	for (size_t i = 0; *(string + i) != '\0'; i++) {
		printCharacter(*(string + i)); 
	}
}

void printCharacter(char character) {
	printf("%c", character);
}

void printStringLine(char* string) {
	printString(string);
	printCharacter('\n');
}

char* concatenate(char* firstString, char* secondString) {
	char* newString = malloc(sizeof(char) * (stringLength(firstString) + stringLength(secondString) + 1));
	size_t i;
	for (i = 0; *(firstString + i) != '\0'; i++) {
	    *(newString + i) = *(firstString + i);
	}
	size_t j;
	for (j = 0; *(secondString + j) != '\0'; j++) {
	    *(newString + i + j) = *(secondString + j);
  }
	*(newString + i + j + 1) = '\0';
	return newString;
}

char* substring(char* string, size_t start, size_t end) {
	char* newString = malloc(sizeof(char) * (stringLength(string) + start - end));
	size_t j = 0;
	for (size_t i = start; *(string + i) != '\0' && i < end; i++) {
	    *(newString + j) = *(string + i);
	    j++;
	}
	*(newString + j + 1) = '\0';
	return newString;
}

size_t stringLength(char* string) {
	size_t length = 0;
	while (*(string + length) != '\0') {
	    length ++;
	}
	return length;
}

size_t trueStringLength(char* string) {
	return stringLength(string) + 1;
}
