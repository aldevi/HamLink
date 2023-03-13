
# --- Paramètres --- #
PREFIX=
CC=/usr/bin/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3
SSH_USER=pi
SSH_IP=172.24.1.1
SSH_DESTDIR=/opt/HamLink
ARCHIVE=archive.tar.gz

# Mode silencieux
ifneq ($V, 1)
	Q=@
endif

# --- Général --- #
all : 

clean :
	@ echo "[Clean]"
	$(Q) rm -f *.o *.e *.pi *.tar.gz

archive :
	tar -czvf $(ARCHIVE) *.pi

# --- menu --- #
menu.pi : menu.c
	$(Q) $(CC) menu.c -o menu.pi


# --- SSH --- #
install : archive
	scp $(ARCHIVE) $(SSH_USER)@$(SSH_IP):$(SSH_DESTDIR)
	make clean