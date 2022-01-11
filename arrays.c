#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define terminator '\a'
#define filler '-'

char* arrayInitialize(size_t length);
size_t arrayLength(char* array);
void arrayPrint(char* array);

void arrayIncreaseLength(char* array, size_t amount);
void arrayDecreaseLength(char* array, size_t amount);

void arraySet(char* array, size_t index, char character);
void arraySetAll(char* array, char character);

char arrayGet(char* array, size_t index);

void arrayAdd(char* array, char character);
void arrayAddAt(char* array, size_t index, char character);

void arrayRemove(char* array, char character);
void arrayRemoveAt(char* array, size_t index);

size_t arrayIndexOf(char* array, char character);
bool arrayContains(char* array, char character);


int main() {
	char* array = arrayInitialize(0);

	arrayAdd(array, 'a');
	arrayAdd(array, 'b');
	arrayAdd(array, 'c');
	arrayAdd(array, 'd');
	arrayAdd(array, 'e');
	arrayAdd(array, 'f');
	arrayAdd(array, 'g');
	arrayAdd(array, 'h');
	arrayPrint(array);

	arrayAddAt(array, 3, 'q');
	arrayPrint(array);

	arrayAddAt(array, 3, 'q');
        arrayPrint(array);

	arrayAddAt(array, 3, 'q');
        arrayPrint(array);

	arrayAddAt(array, 3, 'q');
        arrayPrint(array);

	arrayAddAt(array, 3, 'q');
        arrayPrint(array);

	arrayRemove(array, 'q');
	arrayPrint(array);


	free(array);
}

char* arrayInitialize(size_t length) {
	char* array = malloc(sizeof(char) * (length + 1));
	*(array + length) = terminator;
	arraySetAll(array, filler);
	return array;
}

size_t arrayLength(char* array) {
        size_t length = 0;
        while (*(array + length) != terminator) {
                length++;
        }
        return length;
}

void arrayPrint(char* array) {
	printf("Length: %zu | Elements: %s\n", arrayLength(array), array);
}

void arrayIncreaseLength(char* array, size_t amount) {
        size_t length = arrayLength(array);
        realloc(array, sizeof(char) * (length + amount + 1));
	*(array + length) = filler;
        *(array + length + amount) = terminator;
}

void arrayDecreaseLength(char* array, size_t amount) {
        size_t length = arrayLength(array);
        realloc(array, sizeof(char) * (length - amount + 1));
        *(array + length - amount) = terminator;
}


void arraySet(char* array, size_t index, char character) {
	if (index < arrayLength(array)) {
		*(array + index) = character;
	}
}

void arraySetAll(char* array, char character) {
	for (size_t i = 0; i < arrayLength(array); i++) {
		arraySet(array, i, character);
	}
}

char arrayGet(char* array, size_t index) {
        if (index < arrayLength(array)) {
                return *(array + index);
        }
        return NULL;
}

void arrayAdd(char* array, char character) {
	arrayIncreaseLength(array, 1);
	arraySet(array, arrayLength(array) - 1, character);
}

void arrayAddAt(char* array, size_t index, char character) { 
        arrayIncreaseLength(array, 1);
	for (size_t i = arrayLength(array) - 1; i >= index; i--) {
		arraySet(array, i, arrayGet(array, i - 1));
	}
	arraySet(array, index, character);
}

void arrayRemove(char* array, char character) {
        while (arrayContains(array, character)) {
                arrayRemoveAt(array, arrayIndexOf(array, character));
        }
}


void arrayRemoveAt(char* array, size_t index) {
	for (size_t i = index; i < arrayLength(array); i++) {
		arraySet(array, i, arrayGet(array, i + 1));
	}
	arrayDecreaseLength(array, 1);
}

size_t arrayIndexOf(char* array, char character) {
	for (size_t i = 0; i < arrayLength(array); i++) {
		if (arrayGet(array, i) == character) {
			return i;
		}
	}
	return NULL;
}

bool arrayContains(char* array, char character) {
	for (size_t i = 0; i < arrayLength(array); i++) {
		if (arrayGet(array, i) == character) {
			return true;
		}
	}
	return false;
}
