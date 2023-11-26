CC = gcc
CARGS = -m64 -Werror
LIBARGS = -shared -nostdlib
OutputFolder = baselib/
Output = baselib.so

Input = src/*

Testfile = ./test.c
Testbin = ./test


env:
	bash -c "if ls ${OutputFolder};then echo '${OutputFolder} exists'; else mkdir -p ${OutputFolder};fi"

build: env
	${CC} ${CARGS} ${LIBARGS} ${Input} -o ${OutputFolder}${Output}
	bash -c "cp -r headers/* ${OutputFolder}"

test: build
	${CC} ${CARGS} ${Testfile} ${OutputFolder}${Output} -o ${Testbin}
	bash -c "${Testbin}"

clean:
	bash -c "rm -r ${OutputFolder}"
