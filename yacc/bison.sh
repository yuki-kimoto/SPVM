#/usr/bin/sh

bison -o lib/SPVM/Builder/src/spvm_yacc.c --defines=lib/SPVM/Builder/include/spvm_yacc.h -t -p SPVM_yy -d yacc/spvm_yacc.y
