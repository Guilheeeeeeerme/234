all: clean
	gcc -c array.c -o obj/Debug/array.o
	gcc -c btree.c -o obj/Debug/btree.o
	gcc -c btree-node.c -o obj/Debug/btree-node.o
	gcc -c rbtree.c -o obj/Debug/rbtree.o
	gcc -c rbtree-node.c -o obj/Debug/rbtree-node.o
	gcc -c main.c -o obj/Debug/main.o
	gcc obj/Debug/array.o obj/Debug/btree-node.o obj/Debug/btree.o obj/Debug/main.o obj/Debug/rbtree-node.o obj/Debug/rbtree.o -o b_tree
clean:
	del /s /q obj\*.o || rm -rf obj/Debug/*.o || exit 0
run: all
	b_tree.exe