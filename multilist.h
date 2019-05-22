/**
 * The Secondary Key Record
 */
typedef struct sk {
	char key[21];
	int firstRecord;
	int lastRecord;
	bool isDeleted;
} SKRecord;

/**
 * Inserts a secondary key record in multilist's file
 *
 */
void insert();

/**
 * Removes a secondary key record in multilist's file
 *
 */
void remove();

/**
 * Consults a secondary key record in multilist's file
 *
 */
void consult();