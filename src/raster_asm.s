.export _raster_handler_top
.export _raster_handler_bottom

_raster_handler_top:
    inc $d020                       ; effet visible : couleur de cadre +1
    lda #150
    sta $d012                       ; prochaine IRQ ligne 150
    lda #<_raster_handler_bottom
    sta $0314
    lda #>_raster_handler_bottom
    sta $0315                       ; basculer le vecteur sur _bottom
    lda #$ff
    sta $d019                       ; ack VIC raster IRQ
    jmp $ea31                       ; chaîner vers la sortie KERNAL

_raster_handler_bottom:
    dec $d020                       ; effet visible : couleur de cadre -1
    lda #50
    sta $d012                       ; prochaine IRQ ligne 50
    lda #<_raster_handler_top
    sta $0314
    lda #>_raster_handler_top
    sta $0315                       ; basculer le vecteur sur _top
    lda #$ff
    sta $d019                       ; ack VIC raster IRQ
    jmp $ea31                       ; chaîner vers la sortie KERNAL
