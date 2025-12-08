#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H

// ***** STRUCTS DECLARATION *****
// --- MATCHES STRUCTS ---
// TAD BDMatches
typedef struct bdmatches BDMatches;

// Matches Node
typedef struct match_node MNode;


// ***** VAR INITIATION FUNCTIONS *****
// --- Creates pointer to BDTeam struct ---
BDMatches *bdmatches_create();

// --- Create node ---// --- Create node 2.0 ---
MNode *create_mnode_with_vals(int id, int id_team1, int id_team2, int goals_team1, int goals_team2);

// --- Copy node ---
void append_mnode_copy(BDMatches *bdm, MNode *n);

// --- Remove Node ---
void explode_mnode_by_id(BDMatches *bdm, int id);


// ***** VAR manipulation FUNCTIONS *****
// --- free memory in pointer p ---
void delete_all_matches(BDMatches *bdm);

// --- update match values ---
void update_match_by_id(BDMatches *bdm, int id, int goals1, int goals2);


// ***** Printing Functions *****
// ---  Print Match ---
void print_match(MNode *ptr, char nome1[], char nome2[]);


// ***** SEARCH FUNCTIONS *****
// ---  Search using ID ---
MNode *bdmatches_search_by_id(BDMatches *bdp, int id);

// --- Search for id and return int if exists in bdt ---
int id_in_bdm(BDMatches *bdm, int id);


// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- is BDMatches Empty? ---
int bdm_is_empty(BDMatches *bdm);

// --- is BDMatches Empty? ---
MNode *first_node(BDMatches *bdm);

// --- Mnode->next ---
MNode *next_node(MNode *mn);

// --- change all vals to match values ---
void match_vals(MNode *mn, int *id, int *id1, int *id2, int *goals1, int *goals2);

// --- Number of elements em bdm ---
int new_id_bdm(BDMatches *bdm);


// ***** ARCHIVE LOADING FUNCTIONS *****
// ---  Loads from path to *BDPartidas ---
void bdpartidas_load_csv(BDMatches *bdm, const char path[]);


#endif
