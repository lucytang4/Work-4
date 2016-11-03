all: dir.c
	gcc dir.c -o dirtest 

run: dirtest
	./dirtest

clean:
	rm ./dirtest
	rm *~