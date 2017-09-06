GAMBITFILES := $(shell find $(SRCDIR)/modules/gambit -type f -name *.$(SRCEXT))
DEBUGFILES := $(shell find $(SRCDIR)/dev/debugnew -type f -name *.$(SRCEXT))
INSTRFILES := $(shell find $(SRCDIR)/generator -type f -name *.$(SRCEXT))

parser: $(SRCDIR)/modules/gambit/grammar/parser.yy
	bison -d -v $(SRCDIR)/modules/gambit/grammar/parser.yy -o $(SRCDIR)/modules/gambit/parser.tab.cpp
	#$(CC) $(CFLAGS) $(INC) -c -o $(BUILDDIR)/parser.o $(SRCDIR)/modules/gambit/parser.tab.cpp

lexer: $(SRCDIR)/modules/gambit/grammar/lexer.l
	flex --outfile=$(SRCDIR)/modules/gambit/lexer.yy.cpp  $<
	#$(CC)  $(CFLAGS) $(INC) -c src/modules/gambit/lexer.yy.cpp -o $(BUILDDIR)/lexer.o

gambit_parser: parser lexer
	$(CC) $(CXXSTD) $(INC) $(DYNLIBPARAM) $(GAMBITFILES) $(DEBUGFILES) $(INSTRFILES) -o $(LIBDIR)/gambit.so