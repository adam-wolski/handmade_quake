P=quake
TARGET=build/quake
SOURCES=$(wildcard *.c)
TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
CFLAGS= -g -std=c11 -Wall -Wextra -Wpedantic -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2
LDLIBS=-lX11 -lrt
CC=clang

$(P): clean
	$(CC) $(CFLAGS) -o $(TARGET) $(LDLIBS) $(SOURCES) $(TEST_SRC)

run_tests:
	./${TARGET} run_tests
run:
	./${TARGET}
clean:
	rm -f ${TARGET}
