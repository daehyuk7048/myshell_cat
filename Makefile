PROJ_DIR = $(shell pwd)
SRC_DIR = $(PROJ_DIR)/src
INC_DIR = $(PROJ_DIR)/include
OBJ_DIR = $(PROJ_DIR)/obj
BIN_DIR = $(PROJ_DIR)/bin

$(BIN_DIR)/myshell: $(OBJ_DIR)/myshell.o $(BIN_DIR)
	gcc -o $@ $^

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc -c $< -o $@ -I$(INC_DIR)
# -include $(OBJ_DIR)/*.d
$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(BIN_DIR)/myshell $(OBJ_DIR)/*.o
distclean:
	rm -f $(BIN_DIR)/myshell $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR) $(BIN_DIR)