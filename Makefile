CC = gcc
ARCH = 64
CARGS = -m${ARCH} -Werror
LIBARGS = -shared -nostdlib
OutputFolder = baselib/
Output = baselib.so
Input = src/*

TestOut = ./test.bin
ReleaseFolder = releases/

build: clean
	mkdir -p ${OutputFolder}headers
	${CC} ${CARGS} ${LIBARGS} ${Input} -o ${OutputFolder}${Output}
	bash -c "cp -r headers/* ${OutputFolder}headers"
	bash -c "cp README.md ${OutputFolder}"
	echo "ceated on the: $$(date +%d"."%m".20"%y)" > ${OutputFolder}timestamp

clean:
	bash -c "if ls ${OutputFolder};then rm -r ${OutputFolder};fi"

test: build
	${CC} ${CARGS} ./test.c ${OutputFolder}${Output} -o ${TestOut}
	bash -c ${TestOut}
	rm ${TestOut}

release: build
	mkdir -p ${ReleaseFolder}
	bash -c "tar -cf ${ReleaseFolder}baselib-release-$$(date +%d\".\"%m\".20\"%y).tar ${OutputFolder}"
	bash -c "gzip ${ReleaseFolder}baselib-release-$$(date +%d\".\"%m\".20\"%y).tar"
	rm -r ${OutputFolder}

srcrel: clean
	mkdir -p ${OutputFolder}
	bash -c "cp -r ./src ./headers ${OutputFolder}"
	cp README.md ${OutputFolder}
	echo "ceated on the: $$(date +%d.%m.20%y)" > ${OutputFolder}timestamp
	bash -c "tar -cf ${ReleaseFolder}baselib-release-$$(date +%d\".\"%m\".20\"%y)-src.tar ${OutputFolder}"
	bash -c "gzip ${ReleaseFolder}baselib-release-$$(date +%d\".\"%m\".20\"%y)-src.tar"

install: build
	cp ${OutputFolder}${Output} /usr/lib${ARCH}/lib${Output}
	cp -r ${OutputFolder}headers /usr/include/${OutputFolder}
	rm -r ${OutputFolder}

remove:
	rm /usr/lib${ARCH}/lib${Output}
	rm -r /usr/include/${OutputFolder}
