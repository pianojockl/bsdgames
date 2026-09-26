# bsdgames #
bsdgames sources, primarily for the FreeBSD port games/bsdgames

this is an effort to bring everything up to date, fix some bugs, maybe add some games from the original distribution that are missing in the dragonflybsd distribution.
please see TODO.md for more details.

**any help is highly welcome!!**

compiled from these sources:
* http://deb.debian.org/debian/pool/main/b/bsdgames/bsdgames_2.17.orig.tar.gz
* https://github.com/DragonFlyBSD/DragonFlyBSD/tree/v5.7.0/games
* https://ibiblio.org/pub/linux/games/bsd-games-2.17.tar.gz

## Building ##

These old sources rely on tentative definitions (common symbols), which
modern compilers (clang >= 11, gcc >= 10) no longer emit by default. Without
`-fcommon` the link step fails with "duplicate symbol" errors. The FreeBSD
port sets it in its Makefile; for an in-tree build use `make CC="cc -fcommon"`.
