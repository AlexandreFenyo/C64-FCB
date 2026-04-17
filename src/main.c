#include <stdio.h>

extern void set_border(void);
extern void set_raster_irq(void);
extern void clear_raster_irq(void);

int main(void) {
    int cpt;

    set_border();
    set_raster_irq();
    printf("Hello!\n");
    for (cpt = 0; cpt < 10; cpt++) {
        printf("Counter: %d\n", cpt);
    }
    clear_raster_irq();
    return 0;
}
