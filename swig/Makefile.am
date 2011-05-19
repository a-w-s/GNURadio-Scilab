
include $(top_srcdir)/Makefile.common

AM_CPPFLAGS += -I$(top_srcdir)/lib

if PYTHON

TOP_SWIG_IFILES = \
	slab.i

slab_la_swig_libadd =		\
	$(top_builddir)/lib/libgnuradio-slab.la

include $(top_srcdir)/Makefile.swig

# add some of the variables generated inside the Makefile.swig.gen
BUILT_SOURCES = $(swig_built_sources)

# Do not distribute the output of SWIG
no_dist_files = $(swig_built_sources)

# additional SWIG files to be installed
slab_swiginclude_headers = \
	slab_sbhs_scilab.i


endif
