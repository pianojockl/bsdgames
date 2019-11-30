#define MAXPLAYERS 256

struct  player  {
        short   uids;
        short   scores;
        char    *name;
};

extern const char *recfile;
extern struct player players[MAXPLAYERS], temp;
extern struct player players[MAXPLAYERS], temp;

