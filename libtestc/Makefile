CC=cc
MAJOR_VERSION=0
MINOR_VERSION=1
INCLUDE_HEADER_DIR= -I ~/headers/testc/v_${MAJOR_VERSION}_${MINOR_VERSION}/
CFLAGS=${INCLUDE_HEADER_DIR}

FILE_SUFFIX=a
NAME=libtestc
LIB_DIR=~/lib/
LIB_FILE=${LIB_DIR}${NAME}-${MAJOR_VERSION}.${MINOR_VERSION}.${FILE_SUFFIX}

ARCHIVE_FLAGS=-cvr
ARCHIVE=ar

${LIB_FILE} : *.o
	${ARCHIVE} ${ARCHIVE_FLAGS} $@ $^ 

%.o : %.c
	${CC} ${CFLAGS} -c $^

clean :
	rm *.o

remove :
	rm ${LIB_FILE}

distclean : remove clean
