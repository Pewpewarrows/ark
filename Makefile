APP = Ark

CXX := clang++
SRCEXT = cc
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = inc
LIBS =
LIBDIR =
FWS = OpenGL SFML sfml-graphics sfml-window sfml-system sfml-audio sfml-network

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))

DEBUG = -g
INCLUDES = $(addprefix -I,$(INCDIR))
LIBRARIES = $(addprefix -l,$(LIBS))
LIBRARYDIR = $(addprefix -L,$(LIBDIR))
FRAMEWORKS = $(addprefix -framework ,$(FWS))

# -stdlib=libc++
CFLAGS = -Wall -pedantic -ansi -stdlib=libc++ -c $(DEBUG) $(INCLUDES) $(LIBRARIES) $(LIBRARYDIR)
LDFLAGS = -stdlib=libc++ $(FRAMEWORKS)

ifeq ($(SRCEXT), cc)
	CC = $(CXX)
else
	CFLAGS += -std-gnu99
endif

.PHONY: all clean distclean run git_clean

all: build_engine

build_engine: $(BINDIR)/$(APP)

$(BINDIR)/$(APP): buildrepo $(OBJS)
	@mkdir -p `dirname $@`
	@echo "Linking $@..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.$(SRCEXT)
	@echo "Generating dependencies for $<..."
	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJDIR)

distclean: clean
	$(RM) -r $(BINDIR)

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef

# usage: $(call make-depend,source-file,object-file,depend-file)
define make-depend
  $(CC) -MM       \
        -MF $3    \
        -MP       \
        -MT $2    \
        $(CFLAGS) \
        $1
endef

# build_all:
# 	pelican -s conf/settings.py src

# build_live:
# 	pelican -r -s conf/settings.py src

# develop:
# 	mkvirtualenv mml_redux
# 	~/.virtualenvs/mml_redux/bin/pip install -r conf/requirements.txt

run:
	./bin/Ark

# deploy:
# 	git push --all

# freeze:
# 	pip freeze -l | sort > conf/requirements.txt

git_clean:
	git clean -f
	rm -rf bin
