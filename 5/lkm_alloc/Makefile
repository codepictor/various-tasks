obj-m+=allocator.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) test_allocator.c -o test_allocator
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm test_allocator

