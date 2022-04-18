main: main.c
	clang-format -i main.c
	gcc main.c -Wall -Wextra -g -o main

clean:
	rm -rfv main *.o datos.txt

run: main
	./main
