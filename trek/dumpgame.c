/*-
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @(#)dumpgame.c	8.1 (Berkeley) 5/31/93
 * $FreeBSD: src/games/trek/dumpgame.c,v 1.6 1999/11/30 03:49:46 billf Exp $
 * $DragonFly: src/games/trek/dumpgame.c,v 1.3 2006/09/07 21:19:44 pavalos Exp $
 */

#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "trek.h"

/***  THIS CONSTANT MUST CHANGE AS THE DATA SPACES CHANGE ***/
#define VERSION		2

struct dump {
	char	*area;
	int	count;
};

static bool readdump(int);
static void fix_dump_pointers(long);

struct dump Dump_template[] = {
	{ (char *)&Ship,	sizeof (Ship)	},
	{ (char *)&Now,		sizeof (Now)	},
	{ (char *)&Param,	sizeof (Param)	},
	{ (char *)&Etc,		sizeof (Etc)	},
	{ (char *)&Game,	sizeof (Game)	},
	{ (char *)Sect,		sizeof (Sect)	},
	{ (char *)Quad,		sizeof (Quad)	},
	{ (char *)&Move,	sizeof (Move)	},
	{ (char *)Event,	sizeof (Event)	},
	{ NULL,			0		}
};

/*
**  DUMP GAME
**
**	This routine dumps the game onto the file "trek.dump".  The
**	first two bytes of the file are a version number, which
**	reflects whether this image may be used.  Obviously, it must
**	change as the size, content, or order of the data structures
**	output change.
*/

void
dumpgame(int v __unused)
{
	int		version;
	int		fd;
	struct dump	*d;
	int		i;

	if ((fd = creat("trek.dump", 0644)) < 0) {
		printf("cannot dump\n");
		return;
	}
	version = VERSION;
	write(fd, &version, sizeof version);

	/* output the main data areas */
	for (d = Dump_template; d->area; d++) {
		write(fd, &d->area, sizeof d->area);
		i = d->count;
		write(fd, d->area, i);
	}

	close(fd);
}


/*
**  RESTORE GAME
**
**	The game is restored from the file "trek.dump".  In order for
**	this to succeed, the file must exist and be readable, must
**	have the correct version number, and must have all the appro-
**	priate data areas.
**
**	Return value is zero for success, one for failure.
*/

bool
restartgame(void)
{
	int	fd;
	int		version;

	if ((fd = open("trek.dump", O_RDONLY)) < 0 ||
	    read(fd, &version, sizeof version) != sizeof version ||
	    version != VERSION ||
	    readdump(fd)) {
		printf("cannot restart\n");
		close(fd);
		return (1);
	}

	close(fd);
	return (0);
}


/*
**  READ DUMP
**
**	This is the business end of restartgame().  It reads in the
**	areas.
**
**	Returns zero for success, one for failure.
*/

static bool
readdump(int fd1)
{
	int		fd;
	struct dump	*d;
	int		i;
	long			junk;
	long			differ = 0;

	fd = fd1;

	for (d = Dump_template; d->area; d++) {
		if (read(fd, &junk, sizeof junk) != (sizeof junk))
			return (1);
		/*
		 * junk is the address the area had in the process that
		 * dumped the game.  All areas live in the same executable
		 * image, so the difference to their address here is the same
		 * for each of them; comparing them also catches a dump that
		 * does not fit this template.
		 */
		if (d == Dump_template)
			differ = (char *)d->area - (char *)junk;
		else if ((char *)d->area - (char *)junk != differ)
			return (1);
		i = d->count;
		if (read(fd, d->area, i) != i)
			return (1);
	}

	fix_dump_pointers(differ);

	/* make quite certain we are at EOF */
	return (read(fd, &junk, 1));
}

/*
**  RELOCATE POINTERS INSIDE THE DUMPED AREAS
**
**	Ship.shipname, the Now.eventptr[] array and the copy of Now that
**	is kept in Etc.snapshot (see events.c and warp.c) hold addresses
**	from the process that dumped the game.  Shift them into this one.
*/

static void
fix_dump_pointers(long differ)
{
	struct event	**epp;
	struct event	*ep;
	char		*snap;
	size_t		off;
	int		i;

	if (Ship.shipname)
		Ship.shipname =
		    (const char *)((intptr_t)Ship.shipname + differ);

	/* pointers into the Event[] array */
	for (epp = Now.eventptr; epp < Now.eventptr + NEVENTS; epp++)
		if (*epp)
			*epp = (struct event *)((intptr_t)*epp + differ);

	/* Etc.snapshot holds a copy of Quad, Event and Now */
	snap = Etc.snapshot + sizeof(Quad) + sizeof(Event);
	off = offsetof(struct Now_struct, eventptr);
	for (i = 0; i < NEVENTS; i++) {
		memcpy(&ep, snap + off + i * sizeof(ep), sizeof(ep));
		if (ep == NULL)
			continue;
		ep = (struct event *)((intptr_t)ep + differ);
		memcpy(snap + off + i * sizeof(ep), &ep, sizeof(ep));
	}
}
