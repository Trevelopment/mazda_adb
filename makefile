# ADB makefile
# ------------

#TODO change TOOLCHAIN variable to your toolchain path 
TOOLCHAIN= ~/Mazda/m3-toolchain-master/bin/arm-cortexa9_neon-linux-gnueabi-
CC= $(TOOLCHAIN)gcc
LD= $(TOOLCHAIN)gcc
CXX=$(CC)


SRCS+= adb.c
SRCS+= fdevent.c
SRCS+= adb_client.c
SRCS+= commandline.c
SRCS+= console.c
SRCS+= file_sync_client.c
SRCS+= get_my_path_linux.c
SRCS+= services.c
SRCS+= sockets.c
SRCS+= transport.c
SRCS+= transport_local.c
SRCS+= transport_usb.c
SRCS+= usb_linux.c
SRCS+= usb_vendors.c
SRCS+= adb_auth_host.c
 
VPATH+= ../libcutils
#SRCS+= list.c
SRCS+= socket_inaddr_any_server.c
SRCS+= socket_local_client.c
SRCS+= socket_local_server.c
SRCS+= socket_loopback_client.c
SRCS+= socket_loopback_server.c
SRCS+= socket_network_client.c
SRCS+= load_file.c
 
VPATH+= ../libzipfile
SRCS+= centraldir.c
SRCS+= zipfile.c
 
VPATH+= ../../../external/zlib/src
SRCS+= adler32.c
SRCS+= compress.c
SRCS+= crc32.c
SRCS+= deflate.c
SRCS+= infback.c
SRCS+= inffast.c
SRCS+= inflate.c
SRCS+= inftrees.c
SRCS+= trees.c
SRCS+= uncompr.c
SRCS+= zutil.c

CPPFLAGS+= -DADB_HOST=1
CPPFLAGS+= -DHAVE_FORKEXEC=1
CPPFLAGS+= -DHAVE_SYMLINKS
CPPFLAGS+= -DHAVE_TERMIO_H
CPPFLAGS+= -DHAVE_SYS_SOCKET_H
CPPFLAGS+= -DHAVE_OFF64_T
CPPFLAGS+= -D_GNU_SOURCE
CPPFLAGS+= -D_XOPEN_SOURCE
CPPFLAGS+= -std=c++11 
CPPFLAGS+= -I.
CPPFLAGS+= -I../include
CPPFLAGS+= -I../../../external/zlib
CPPFLAGS+= -I../../../external/openssl/include
CPPFLAGS+= -I../base/include 
CPPFLAGS+= -D_FILE_OFFSET_BITS=64
CFLAGS+= -O2 -g -Wall -Wno-unused-parameter

LIBS= -lcrypto -lpthread -lrt 
 
OBJS= $(SRCS:.c=.o)

LDFLAGS= -L../../../../openssl-1.0.2f
 
all: adb
 
adb: $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
 
clean:
	rm -rf $(OBJS)
