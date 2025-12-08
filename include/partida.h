#ifndef PARTIDAS_H
#define PARTIDAS_H

// ***** STRUCTS DECLARATION *****
// --- TEAMS STRUCTS ---
// TAD partida info
typedef struct match Match;


// ***** VAR INITIATION FUNCTIONS *****
// --- returns pointer to Match with all values ---
Match *create_match(int id, int id_team1, int id_team2, int goals_team1, int goals_team2);


// ***** VAR manipulation FUNCTIONS *****
// --- free memory in pointer p ---
void delete_match(Match *p);

// --- Change match goals scored ---
void update_match(Match* p, int goals1, int goals2);

// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- Returns match id ---
int match_id(Match *p);

// --- Returns match team1 id ---
int match_id_team1(Match *p);

// --- Returns match team2 id ---
int match_id_team2(Match *p);

// --- Returns team1 goals ---
int match_goals_team1(Match *p);

// --- Returns team2 goals ---
int match_goals_team2(Match *p);


#endif
