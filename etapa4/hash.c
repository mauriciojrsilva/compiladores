#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "ast.h"

#define SIZE 997

HASH_ELEMENT** hash_init() {
	int i;
	HASH_ELEMENT** hashTable = (HASH_ELEMENT**)calloc(SIZE, sizeof(HASH_ELEMENT*));
	return hashTable;	
}

HASH_ELEMENT* hashElement_create(int token, char* text) {
	int address;
	HASH_ELEMENT *element;

	element = (HASH_ELEMENT*)malloc(sizeof(HASH_ELEMENT));
	element->token = token;
	element->text = (char*)calloc(strlen(text)+1,sizeof(char));
	strcpy(element->text, text);
	element->next = 0;
	element->tipoDado = 0;
	element->count = 0;

	return element;
}

HASH_ELEMENT* hashElement_insert(HASH_ELEMENT** hashTable, HASH_ELEMENT* hashElement) {
	int address;
	HASH_ELEMENT *element;

	if (element = hash_find(hashTable, hashElement->text)) {

		return element;
	}

	address = hash_address(hashElement->text);
	hashElement->next = hashTable[address];
	hashTable[address] = hashElement;

	return hashElement;
}

HASH_ELEMENT* hash_insert(HASH_ELEMENT** hashTable, int token, char* text) {
	int address;
	HASH_ELEMENT *element;
	
	if(element = hash_find(hashTable, text))
		return element;
	
	element = (HASH_ELEMENT*)malloc(sizeof(HASH_ELEMENT));
	element->token = token;
	element->text = (char*)calloc(strlen(text)+1,sizeof(char));
	strcpy(element->text, text);
	element->next = 0;

	address = hash_address(text);
	element->next = hashTable[address];
	hashTable[address] = element;

	return element;
}

int hash_address(char *text) {
	int i;
	int address=1;
	int textlen = strlen(text);
	for(i = 0; i < textlen; ++i) {
		address = (address * text[i]) % SIZE + 1;
	}
	return address - 1;
}

HASH_ELEMENT* hash_find(HASH_ELEMENT** hashTable, char* text) {
	int address;
	HASH_ELEMENT* ret;

	address = hash_address(text);

	ret = hashTable[address];
	while(ret && strcmp(ret->text, text) != 0) ret = ret->next;

	return ret;
}

HASH_ELEMENT* hash_find_outer(AST* nodo, char* text) {
	HASH_ELEMENT* el;
	int i;
	
	for(i = 0; i < nodo->numHashTablesPai; i++) {
		if (nodo->hashTablesPai[i] == NULL) 
			break;
			
		if (el = hash_find(nodo->hashTablesPai[i], text))
			return el;
	}

	return NULL;
}

void hash_print(HASH_ELEMENT** hashTable) {
	int i;
	HASH_ELEMENT* aux;
	AST* astAux;
	for(i = 0; i < SIZE; ++i){
		aux = hashTable[i];
		while(aux != 0) {
			element_print(aux);
			aux = aux->next;
		}
	}
}

void element_print(HASH_ELEMENT* element) {
	AST* astAux = element->ast;
	printf("token: %d, tipo de dado: %d, nome: %s, count: %d, ast: %d\n", element->token, element->tipoDado, element->text, element->count, astAux->tipo);
}