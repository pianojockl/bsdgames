PROG=	adventure
SRCS=	main.c init.c done.c save.c subr.c vocab.c wizard.c io.c data.c crc.c
MAN=	adventure.6
CLEANFILES=data.c setup

data.c: glorkz setup
	${.CURDIR}/setup ${.CURDIR}/glorkz > data.c

.include <bsd.prog.mk>

SUBDIR=		setup
.include <bsd.subdir.mk>
