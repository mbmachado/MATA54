#include <stdio.h>
#include "multilist.h"

int main(int argc, char const *argv[]) {
    char command;

    do {
        scanf("%c", &command);
        switch(command) {
            case 'i':
                insert();
                break;
            case 'c':
                consult();
                break;
            case 'r':
                remove();
                break;
            default:
                return 0;
        }
    } while(scanf("%c", &command));

}
