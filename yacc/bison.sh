#/usr/bin/sh

bison -t -p SPVM_yy -d yacc/spvm_yacc.y
mv -f spvm_yacc.tab.c spvm_yacc.c
mv -f spvm_yacc.tab.h spvm_yacc.h
