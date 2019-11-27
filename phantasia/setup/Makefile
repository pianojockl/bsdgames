.PATH: ${.CURDIR}/..

PROG=	setup
SRCS=	phantglobs.c setup.c
MK_MAN= no

# for floor()
LDADD+=	-lm

CFLAGS+=-DCOMPILING_SETUP -I${.CURDIR}/..

build-tools: setup.nx

# this setup is used in place, it is not installed anywhere
install:

.include <bsd.prog.mk>
