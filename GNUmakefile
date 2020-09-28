
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -pedantic -Iinclude -DSVM_ASSERT_LEVEL=2 -g
LDFLAGS := -g
LDLIBS := -lm

BUILDDIR := _build
DEPSDIR := $(BUILDDIR)/deps

#############################################################################

SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c,$(BUILDDIR)/%.o,$(SOURCES))
DEPFILES := $(patsubst src/%.c,$(DEPSDIR)/%.d,$(SOURCES))

.DEFAULT: all
.PHONY: clean

all: $(BUILDDIR)/svm

$(BUILDDIR)/%.o: src/%.c $(DEPSDIR)/%.d | $(BUILDDIR) $(DEPSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: test/%.c | $(BUILDDIR) $(DEPSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/svm: $(OBJECTS) | $(BUILDDIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILDDIR)/value-test: $(BUILDDIR)/assert.o $(BUILDDIR)/value-test.o | $(BUILDDIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILDDIR)/string-test: $(BUILDDIR)/assert.o $(BUILDDIR)/string.o $(BUILDDIR)/string-test.o | $(BUILDDIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILDDIR)/error-test: $(BUILDDIR)/error-test.o | $(BUILDDIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILDDIR) $(DEPSDIR):
	mkdir -p $@

$(DEPFILES): ; @:

-include $(DEPFILES)

