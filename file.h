/**
 * The Record
 */
typedef struct record {
	char key[21];
	char content[51];
	long next;
} Record;

/**
 * Inserts a record in primary file
 * @param char[21] key
 * @param char[51] content
 * @return long insertionPosition
 *
 */
long insertRecordInPrimaryFile(char key[21], char content[51]);

/**
 * Updates a record's next poiter in primary file
 * @param long lastRecordPosition
 * @param long newNextValue
 *
 */
void updatePointerInPrimaryFile(long lastRecordPosition, long newNextValue);

/**
 * Follows the chain and prints all record found in primary file
 * @param long firstRecordPosition
 *
 */
void consultRecordsInPrimaryFile(long firstRecordPosition);