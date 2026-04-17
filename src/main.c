#include <c64.h>
#include <string.h>
#include <6502.h>

/* Structure et données définies dans scenes.c */
typedef struct {
    const char *name;
    const unsigned char *screen;
    const unsigned char *color;
} Scene;

extern const unsigned char CHARSET[32][8];
extern const Scene SCENES[3];

/* Registres VIC-II (valeurs issues de scenes.c) */
#define VIC_BORDER_COLOR  0x0D
#define VIC_BG_COLOR_0    0x0D
#define VIC_BG_COLOR_1    0x0B
#define VIC_BG_COLOR_2    0x01

/* Attendre n frames PAL (~20 ms chacune, 50 = ~1 seconde) */
static void wait_frames(unsigned char n) {
    while (n--) {
        while (VIC.rasterline != 255)
            ;
        while (VIC.rasterline == 255)
            ;
    }
}

/* Copier le jeu de caractères ROM en RAM à $3800,
   puis superposer les 32 tiles custom à l'offset 0x40*8 */
static void setup_charset(void) {
    unsigned char *ram = (unsigned char *)0x3800;

    SEI();
    /* Rendre la ROM caractères visible à $D000
       en mettant CHAREN (bit 2 de $0001) à 0 */
    *(unsigned char *)0x0001 &= ~0x04;
    memcpy(ram, (const unsigned char *)0xD000, 2048);
    *(unsigned char *)0x0001 |= 0x04;
    CLI();

    /* Tiles custom (codes $40..$5F) à l'offset $200 */
    memcpy(ram + 0x200, (const unsigned char *)CHARSET, 32 * 8);
}

static void show_scene(const Scene *s) {
    memcpy((unsigned char *)0x0400, s->screen, 1000);
    memcpy((unsigned char *)0xD800, s->color, 1000);
}

int main(void) {
    unsigned char i;

    setup_charset();

    /* Couleurs globales */
    VIC.bordercolor = VIC_BORDER_COLOR;
    VIC.bgcolor0 = VIC_BG_COLOR_0;
    VIC.bgcolor1 = VIC_BG_COLOR_1;
    VIC.bgcolor2 = VIC_BG_COLOR_2;

    /* Charset à $3800 (bits 1-3 = 7), écran à $0400 (bits 4-7 = 1) */
    VIC.addr = 0x1E;

    /* Activer le mode multicolore (bit 4 de $D016) */
    VIC.ctrl2 |= 0x10;

    /* Boucle infinie : afficher chaque scène ~1 seconde */
    for (;;) {
        for (i = 0; i < 3; i++) {
            show_scene(&SCENES[i]);
            wait_frames(50);
        }
    }
}
