#include <stdio.h>
#include "multilist.h"

void insert() {
	bool keyExists = false;
	char[21] key;
	char[51] content;
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
		int line =  insertRecordInPrimaryFile(key, content);
		
		// Atualizar apontador do ex-último registro em primary file
		updatePointerInPrimaryFile(oldRecord.lastRecord, line);

		// Atualizar valor de lastRecord do registro na multilista
		oldRecord.lastRecord = line;
		fseek(multilist, ftell(multilist) - sizeof(SKRecord), SEEK_SET);
		fwrite(&oldRecord, sizeof(SKRecord), 1, multilist); 
	} else {
		int line =  insertRecordInPrimaryFile(key, content);

		newRecord.key = key;
		newRecord.firstRecord = line;
	 	newRecord.lastRecord = line;
	 	newRecord.isDeleted = false;		

		fwrite(&newRecord, sizeof(SKRecord), 1, multilist); 
	}

	fclose(multilist);
}

void remove() {
	bool keyExists = false;
	SKRecord record;
	char[21] key;
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
	char[21] key;
	FILE *multilist;

	scanf("%i", &key);

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