This is SPVM solo test program

## Run

   # Normal run
   perl solo/solo_Makefile.PL && yacc/bison.sh && make -f solo/Makefile && ./solo/spvm_main TestCase

   # Debug run - Print AST, package information, operaion codes
   perl solo/solo_Makefile.PL --debug-dump --debug-object-count && yacc/bison.sh && make -f solo/Makefile && ./solo/spvm_main TestCase

   # Debug run - Print yacc result
   perl solo/solo_Makefile.PL --debug-yacc && yacc/bison.sh && make -f solo/Makefile && ./solo/spvm_main TestCase
