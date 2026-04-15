.export _set_raster_irq

_set_raster_irq:
    sei
    lda #$7f
    sta $dc0d           ; disable CIA1 timer IRQs
    lda $dc0d           ; ack any pending CIA1 IRQ
    lda #$01
    sta $d01a           ; enable VIC raster IRQ source
    lda #50
    sta $d012           ; raster compare = line 50
    lda $d011
    and #$7f
    sta $d011           ; clear high bit of raster compare
    lda #<irq_handler
    sta $0314
    lda #>irq_handler
    sta $0315
    lda #$ff
    sta $d019           ; ack any pending VIC IRQ
    cli
    rts

irq_handler:
    inc $d020           ; visible effect: cycle border color
    lda #$ff
    sta $d019           ; ack VIC raster IRQ
    jmp $ea31           ; chain to KERNAL IRQ exit
