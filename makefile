.SUFFIXES:
.SECONDARY:

######### directories
bindir := bin
objdir := obj
srcdir := src

target := $(bindir)/Crocodin
srcs := $(wildcard $(srcdir)/*.cpp)
objs := $(patsubst $(srcdir)/%.cpp, $(objdir)/%.o, $(srcs))

######### programs
SHELL = /bin/sh
compile = $(strip g++ -c $< -o $@ $(cppflags) $(cxxflags))
link = $(strip g++ $^ -o $@ $(cxxflags) $(ldflags)) 
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
	-g \
	-fmessage-length=0 \
	$(shell pkg-config $(pkgdepend) --cflags-only-other)

######### linker flags
ldflags := \
	-rdynamic \
	$(shell pkg-config $(pkgdepend) --libs)

######### make targets
.PHONY: all
all: $(target)

.PHONY: test
test: all
	./$(target)

.PHONY: clean
clean:
	$(rm) -R $(objdir)
	$(rm) -R $(bindir)

######### build rules
$(bindir)/%: $(objs) | $(bindir)
	$(link)

$(objdir)/%.o: $(srcdir)/%.cpp $(MAKEFILE_LIST) | $(objdir)
	$(compile)

$(objdir) $(bindir):
	$(mkdir) $@

######### dependency tracking
-include $(wildcard $(objdir)/*.d)
