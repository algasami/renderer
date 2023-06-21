# app/Makefile

SOURCES=main.c
OBJECTS=${SOURCES:.c=.o}

CC_FLAGS:=${CC_FLAGS}

install: a.out
	cp ./a.out ${BUILD}/a.out

a.out: ${OBJECTS}
	${CC} ${CC_FLAGS} -L${BUILD}/lib -llinalg -lrenderer ${OBJECTS} -o a.out

%.o: %.c
	${CC} ${CC_FLAGS} -I${BUILD}/include -c $< -o $@

install-headers:
	cp -rp ./include/* ${BUILD}/include
