#include <stdio.h>

extern void set_border(void);

int main(void) {
    set_border();
    printf("HELLO, WORLD!\n");
    return 0;
}
