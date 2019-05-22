#include <stdio.h>
#include "file.h"

int insertRecordInPrimaryFile(char key[21], char content[51]) {
	printf("%s\n", "Cheguei no insert");
	return 1;
}

void updatePointerInPrimaryFile(int lastRecordLine, int newNextValue) {
	printf("%s\n", "Cheguei no update");
}

void consultRecordsInPrimaryFile(int firstRecordLine) {
	printf("%s\n", "Cheguei no consult");
}