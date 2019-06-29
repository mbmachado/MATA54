#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
const char *FILE_NAME = "entradas/dados1";

using namespace std;

/**
 * The Record
 */
typedef struct record {
    char key[21];
    char content[51];
    long next;
} Record;

/**
 * The Secondary Key Record
 */
typedef struct sk {
    char key[21];
    long firstRecord;
    long lastRecord;
    short isDeleted;
} SKRecord;

/**
 * Inserts a record into the primary file
 * @param char[21] key
 * @param char[51] content
 * @return long insertionPosition
 *
 */
long insertRecord(char key[21], char content[51]) {
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

/**
 * Updates a record's next pointer in primary file
 * @param long lastRecordPosition
 * @param long newNextValue
 *
 */
void updatePointer(long lastRecordPosition, long newNextValue) {
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

/**
 * Inserts a secondary key record into multilist file
 *
 */
void initializeDataBase(Record record) {
    bool keyExists = false;
    char content[51];
    SKRecord newRecord;
    SKRecord oldRecord;
    FILE *multilist;

    strncpy(newRecord.key, record.key, 21);
    strncpy(content, record.content, 51);

    multilist = fopen("multilist.txt", "r+b");
    fseek(multilist, 0, SEEK_SET);

    while(fread(&oldRecord, sizeof(SKRecord), 1, multilist)) {
        if(strncmp(oldRecord.key, newRecord.key, 20) == 0 && oldRecord.isDeleted == 0) {
            keyExists = true;
            break;
        }
    }

    if(keyExists) {
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

    fclose(multilist);
}

/**
 * Splits a string by given delimiter
 * @param string line
 * @return Record
 *
 */
Record explode(string line) {
    istringstream iss(line);
    Record record;

    iss.getline(record.key, 21, ',');
    iss.getline(record.content, 51, ',');

    return record;
}

int main(int argc, char const *argv[]) {
    ifstream file;
    string line;

    file.open(FILE_NAME);
    while(getline(file, line)) {
        initializeDataBase(explode(line));
    }
    file.close();

    return 0;
}
