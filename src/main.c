#include <stdio.h>

extern void set_border(void);
extern void set_raster_irq(void);

int main(void) {
    set_border();
    set_raster_irq();
    printf("HELLO, WORLD!\n");
    for (;;) { }
    return 0;
}
