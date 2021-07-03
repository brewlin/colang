test:
	sh tests_compiler.sh
	sh tests_asmer.sh
	sh tests_linker.sh
install:
	mkdir bin
	cd bin
	cmake ..
	make & make install