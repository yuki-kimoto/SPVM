This is SPVM solo test program

## Run

   # Normal run
   perl solo/solo_Makefile.PL && yacc/bison.sh && make -f solo/Makefile && ./solo/spvm_main TestCase

   # Debug run
   perl solo/solo_Makefile.PL && yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG && ./solo/spvm_main TestCase
