BUILT_SOURCES =
MOSTLYCLEANFILES =
include $(top_srcdir)/gnuscripts/lalsuite_header_links.am
include $(top_srcdir)/gnuscripts/lalsuite_vcs_info.am

SUBDIRS = \
	std \
	tools \
	factories \
	vectorops \
	utilities \
	stats \
	inject \
	date \
	tdfilter \
	window \
	fft \
	noisemodels \
	. \
	support \
	$(END_OF_LIST)

lib_LTLIBRARIES = liblal.la

pkginclude_HEADERS = \
	LALConfig.h \
	LALVCSInfo.h \
	LALVCSInfoHeader.h \
	$(END_OF_LIST)

liblal_la_SOURCES = \
	LALMisc.c \
	LALVCSInfo.c \
	$(END_OF_LIST)

nodist_liblal_la_SOURCES = LALBuildInfo.c

liblal_la_DEPENDENCIES = \
	std/libstd.la \
	tools/libtools.la \
	factories/libfactories.la \
	vectorops/libvectorops.la \
	utilities/libutilities.la \
	stats/libstats.la \
	inject/libinject.la \
	date/libdate.la \
	tdfilter/libtdfilter.la \
	window/libwindow.la \
	fft/libfft.la \
	noisemodels/libnoisemodels.la \
	$(END_OF_LIST)

liblal_la_LIBADD = $(liblal_la_DEPENDENCIES)
liblal_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(LIBVERSION)

EXTRA_DIST = \
	config.h.in \
	simd_dispatch.h \
	$(END_OF_LIST)

DISTCLEANFILES = config.h

vcs_info_sources = LALVCSInfoHeader.h
build_info_source = LALBuildInfo.c
$(build_info_source): $(liblal_la_DEPENDENCIES)

bin_PROGRAMS = \
	lal-simd-detect \
	lal-version \
	$(END_OF_LIST)

lal_version_SOURCES = lal-version.c
lal_version_LDADD = liblal.la

lal_simd_detect_SOURCES = lal-simd-detect.c
lal_simd_detect_LDADD = liblal.la

TESTS = $(bin_PROGRAMS)
