CC=clang
TARGET=main
CFLAGS=-Wall -lgmp -lmpfr -lm
DFLAGS=-g
SANITIZE=-fsanitize=address
SOURCE = $(wildcard src/*.c)
OBJS=$(addprefix build/, $(patsubst %.c, %.o, $(notdir $(SOURCE))))

all: $(TARGET)
$(TARGET): $(OBJS)
	@mkdir -p exec
	@echo "============="
	@echo "Linking the target $@"
	@echo "============="
	@$(CC) $(CFLAGS) $(DFLAGS) -o exec/$@ $^ 
	@echo -- Link finished --
# Rule for compiling .c files
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "============="
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@
	@echo -- Compilation finished --
# Clean up build and exec directories
clean:
	@-rm -rf build/ exec/