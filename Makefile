build:
	gcc -o mycat main.c
install: build
	cp mycat /usr/bin
clean:
	rm mycat