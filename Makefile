
CC = gcc
CFLAGS = -Wextra -pg -g
LDFLAGS = -lm

SRC = main.c lib/graph.c lib/graph_math.c lib/read_graph.c lib/utils.c lib/visualize_graph.c
OBJ = $(patsubst %.c,bin/%.o,$(SRC))
EXEC = bin/divide_graph
SUBMODULE = jimp2/projekt-4
SUBREPO = jimp2

all: $(EXEC)

$(EXEC): $(OBJ) | bin
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

bin/%.o: %.c | bin_dirs
	$(CC) $(CFLAGS) -c $< -o $@

bin_dirs:
	mkdir -p bin bin/lib

clean:
	rm -rf bin

sub:
	rm -rf $(SUBREPO)
	git clone https://github.com/yallxe/jimp2
	make -C $(SUBMODULE)

TEST_SRC = test.c
TEST_EXEC = bin/test

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRC) | bin
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_EXEC) $(LDFLAGS)
