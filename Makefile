CC = g++
# debug
CXXFLAGS = -std=c++20 -Wall -Wpedantic -Wextra -O0 -ggdb
# release
# CXXFLAGS = -std=c++20 -Wall -O3 -march=native -mtune=native
# LDFLAGS = -flto=full -fuse-ld=lld
LDFLAGS = -flto=full

OUTNAME = cadaej
EXT = .cpp
SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

RM = rm
DELOBJ = $(OBJ)

DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

all: $(OUTNAME)


$(OUTNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@


-include $(DEP)


$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(OUTNAME)


.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(OUTNAME)$(EXE)

.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)