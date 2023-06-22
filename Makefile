PROJECTS=linalg renderer app
HEADER_PROJECTS=linalg renderer app

export BUILD:=$(shell pwd)/out
export CC_FLAGS:=-Wall

all: install build run

build: install install-headers

build-folder:
	@echo Creating build folder at ${BUILD}
	@mkdir -p ${BUILD}
	@mkdir -p ${BUILD}/include
	@mkdir -p ${BUILD}/lib

install: build-folder install-headers
	rm -f compile_commands.json
	@echo Installing Applications
	@for project in ${PROJECTS}; do\
		(cd src/$${project} && make install);\
	done

install-headers: build-folder
	@echo Installing headers
	@for project in ${HEADER_PROJECTS}; do\
		(cd src/$${project} && make install-headers);\
	done

clean:
	rm -rf ${BUILD}/*.out
	find . -name "*.a" -type f -delete
	find . -name "*.o" -type f -delete
