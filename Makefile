include config.mk

SRC = main.cpp bubble.cpp select.cpp insert.cpp binary_insert.cpp bucket.cpp
OBJ = ${SRC:.cpp=.o}

all: options main

options:
	@echo build options:
	@echo "CPPFLAGS = ${CPPFLAGS}"
	@echo "CXX 	= ${CXX}"

main: ${OBJ}
	${CXX} -o $@ ${OBJ} ${CPPFLAGS}

clean:
	@rm ${OBJ}
	@rm main
