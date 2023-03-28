# --- Paramètres --- #
LIBS=libs
BIN=bin
HAMLINK=HamLink
CC=/usr/bin/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3
OPT=-std=c99
SSH_USER=pi
SSH_IP=172.24.2.1
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

pc : $(BIN)/HamLink.pc

pi : $(BIN)/HamLink.pi

clean :
	@ echo "[Clean]"
	$(Q) rm -f bin/*

archive :
	tar -czvf $(ARCHIVE) bin/*.pi

# --- Librairies --- #
$(BIN)/fenetre.pc.o : $(LIBS)/fenetre.c
	$(Q) gcc -c $^ -o $@ -lncurses -lmenu -lform

$(BIN)/fenetre.pi.o : $(LIBS)/fenetre.c
	$(Q) $(CC) $(OPT) $(PI_CFLAGS) $(PI_LDFLAGS) -c $^ -o $@ -lncurses -lmenu -lform

# --- Programme --- #
$(BIN)/HamLink.pc : $(HAMLINK)/HamLink.c $(BIN)/fenetre.pc.o
	$(Q) gcc $^ -o $@ -lncurses -lmenu -lform

$(BIN)/HamLink.pi : $(HAMLINK)/HamLink.c $(BIN)/fenetre.pi.o
	$(Q) $(CC) $(OPT) $(PI_CFLAGS) $(PI_LDFLAGS) $^ -o $@ -lncurses -lmenu -lform

# --- SSH --- #
install : archive
	scp $(ARCHIVE) $(SSH_USER)@$(SSH_IP):$(SSH_DESTDIR)
	make clean