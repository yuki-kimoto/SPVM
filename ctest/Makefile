
all:
	cc -c  -fno-strict-aliasing -pipe -fstack-protector -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_FORTIFY_SOURCE=2 -std=c99 -O3 -I ../lib/SPVM/Builder/include -o spvm_list.o ../lib/SPVM/Builder/src/spvm_list.c
	cc -c  -fno-strict-aliasing -pipe -fstack-protector -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_FORTIFY_SOURCE=2 -std=c99 -O3 -I ../lib/SPVM/Builder/include -o spvm_hash.o ../lib/SPVM/Builder/src/spvm_hash.c

test:
	t/spvm_t_list
	t/spvm_t_hash

clean:
	rm -f t/spvm_t_list
	rm -f t/spvm_t_hash
	rm -f spvm_list.o
	rm -f spvm_hash.o
	rm -f Makefile
