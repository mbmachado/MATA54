/**
 * The Record
 */
typedef struct record {
	char key[21];
	char content[51];
	long next;
} Record;

/**
 * Inserts a record into the primary file
 * @param char[21] key
 * @param char[51] content
 * @return long insertionPosition
 *
 */
long insertRecordIntoPrimaryFile(char key[21], char content[51]);

/**
 * Updates a record's next poiter in primary file
 * @param long lastRecordPosition
 * @param long newNextValue
 *
 */
void updatePointerInPrimaryFile(long lastRecordPosition, long newNextValue);

/**
 * Follows the chain and prints all records found in the primary file
 * @param long firstRecordPosition
 *
 */
void consultRecordsFromPrimaryFile(long firstRecordPosition);