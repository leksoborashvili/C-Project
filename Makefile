run: compile
	./a.out department1.txt department2.txt degree1.txt degree2.txt

compile: c
	gcc -Wall requirements.o main.o course.o degrees.o department.o commands.o student.o
c:
	gcc -c -Wall main.c
	gcc -c -Wall requirements.c
	gcc -c -Wall degrees.c
	gcc -c -Wall course.c
	gcc -c -Wall department.c
	gcc -c -Wall commands.c
	gcc -c -Wall student.c
	
debug: g
	gcc -g requirements.o main.o degrees.o course.o department.o commands.o student.o -o debug
g:
	gcc -c -g -Wall main.c
	gcc -c -g -Wall requirements.c
	gcc -c -g -Wall degrees.c
	gcc -c -g -Wall course.c
	gcc -c -g -Wall department.c
	gcc -c -g -Wall commands.c
	gcc -c -g -Wall student.c