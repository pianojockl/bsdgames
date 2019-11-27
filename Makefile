#	@(#)Makefile	8.2 (Berkeley) 3/31/94
# $FreeBSD: src/games/Makefile,v 1.16 1999/08/27 23:28:45 peter Exp $

SUBDIR= adventure \
	arithmetic \
	atc \
	backgammon \
	battlestar \
	bcd \
	bs \
	boggle \
	canfield \
	cribbage \
	colorbars \
	fish \
	hack \
	hals_end \
	hangman \
	hunt \
	larn \
	mille \
	phantasia \
	pig \
	ppt \
	quiz \
	rain \
	robots \
	rogue \
	sail \
	snake \
	tetris \
	trek \
	wargames \
	worm \
	worms \
	wump

# Included, but not to be compiled:
# banner, caesar, factor, fortune, grdc, morse, number, pom, primes, random

# maximum parallelism
#
SUBDIR_ORDERED=

.include <bsd.subdir.mk>
