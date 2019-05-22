#include <stdio.h>
#include "multilist.h"
#include "file.h"

void insert() {
	bool keyExists = false;
	char key[21];
	char content[51];
	SKRecord newRecord;
	SKRecord oldRecord;
	FILE *multilist;

	scanf(" %[^\n]s", key);
	scanf(" %[^\n]s", content);

	multilist = fopen("multilist.txt", "a+b");
	fseek(multilist, 0 * sizeof(SKRecord), SEEK_SET);

	while(fread(&oldRecord, sizeof(SKRecord), 1, multilist)) {
		if(oldRecord.key == key && !oldRecord.isDeleted) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		long int position = insertRecordInPrimaryFile(key, content);

		// Atualizar apontador do ex-último registro em primary file //
		updatePointerInPrimaryFile(oldRecord.lastRecord, position);

		// Atualizar valor de lastRecord do registro em multilist //
		oldRecord.lastRecord = position;
		fseek(multilist, ftell(multilist) - sizeof(SKRecord), SEEK_SET);
		fwrite(&oldRecord, sizeof(SKRecord), 1, multilist); 
	} else {
		long int position =  insertRecordInPrimaryFile(key, content);

		newRecord.key[21] = key[21];
		newRecord.firstRecord = position;
	 	newRecord.lastRecord = position;
	 	newRecord.isDeleted = false;		

		fwrite(&newRecord, sizeof(SKRecord), 1, multilist); 
	}

	fclose(multilist);
}

void remove() {
	bool keyExists = false;
	SKRecord record;
	char key[21];
	FILE *multilist;

	scanf(" %[^\n]s", key);

	multilist = fopen("multilist.txt", "r+b");
	fseek(multilist, 0 * sizeof(SKRecord), SEEK_SET);

	while(fread(&record, sizeof(SKRecord), 1, multilist)) {
		if(record.key == key && !record.isDeleted) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		record.isDeleted = true;
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

	scanf(" %[^\n]s", key);

	multilist = fopen("multilist.txt", "rb");
	fseek(multilist, 0 * sizeof(SKRecord), SEEK_SET);

	while(fread(&record, sizeof(SKRecord), 1, multilist)) {
		if(record.key == key && !record.isDeleted) {
			keyExists = true;
			break;
		}
	}

	if(keyExists) {
		consultRecordsInPrimaryFile(record.firstRecord);
	}
	
	fclose(multilist);	
}