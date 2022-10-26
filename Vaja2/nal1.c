

#include <stdio.h>
#define MAX_LIMIT 20

int main() {
    char str[MAX_LIMIT];
    printf("Prosim vnesite svoje ime: ");
    fgets(str, MAX_LIMIT, stdin);
    printf("Pozdravljen %s\n", str);

    return 0;
}
