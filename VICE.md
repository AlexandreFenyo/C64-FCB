# VICE — aide-mémoire

## Moniteur

Ouvrir le moniteur à tout moment : `Alt+H`. Le quitter et reprendre l'exécution : `x`.

### Navigation / inspection

| Commande | Effet |
|---|---|
| `r` | Affiche les registres (`PC AC XR YR SP` + flags `NV-BDIZC`) |
| `r a=$ff` | Modifie un registre (`a`, `x`, `y`, `pc`, `sp`…) |
| `d $c000` | Désassemble à partir de `$c000` |
| `m $c000` | Dump mémoire à partir de `$c000` |

### Exécution

| Commande | Effet |
|---|---|
| `g $c000` | *Go* : reprend l'exécution à `$c000` |
| `r pc=$c000` | Change le PC sans relancer |
| `z` | Step (entre dans les `JSR`) |
| `n` | Next (n'entre pas dans les `JSR`) |
| `ret` | Continue jusqu'au prochain `RTS` |
| `bk $c000` | Pose un breakpoint à `$c000` |
| `x` | Sort du moniteur, reprend l'exécution |

### Formats d'adresses

- Hexadécimal : `$c000`
- Décimal : `+49152`
- Binaire : `%1100000000000000`

## Adresses utiles

| Adresse | Rôle |
|---|---|
| `$FFFC/$FFFD` | Vecteur de reset (pointe sur `$FCE2`) |
| `$FCE2` | Cold-start KERNAL — équivalent reset matériel |
| `$FF81` | Cold start KERNAL (init écran + E/S) |
| `$FF5B` | Init VIC / CIA via la table KERNAL |
| `$A474` | Warm start BASIC (retour au prompt `READY.`) |
| `$D020` | Couleur du cadre |
| `$D021` | Couleur du fond |

Pour redémarrer le C64 depuis le moniteur :

```
g $fce2
```
