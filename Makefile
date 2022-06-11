compile:
	@echo "Compiling..."
	@gcc WebLite.c lib/sock.h lib/sock.c

execute:
	@./a.out

clean:
	@rm a.out
