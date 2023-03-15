# --- Paramètres --- #
LIBS=libs
BIN=bin
MENU=menu
PREFIX=
CC=/usr/bin/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3
SSH_USER=pi
SSH_IP=172.24.1.1
SSH_DESTDIR=/opt/HamLink
ARCHIVE=archive.tar.gz

# --- Librairies --- #
PATH_LIB_NCURSES=/usr/lib/ncurses-pi
PI_CFLAGS=-I$(PATH_LIB_NCURSES)/include/ncurses -I$(PATH_LIB_NCURSES)/include
PI_LDFLAGS=-L$(PATH_LIB_NCURSES)/lib

# --- Mode silencieux --- "
ifneq ($V, 1)
	Q=@
endif

# --- Général --- #
all : pc pi

pc : $(BIN)/menu.pc

pi : $(BIN)/menu.pi

clean :
	@ echo "[Clean]"
	$(Q) rm -f bin/*

archive :
	tar -czvf $(ARCHIVE) bin/*.pi

# --- Librairies --- #
$(BIN)/fenetre.pc.o : $(LIBS)/fenetre.c
	$(Q) gcc -c $^ -o $@ -lncurses

$(BIN)/fenetre.pi.o : $(LIBS)/fenetre.c
	$(Q) $(CC) $(PI_CFLAGS) $(PI_LDFLAGS) -c $^ -o $@ -lncurses

# --- Programme --- #
$(BIN)/menu.pc : $(MENU)/menu.c $(BIN)/fenetre.pc.o
	$(Q) gcc $^ -o $@ -lncurses

$(BIN)/menu.pi : $(MENU)/menu.c $(BIN)/fenetre.pi.o
	$(Q) $(CC) $(PI_CFLAGS) $(PI_LDFLAGS) $^ -o $@ -lncurses

# --- SSH --- #
install : archive
	scp $(ARCHIVE) $(SSH_USER)@$(SSH_IP):$(SSH_DESTDIR)
	make clean