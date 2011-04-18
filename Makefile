CC=g++
COPTS=-g -Wall
ALL=fturtlec

all: $(ALL)

JUNK=*.o *~ *.dSYM *.tab.* lex.yy.c*

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

fturtlec: fturtlec.ypp fturtlec.l Type.o Symbol.o Expr.o Func.o Error.h
	bison -d fturtlec.ypp
	flex fturtlec.l
	$(CC) $(COPTS) fturtlec.tab.cpp lex.yy.c Type.o Symbol.o Expr.o Func.o -lfl -o $@
