.export _raster_handler

_raster_handler:
    inc $d020           ; visible effect: cycle border color
    lda #$ff
    sta $d019           ; ack VIC raster IRQ
    jmp $ea31           ; chain to KERNAL IRQ exit
