# AM_CFLAGS = -Wall -I$(top_builddir) -I$(top_builddir)/test -std=c++11
AM_CXXFLAGS = -Wall -std=c++11
AM_CXXFLAGS += -I$(top_builddir)
AM_CXXFLAGS += -I$(top_builddir)/test

noinst_PROGRAMS = test.out
test_out_SOURCES = test.cc \
	catch.hpp

test_out_LDADD = $(top_builddir)/src/libsnd.a $(AM_LDFLAGS)

check_PROGRAMS = $(bin_PROGRAMS)
TESTS = $(check_PROGRAMS)

test: $(check_programs)
	chmod +x ./unit.test && ./unit.test
