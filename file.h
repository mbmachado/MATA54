/**
 * The Record
 */
typedef struct record {
	char key[21];
	char content[51];
	int next;
} Record;

/**
 * Inserts a record in primary file
 * @param char[21] key
 * @param char[51] content
 * @return int insertionLine
 *
 */
int insertRecordInPrimaryFile(char key[21], char content[51]);

/**
 * Updates a record's next poiter in primary file
 * @param int lastRecordLine
 * @param int newNextValue
 *
 */
void updatePointerInPrimaryFile(int lastRecordLine, int newNextValue);

/**
 * Follows the chain and prints all record found in primary file
 * @param int firstRecordLine
 *
 */
void consultRecordsInPrimaryFile(int firstRecordLine);