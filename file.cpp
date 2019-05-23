#include <stdio.h>
#include "file.h"

long int insertRecordInPrimaryFile(char key[21], char content[51]) {
	long int position;
	Record record;
	FILE *file;

	record.key[21] = key[21];
	record.content[51] = content[51];
	record.next = -1;

	file = fopen("file.txt", "a+b");
	fwrite(&record, sizeof(Record), 1, file); 
	position = ftell(file);
	fclose(file);

	return position;
}

void updatePointerInPrimaryFile(long int lastRecordPosition, long int newNextValue) {
	FILE *file;
	Record record;

	file = fopen("file.txt", "r+b");
	fseek(file, lastRecordPosition, SEEK_SET);
	fread(&record, sizeof(Record), 1, file);

	record.next = newNextValue;

	fwrite(&record, sizeof(Record), 1, file);
	fclose(file);
}

void consultRecordsInPrimaryFile(long int firstRecordPosition) {
	Record record;
	FILE *file;

	file = fopen("file.txt", "rb");
	fseek(file, firstRecordPosition, SEEK_SET);

	do {
		fread(&record, sizeof(Record), 1, file);
		fseek(file, record.next, SEEK_SET);
		printf("%s %s\n", record.key, record.content);
	} while(record.next != -1);

	fclose(file);
}