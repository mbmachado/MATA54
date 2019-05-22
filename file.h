typedef struct person {
	int key;
	char name[21];
	unsigned int age;
} Person;

/*
 * Função save:
 * Salva um registro na chave indicada 
 *
 * */

void insert();

/*
 * Função remove:
 * Remove um registro na chave indicada 
 *
 * */
void remove();

/*
 * Função get:
 * Imprime um registro na chave indicada
 *
 * */
void consult();

/*
 * Função getAll:
 * Imprime todos os registro salvos no arquivo
 *
 * */
void printAll();