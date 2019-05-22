#include <stdio.h>
#include "file.h"

void insert() {
	bool keyExists = false;
	Person oldPerson;
	Person newPerson;
	FILE *file;

	scanf("%i", &newPerson.key);
	scanf(" %[^\n]s", newPerson.name);
	scanf("%i", &newPerson.age);

	file = fopen("file.txt", "a+b");
	fseek(file, 0 * sizeof(Person), SEEK_SET);

	while(fread(&oldPerson, sizeof(Person), 1, file)) {
		if(oldPerson.key == newPerson.key) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		printf("registro com chave existente\n");
	} else {
		fwrite(&newPerson, sizeof(Person), 1, file); 
	}

	fclose(file);
}

void remove() {
	bool keyExists = false;
	Person person;
	unsigned int key;
	FILE *file;

	scanf("%i", &key);

	file = fopen("file.txt", "r+b");
	fseek(file, 0 * sizeof(Person), SEEK_SET);

	while(fread(&person, sizeof(Person), 1, file)) {
		if(person.key == key) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		person.key = -1;
		fseek(file, ftell(file) - sizeof(Person), SEEK_SET);
		fwrite(&person, sizeof(Person), 1, file); 
	} else {
		printf("nao existe registro com chave: %i\n", key);
	}
	
	fclose(file);	
}

void consult() {
	bool keyExists = false;
	Person person;
	unsigned int key;
	FILE *file;

	scanf("%i", &key);

	file = fopen("file.txt", "rb");
	fseek(file, 0 * sizeof(Person), SEEK_SET);

	while(fread(&person, sizeof(Person), 1, file)) {
		if(person.key == key) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		printf("chave: %i %s %i\n", person.key, person.name, person.age);
	} else {
		printf("nao ha registro com chave: %i\n", key);
	}
	
	fclose(file);	
}

void printAll() {
	Person person;
	FILE *file;

	file = fopen("file.txt", "rb");
	fseek(file, 0 * sizeof(Person), SEEK_SET);

	while(fread(&person, sizeof(Person), 1, file)) {
		if(person.key != -1) {
			printf("chave: %i | nome: %s | idade: %i\n", person.key, person.name, person.age);
		}
	}

	fclose(file);
}