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
long insertRecord(char key[21], char content[51]);

/**
 * Updates a record's next pointer in primary file
 * @param long lastRecordPosition
 * @param long newNextValue
 *
 */
void updatePointer(long lastRecordPosition, long newNextValue);

/**
 * Follows the chain and prints all records found in the primary file
 * @param long firstRecordPosition
 *
 */
void consultRecords(long firstRecordPosition);
