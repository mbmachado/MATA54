#include <stdio.h>
#include <string.h>
#include "multilist.h"
#include "file.h"

void insert() {
	bool keyExists = false;
	char content[51];
	SKRecord newRecord;
	SKRecord oldRecord;
	FILE *multilist;

	scanf("%s", newRecord.key);
	scanf("%s", content);

	multilist = fopen("multilist.txt", "r+b");
	fseek(multilist, 0, SEEK_SET);

	while(fread(&oldRecord, sizeof(SKRecord), 1, multilist)) {
		if(strncmp(oldRecord.key, newRecord.key, 20) == 0 && oldRecord.isDeleted == 0) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		long position = insertRecordIntoPrimaryFile(newRecord.key, content);

		// Atualizar apontador do ex-último registro em primary file //
		updatePointerInPrimaryFile(oldRecord.lastRecord, position);

		// Atualizar valor de lastRecord do registro em multilist //
		oldRecord.lastRecord = position;
		fseek(multilist, ftell(multilist) - sizeof(SKRecord), SEEK_SET);
		fwrite(&oldRecord, sizeof(SKRecord), 1, multilist);
	} else {
		long position = insertRecordIntoPrimaryFile(newRecord.key, content);

		newRecord.firstRecord = position;
	 	newRecord.lastRecord = position;
	 	newRecord.isDeleted = 0;

	 	fseek(multilist, 0, SEEK_END);
		fwrite(&newRecord, sizeof(SKRecord), 1, multilist);
	}

	fclose(multilist);
}

void remove() {
	bool keyExists = false;
	SKRecord record;
	char key[21];
	FILE *multilist;

	scanf("%s", key);

	multilist = fopen("multilist.txt", "r+b");
	fseek(multilist, 0, SEEK_SET);

	while(fread(&record, sizeof(SKRecord), 1, multilist)) {
		if(strncmp(record.key, key, 20) == 0 && record.isDeleted == 0) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		record.isDeleted = 1;
		fseek(multilist, ftell(multilist) - sizeof(SKRecord), SEEK_SET);
		fwrite(&record, sizeof(SKRecord), 1, multilist);
	}

	fclose(multilist);
}

void consult() {
	bool keyExists = false;
	SKRecord record;
	char key[21];
	FILE *multilist;

	scanf("%s", key);

	multilist = fopen("multilist.txt", "rb");
	fseek(multilist, 0, SEEK_SET);

	while(fread(&record, sizeof(SKRecord), 1, multilist)) {
		if(strncmp(record.key, key, 20) == 0 && record.isDeleted == 0) {
			keyExists = true;
			break;
		}
	}

	fclose(multilist);

	if(keyExists) {
		consultRecordsFromPrimaryFile(record.firstRecord);
	}
}
