all:
	gcc -c array.c -o array.o
	gcc -c btree.c -o btree.o
	gcc -c btree-node.c -o btree-node.o
	gcc -c rbtree.c -o rbtree.o
	gcc -c rbtree-node.c -o rbtree-node.o
	gcc -c main.c -o main.o
	gcc array.o btree-node.o btree.o main.o rbtree-node.o rbtree.o -o main
clean:
	del /s /q *.o || rm -rf *.o