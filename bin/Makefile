
BLOCK_SERVER_OBJ = $(BIN_DIR)/dk_example_tcp_server.o
EPOLL_SERVER_OBJ = $(BIN_DIR)/dk_example_epoll_server.o
EPOLL_RB_SERVER_OBJ = $(BIN_DIR)/dk_example_epoll_rb_server.o
POSIX_SERVER_OBJ = $(BIN_DIR)/dk_example_posix_block_server.o

BLOCK_SERVER = dk_example_block_server
EPOLL_SERVER = dk_example_epoll_server
EPOLL_RB_SERVER = dk_example_epoll_rb_server
POSIX_SERVER = dk_example_posix_block_server

all : $(BLOCK_SERVER) $(EPOLL_SERVER) $(EPOLL_RB_SERVER) $(POSIX_SERVER)

$(BLOCK_SERVER) : $(BLOCK_SERVER_OBJ)
	$(CC) -o $(BIN_DIR)/$(BLOCK_SERVER) $(OBJS_DIR)/* $(BLOCK_SERVER_OBJ) $(FLAG)

$(EPOLL_SERVER) : $(EPOLL_SERVER_OBJ)
	$(CC) -o $(BIN_DIR)/$(EPOLL_SERVER) $(OBJS_DIR)/* $(EPOLL_SERVER_OBJ) $(FLAG)

$(EPOLL_RB_SERVER) : $(EPOLL_RB_SERVER_OBJ)
	$(CC) -o $(BIN_DIR)/$(EPOLL_RB_SERVER) $(OBJS_DIR)/* $(EPOLL_RB_SERVER_OBJ) $(FLAG)

$(POSIX_SERVER) : $(POSIX_SERVER_OBJ)
	$(CC) -o $(BIN_DIR)/$(POSIX_SERVER) $(OBJS_DIR)/* $(POSIX_SERVER_OBJ) $(FLAG)
