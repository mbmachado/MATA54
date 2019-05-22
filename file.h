/**
 * The Record
 */
typedef struct record {
	char key[21];
	char content[51];
	long int next;
} Record;

/**
 * Inserts a record in primary file
 * @param char[21] key
 * @param char[51] content
 * @return int insertionLine
 *
 */
long int insertRecordInPrimaryFile(char key[21], char content[51]);

/**
 * Updates a record's next poiter in primary file
 * @param int lastRecordPosition
 * @param int newNextValue
 *
 */
void updatePointerInPrimaryFile(long int lastRecordPosition, long int newNextValue);

/**
 * Follows the chain and prints all record found in primary file
 * @param int firstRecordPosition
 *
 */
void consultRecordsInPrimaryFile(long int firstRecordPosition);