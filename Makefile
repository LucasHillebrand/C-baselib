CC = gcc
CARGS = -m64 -Werror
LIBARGS = -shared -nostdlib
OutputFolder = baselib/
Output = baselib.so
Input = src/*

TestOut = ./testbin

build:
	mkdir -p ${OutputFolder}
	${CC} ${CARGS} ${LIBARGS} ${Input} -o ${OutputFolder}${Output}
	bash -c "cp -r headers/* ${OutputFolder}"

clean:
	bash -c "rm -r ${OutputFolder}"

test: build
	${CC} ${CARGS} ./test.c ${OutputFolder}${Output} -o ${TestOut}
	bash -c ${TestOut}
	rm ${TestOut}