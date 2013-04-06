.SUFFIXES:
.SECONDARY:

######### directories
bindir := bin
objdir := obj
srcdir := src
logdir := log
miscdir := misc

target := $(bindir)/Crocodin
srcs := $(wildcard $(srcdir)/*.cpp)
objs := $(patsubst $(srcdir)/%.cpp, $(objdir)/%.o, $(srcs))

######### programs
SHELL = /bin/sh
compile = $(strip g++ -c $< -o $@ $(cppflags) $(cxxflags))
link = $(strip g++ $^ -o $@ $(cxxflags) $(ldflags))
memcheck = valgrind $(memcheckflags) $(target) 2>&1 | tee $(logdir)/memcheck.txt
rm := rm -f
mkdir := mkdir -p

######### pkg-config dependencies
pkgdepend := \
	sfml-window \
	sfml-system \
	sfml-graphics

######### compiler flags
cppflags := \
	-Wall -Wextra -Wno-unused-parameter \
	-MMD -MP \
	$(shell pkg-config $(pkgdepend) --cflags-only-I)

######### flags to both compiler and linker
cxxflags := \
	-O0 -g \
	-fmessage-length=0 \
	$(shell pkg-config $(pkgdepend) --cflags-only-other)

######### linker flags
ldflags := \
	-rdynamic \
	$(shell pkg-config $(pkgdepend) --libs)

######### valgrind flags
memcheckflags := \
	--leak-check=full \
	--num-callers=32 \
	--gen-suppressions=all \
	--suppressions=$(miscdir)/memcheck.supp

######### make targets
.PHONY: all
all: $(target)

.PHONY: check
check: all
	./$(target)

.PHONY: memcheck
memcheck: all | $(logdir)
	$(memcheck)

PHONY: clean
clean:
	$(rm) -R $(objdir)
	$(rm) -R $(bindir)
	$(rm) -R $(logdir)

######### build rules
$(bindir)/%: $(objs) | $(bindir)
	$(link)

$(objdir)/%.o: $(srcdir)/%.cpp $(MAKEFILE_LIST) | $(objdir)
	$(compile)

$(objdir) $(bindir) $(logdir):
	$(mkdir) $@

######### dependency tracking
-include $(wildcard $(objdir)/*.d)
