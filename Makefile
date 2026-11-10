CC     := gcc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -g -Iinclude

TOOLS   := $(basename $(notdir $(wildcard src/tools/*.c)))
BINS    := $(addprefix bin/,$(TOOLS))

all: $(BINS)

bin/%: src/tools/%.c | bin
	$(CC) $(CFLAGS) $(filter %.c,$^) -o $@

bin:
	mkdir -p bin

$(TOOLS): %: bin/%

test: all
	sh tests/run_tests.sh
	

clean:
	rm -rf bin

.PHONY: all test watch clean $(TOOLS)