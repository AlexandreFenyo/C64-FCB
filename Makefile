CC     := cl65
TARGET := c64
PRG    := hello.prg
OBJS   := src/main.o src/scenes.o

all: $(PRG)

%.o: %.c
	$(CC) -t $(TARGET) -c -o $@ $<

%.o: %.s
	$(CC) -t $(TARGET) -c -o $@ $<

$(PRG): $(OBJS)
	$(CC) -t $(TARGET) -o $@ $(OBJS)

run: $(PRG)
	x64sc -symkeymap $$PWD/keymap.vice.vkm -keymap 2 $(PRG)

debug: $(PRG)
	x64sc -symkeymap $$PWD/keymap.vice.vkm -keymap 2 -initbreak ready $(PRG)

cli: $(PRG)
	x64sc -symkeymap $$PWD/keymap.vice.vkm -keymap 2 -iecdevice8 -virtualdev8 -fs8 . -drive8type 0

clean:
	rm -f $(OBJS) $(PRG)

.PHONY: all run debug cli clean
