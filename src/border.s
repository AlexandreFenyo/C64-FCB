.export _set_border

_set_border:
    lda #0
    sta $d020
    sta $d021
    rts
