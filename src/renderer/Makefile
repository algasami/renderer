# renderer/Makefile

SOURCES=renderer/renderer.c
OBJECTS=${SOURCES:.c=.o}

CC_FLAGS:=${CC_FLAGS} -Iinclude

LIB_NAME=librenderer.a

install: ${LIB_NAME}
	cp ${LIB_NAME} ${BUILD}/lib

${LIB_NAME}: ${OBJECTS}
	${AR} -rcs ${LIB_NAME} ${OBJECTS}

%.o: %.c
	${CC} ${CC_FLAGS} -c $< -o $@

install-headers:
	cp -rp ./include/* ${BUILD}/include
