#CFLAGS=$(OPTIM) $(CFLAGS1) $(EXTRA_CFLAGS)
#LIBS=$(EXTRA_LIBS) $(LIBS1)
#INCLUDES=$(INCLUDES1) $(INCLUDES0) $(EXTRA_INCLUDES)
#LDFLAGS=$(LDFLAGS1) $(EXTRA_LDFLAGS)

RM=@RM@
CC=@CC@
RANLIB=@RANLIB@
CFLAGS=@CFLAGS@ @OPTIM@
LIBS=@LIBS@
LDFLAGS=@LDFLAGS@ $(LIBS)
INCDIR=../../include
INCDIR1=../../../include
INCDIR2=../../file_io/beos
INCLUDES=-I$(INCDIR) -I$(INCDIR1) -I$(INCDIR2) -I.

LIB=../libsig.a

OBJS=signal.o \

.c.o:
	$(CC) $(CFLAGS) -c $(INCLUDES) $<

all: $(LIB)

clean:
	$(RM) -f *.o *.a *.so

distclean: clean
	-$(RM) -f Makefile

$(OBJS): Makefile

$(LIB): $(OBJS)
	$(RM) -f $@
	$(AR) cr $@ $(OBJS)
	$(RANLIB) $@

#
# We really don't expect end users to use this rule.  It works only with
# gcc, and rebuilds Makefile.tmpl.  You have to re-run Configure after
# using it.
#
depend:
	cp Makefile.in Makefile.in.bak \
	    && sed -ne '1,/^# DO NOT REMOVE/p' Makefile.in > Makefile.new \
	    && gcc -MM $(INCLUDES) $(CFLAGS) *.c >> Makefile.new \
	    && sed -e '1,$$s: $(INCDIR)/: $$(INCDIR)/:g' \
	           -e '1,$$s: $(OSDIR)/: $$(OSDIR)/:g' Makefile.new \
		> Makefile.in \
	    && rm Makefile.new

# DO NOT REMOVE
signal.o: signal.c ../../../include/apr_general.h \
 $(INCDIR)/apr_config.h ../../../include/apr_errno.h
