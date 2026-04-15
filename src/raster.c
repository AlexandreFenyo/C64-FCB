#include <c64.h>
#include <6502.h>

/* Handler IRQ écrit en assembleur (src/raster_asm.s).
   On ne peut pas l'écrire en C standard : un handler d'IRQ doit
   préserver tous les registres et terminer par RTI (ou chaîner via
   $EA31), ce que le code généré par cc65 ne fait pas. */
extern void raster_handler_top(void);

void set_raster_irq(void) {
    /* Vecteur IRQ logiciel du KERNAL en $0314/$0315 : quand une IRQ
       arrive, la routine ROM en $FF48 sauve les registres puis saute
       en JMP ($0314). C'est ce vecteur qu'on détourne vers notre
       handler. */
    void (**vec)(void) = (void (**)(void))0x0314;

    /* SEI : on masque les IRQ pendant qu'on reconfigure la chaîne
       d'interruption, sinon une IRQ pourrait survenir dans un état
       incohérent. */
    SEI();

    /* CIA1 $DC0D (Interrupt Control Register) :
       écrire avec bit7=0 *désactive* les sources sélectionnées.
       $7F = 0111 1111 -> on désactive toutes les sources d'IRQ du
       CIA1 (notamment Timer A qui génère normalement l'IRQ jiffy
       toutes les 1/60s pour le KERNAL). */
    CIA1.icr = 0x7f;

    /* Lecture de $DC0D : acquitte une éventuelle IRQ CIA1 en attente
       (le registre est "read to clear"). Le (void) évite un warning
       sur la valeur ignorée. */
    (void)CIA1.icr;

    /* VIC $D01A (Interrupt Mask Register) :
       bit0 = autoriser l'IRQ "raster compare". On n'active que
       celle-là (pas les collisions sprite, ni light pen). */
    VIC.imr = 0x01;

    /* VIC $D012 = 8 bits de poids faible de la ligne raster cible.
       Ici 50 : le handler sera appelé quand le faisceau atteint la
       ligne 50 de l'écran. */
    VIC.rasterline = 50;

    /* VIC $D011 bit 7 = bit 8 (poids fort) de la ligne raster cible.
       L'écran ne fait que 312 lignes mais le compteur va jusqu'à 511,
       donc ce bit est nécessaire pour cibler une ligne >= 256.
       Ligne 50 < 256 -> on force le bit à 0. On garde les autres bits
       de $D011 (mode texte/bitmap, hauteur écran, etc.) intacts. */
    VIC.ctrl1 &= 0x7f;

    /* Installation atomique du nouveau handler dans le vecteur IRQ. */
    *vec = raster_handler_top;

    /* VIC $D019 (Interrupt Request Register) : écrire 1 sur un bit
       l'acquitte. $FF acquitte tout ce qui pourrait être en attente,
       sinon l'IRQ partirait immédiatement après le CLI. */
    VIC.irr = 0xff;

    /* CLI : on réautorise les IRQ ; à partir d'ici, à chaque passage
       du faisceau sur la ligne 50, raster_handler sera appelé. */
    CLI();
}
