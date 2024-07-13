
PYTHON3 ?= python3

CROSS_COMPILE ?= h8300-hitachi-elf-

OBJCOPY ?= objcopy

AS := $(CROSS_COMPILE)$(AS)
LD := $(CROSS_COMPILE)$(LD)
OBJCOPY := $(CROSS_COMPILE)$(OBJCOPY)

ASFLAGS := --h-tick-hex -mach=h8300h -I./inc/ $(ASFLAGS)
LDFLAGS := -m h8300helf -T payload.ld -static $(LDFLAGS)
LDFLAGS := -nostdlib --build-id=none --relax $(LDFLAGS)

default: all

INPUT_SOURCES := $(wildcard src/*.s)
OBJECT_FILES := $(patsubst src/%.s,obj/%.s.o,$(INPUT_SOURCES))
ELVES_OUT := $(patsubst src/%.s,bin/%.elf,$(INPUT_SOURCES))
BINARIES_OUT := $(patsubst src/%.s,bin/%.bin,$(INPUT_SOURCES))
HEADERS_OUT := $(patsubst src/%.s,bin/%.h,$(INPUT_SOURCES))

all: $(BINARIES_OUT) $(HEADERS_OUT)

%/:
	@mkdir -vp "$@"

obj/%.s.o: src/%.s obj/
	$(AS) $(ASFLAGS) -o "$@" "$<"

bin/%.elf: obj/%.s.o bin/
	$(LD) --cref -Map="$@.map" $(LDFLAGS) -o "$@" "$<"

bin/%.bin: bin/%.elf
	$(OBJCOPY) -O binary "$<" "$@"

bin/%.h: bin/%.bin
	$(PYTHON3) -c 'import sys;import textwrap;print(textwrap.fill(",".join("0x%02x"%x for x in sys.stdin.buffer.read())))' < "$<" > "$@"

clean:
	@$(RM) -v $(OBJECT_FILES) $(ELVES_OUT) $(BINARIES_OUT) $(HEADERS_OUT)

.PHONY: default all clean
.PRECIOUS: $(OBJECT_FILES) $(ELVES_OUT) bin/ obj/

