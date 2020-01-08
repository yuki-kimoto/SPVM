
all:
	cc -c  -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -std=c99  -Ilib/SPVM/Builder/include -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers -O3 -o ctest/spvm_list.o lib/SPVM/Builder/src/spvm_list.c
	cc -c  -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -std=c99  -Ilib/SPVM/Builder/include -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers -O3 -o ctest/spvm_hash.o lib/SPVM/Builder/src/spvm_hash.c
	cc -c  -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -std=c99  -Ilib/SPVM/Builder/include -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers -O3 -o ctest/spvm_hash_func.o lib/SPVM/Builder/src/spvm_hash_func.c
	cc -c  -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -std=c99  -Ilib/SPVM/Builder/include -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers -O3 -o ctest/spvm_util_allocator.o lib/SPVM/Builder/src/spvm_util_allocator.c
	cc  -o ctest/t/spvm_t_list ctest/t/spvm_t_list.c ctest/spvm_list.o ctest/spvm_util_allocator.o
	cc  -o ctest/t/spvm_t_hash ctest/t/spvm_t_hash.c ctest/spvm_hash.o ctest/spvm_util_allocator.o ctest/spvm_hash_func.o

test:
	ctest/t/spvm_t_list
	ctest/t/spvm_t_hash

clean:
	rm -f ctest/t/spvm_t_list
	rm -f ctest/t/spvm_t_hash
	rm -f ctest/spvm_list.o
	rm -f ctest/spvm_hash.o
	rm -f ctest/spvm_hash_func.o
	rm -f ctest/spvm_util_allocator.o
