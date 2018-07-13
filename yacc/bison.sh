#/usr/bin/sh

bison -t -p SPVM_yy -d yacc/spvm_yacc.y
mv -f spvm_yacc.tab.c lib/SPVM/Build/src/spvm_yacc.c
mv -f spvm_yacc.tab.h lib/SPVM/Build/include/spvm_yacc.h
