all: src/libcsock.a

src/libcsock.a:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
