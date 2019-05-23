#include <stdio.h>
#include <string.h>
#include "multilist.h"
#include "file.h"

void insert() {
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
            long position = insertRecord(newRecord.key, content);

            // Atualizar apontador do ex-último registro em primary file //
            updatePointer(oldRecord.lastRecord, position);

            // Atualizar valor de lastRecord do registro em multilist //
            oldRecord.lastRecord = position;
            fseek(multilist, ftell(multilist) - sizeof(SKRecord), SEEK_SET);
            fwrite(&oldRecord, sizeof(SKRecord), 1, multilist);
        } else {
            long position = insertRecord(newRecord.key, content);

            newRecord.firstRecord = position;
            newRecord.lastRecord = position;
            newRecord.isDeleted = 0;

            fseek(multilist, 0, SEEK_END);
            fwrite(&newRecord, sizeof(SKRecord), 1, multilist);
        }
        break;
    }

    fclose(multilist);
}

void remove() {
    SKRecord record;
    char key[21];
    FILE *multilist;

    scanf("%s", key);

    multilist = fopen("multilist.txt", "r+b");
    fseek(multilist, 0, SEEK_SET);

    while(fread(&record, sizeof(SKRecord), 1, multilist)) {
        if(strncmp(record.key, key, 20) == 0 && record.isDeleted == 0) {
            record.isDeleted = 1;
            fseek(multilist, ftell(multilist) - sizeof(SKRecord), SEEK_SET);
            fwrite(&record, sizeof(SKRecord), 1, multilist);
            break;
        }
    }

    fclose(multilist);
}

void consult() {
    SKRecord record;
    char key[21];
    FILE *multilist;

    scanf("%s", key);

    multilist = fopen("multilist.txt", "rb");
    fseek(multilist, 0, SEEK_SET);

    while(fread(&record, sizeof(SKRecord), 1, multilist)) {
        if(strncmp(record.key, key, 20) == 0 && record.isDeleted == 0) {
            consultRecords(record.firstRecord);
            break;
        }
    }

    fclose(multilist);
}
