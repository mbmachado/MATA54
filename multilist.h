/**
 * The Secondary Key Record
 */
typedef struct sk {
	char key[21];
	long int firstRecord;
	long int lastRecord;
	bool isDeleted;
} SKRecord;

/**
 * Inserts a secondary key record in multilist file
 *
 */
void insert();

/**
 * Removes a secondary key record in multilist file
 *
 */
void remove();

/**
 * Consults a secondary key record in multilist file
 *
 */
void consult();