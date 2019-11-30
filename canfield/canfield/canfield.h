extern char suitmap[4], colormap[4], pilemap[4];
extern bool mtfdone, Cflag;
extern int status;
extern bool startedgame, infullgame;
extern int dbfd;
extern const char *const basicinstructions[];
extern const char *const bettinginstructions[];

#define decksize        52
#define originrow       0
#define origincol       0
#define basecol         1
#define boxcol          42
#define tboxrow         2
#define bboxrow         17
#define movecol         43
#define moverow         16
#define msgcol          43
#define msgrow          15
#define titlecol        30
#define titlerow        0
#define sidecol         1
#define ottlrow         6
#define foundcol        11
#define foundrow        3
#define stockcol        2
#define stockrow        8
#define fttlcol         10
#define fttlrow         1
#define taloncol        2
#define talonrow        13
#define tabrow          8
#define ctoprow         21
#define cbotrow         23
#define cinitcol        14
#define cheightcol      1
#define cwidthcol       4
#define handstatrow     21
#define handstatcol     7
#define talonstatrow    22
#define talonstatcol    7
#define stockstatrow    23
#define stockstatcol    7
#define Ace             1
#define Jack            11
#define Queen           12
#define King            13
#define atabcol         11
#define btabcol         18
#define ctabcol         25
#define dtabcol         32

#define spades          's'
#define clubs           'c'
#define hearts          'h'
#define diamonds        'd'
#define black           'b'
#define red             'r'

#define stk             1
#define tal             2
#define tab             3
#define INCRHAND(row, col) {\
        row -= cheightcol;\
        if (row < ctoprow) {\
                row = cbotrow;\
                col += cwidthcol;\
        }\
}
#define DECRHAND(row, col) {\
        row += cheightcol;\
        if (row > cbotrow) {\
                row = ctoprow;\
                col -= cwidthcol;\
        }\
}


struct cardtype {
        char suit;
        char color;
        bool visible;
        bool paid;
        int rank;
        struct cardtype *next;
};

#define NIL     ((struct cardtype *) -1)

extern struct cardtype *deck[decksize];
extern struct cardtype cards[decksize];
extern struct cardtype *bottom[4], *found[4], *tableau[4];
extern struct cardtype *talon, *hand, *stock, *basecard;

extern int length[4];
extern int cardsoff, base, cinhand, taloncnt, stockcnt, timesthru;
extern char srcpile, destpile;
extern int mtforigin, tempbase;
extern int coldcol, cnewcol, coldrow, cnewrow;
extern bool errmsg, done;
extern int uid;
extern struct betinfo this, game, total;

/*
 * Basic betting costs
 */
#define costofhand              13
#define costofinspection        13
#define costofgame              26
#define costofrunthroughhand     5
#define costofinformation        1
#define secondsperdollar        60
#define maxtimecharge            3
#define valuepercardup           5
/*
 * Variables associated with betting
 */
struct betinfo {
        long    hand;           /* cost of dealing hand */
        long    inspection;     /* cost of inspecting hand */
        long    game;           /* cost of buying game */
        long    runs;           /* cost of running through hands */
        long    information;    /* cost of information */
        long    thinktime;      /* cost of thinking time */
        long    wins;           /* total winnings */
        long    worth;          /* net worth after costs */
};

extern time_t acctstart;
