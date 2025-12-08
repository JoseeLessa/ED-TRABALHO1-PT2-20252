#ifndef BDTIMES_H
#define BDTIMES_H


// ***** STRUCTS DECLARATION *****
// TAD BDTeam
typedef struct bdteams BDTeams;

// TAD BDTeam Node
typedef struct node Node;

// ***** VAR INITIATION FUNCTIONS *****
// ---  Creates pointer to BDTeam struct ---
BDTeams *bdteams_create();


// ***** VAR MANIPULATION FUNCTIONS *****
// --- free memory in pointer p ---
void free_bdteams(BDTeams *bdt);

// --- Insert match result in team with node ---
void node_add_match(Node *t, int goals1, int goals2);


// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- is BD Empty? ---
int bd_is_empty(BDTeams *bdt);

// --- size of BDTeams ---
int bdteams_size(BDTeams *bdt);

// --- Returns node team name ---
char *node_team_name(Node *n);


void print_teams(BDTeams *bdt);


// ***** ARCHIVE LOADING FUNCTIONS *****
// ---  Loads from path to *BDTeams ---
void bdteams_load_csv(BDTeams *bd, const char *path);


// ***** SEARCH FUNCTIONS *****
// ---  Search using ID ---
Node *bdteams_search_by_id(BDTeams *bd, int id);

// ---  Search using a prefix string (case-insensitive) Returns BDTeams with all teams found ---
BDTeams *bdteams_search_by_prefix(BDTeams *bd, const char *prefixo);

// --- Search for id and return int if exists in bdt ---
int id_in_bdt(BDTeams *bd, int id);


// ***** SORTING FUNCTIONS *****
// --- Sort BDTeams ---
BDTeams *sort_bdteams(BDTeams *bdt);

// ***** Printing Functions *****
// --- Print Team ---
void print_team(Node *ptr);

// --- Print table ---
void bdteams_print_table(const BDTeams *bd);


// ***** BD UPDATE FUNCTIONS *****
// --- Clear all teams data ---
void reset_bdteams(BDTeams *bdt);



// ***** UTENSILS FUNCTIONS *****
// --- is prefix? (case insensitive) ---
int is_prefix_ascii(const char *a, const char *b);


#endif