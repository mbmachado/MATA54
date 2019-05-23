#include <stdio.h>
#include <string.h>
#include "file.h"

long insertRecordIntoPrimaryFile(char key[21], char content[51]) {
	long position;
	Record record;
	FILE *file;

	strncpy(record.key, key, 21);
	strncpy(record.content, content, 51);
	record.next = -1;

	file = fopen("file.txt", "a+b");
	fwrite(&record, sizeof(Record), 1, file);
	position = ftell(file) - sizeof(Record);
	fclose(file);

	return position;
}

void updatePointerInPrimaryFile(long lastRecordPosition, long newNextValue) {
	FILE *file;
	Record record;

	file = fopen("file.txt", "r+b");
	fseek(file, lastRecordPosition, SEEK_SET);
	fread(&record, sizeof(Record), 1, file);

	record.next = newNextValue;

	fseek(file, lastRecordPosition, SEEK_SET);
	fwrite(&record, sizeof(Record), 1, file);
	fclose(file);
}

void consultRecordsFromPrimaryFile(long firstRecordPosition) {
	Record record;
	FILE *file;

	file = fopen("file.txt", "rb");
	fseek(file, firstRecordPosition, SEEK_SET);

	while(true) {
		fread(&record, sizeof(Record), 1, file);
		printf("%s %s\n", record.key, record.content);

		if (record.next == -1) {
			break;
		}

		fseek(file, record.next, SEEK_SET);
	}

	fclose(file);
}
