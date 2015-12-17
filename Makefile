GLIB2_CFLAGS = $(shell pkg-config --cflags glib-2.0)
PIDGIN_LIBDIR = $(shell pkg-config --variable=libdir pidgin)/pidgin

CFLAGS=-fPIC -DPURPLE_PLUGINS -I/usr/include/libpurple -Waggregate-return -Wcast-align -Wdeclaration-after-statement -Wendif-labels -Werror-implicit-function-declaration -Wextra -Wno-sign-compare -Wno-unused-parameter -Wformat -Wformat-security -Winit-self -Wmissing-declarations -Wmissing-noreturn -Wmissing-prototypes -Wpointer-arith -Wundef -Wp,-D_FORTIFY_SOURCE=2 -pthread -O2 $(GLIB2_CFLAGS)

all:	ponger.so

clean:
	rm -f ponger.o ponger.so

ponger.so:	ponger.o
	gcc -shared ponger.o -o $@

install-home:	ponger.so
	mkdir -p ~/.purple/plugins
	cp ponger.so ~/.purple/plugins

install:	$(DESTDIR)/$(PIDGIN_LIBDIR)/ponger.so

$(DESTDIR)/$(PIDGIN_LIBDIR)/ponger.so:ponger.so
	install -D $< $@

rpm:	rpmbuild/SOURCES/pidgin-ponger.tar.gz
	rpmbuild --define "_topdir `pwd`/rpmbuild" -ta $<

rpmbuild/SOURCES/pidgin-ponger.tar.gz:	FORCE
	@mkdir -p rpmbuild/SOURCES
	#git archive --format=tgz --prefix=pidgin-ponger/ HEAD >$@
	tar --transform 's,^,pidgin-ponger/,S' -zcf $@ `git ls-files`

FORCE:
