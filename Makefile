CC=g++ 
COPTS=-g -Wall -std=c++0x
ALL=fturtlec

all: $(ALL)

JUNK=*.o *~ *.dSYM *.tab.* lex.yy.c* *.bc *.s *.ll

clean:
	-rm -rf $(JUNK)

clobber:
	-rm -rf $(JUNK) $(ALL)

.cpp.o:
	$(CC) -c $(COPTS) $<

Type.o: Type.cpp Type.h
Symbol.o: Symbol.cpp Symbol.h Type.h
Expr.o: Expr.cpp Expr.h Type.h Symbol.h
Func.o: Func.cpp Func.h Symbol.h Type.h Expr.h
Label.o: Label.cpp Label.h
Value.o: Value.cpp Value.h

ifeq "$(shell uname)" "Darwin"
LIBS=-lm
else
LIBS=-lfl -lm
endif

fturtlec: fturtlec.ypp fturtlec.l Type.o Symbol.o Expr.o Func.o Error.h Value.o Label.o
	bison -d fturtlec.ypp
	flex fturtlec.l
	$(CC) $(COPTS) fturtlec.tab.cpp lex.yy.c Type.o Symbol.o Expr.o Func.o Value.o Label.o $(LIBS) -o $@
