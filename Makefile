test:
	sh test*.sh
install:
	mkdir bin
	cd bin
	cmake ..
	make & make install