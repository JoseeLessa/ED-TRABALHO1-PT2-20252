#ifndef TIME_H
#define TIME_H

// ***** STRUCTS DECLARATION *****

// --- TEAMS STRUCTS ---
// TAD Team info
typedef struct team Team;


// ***** VAR INITIATION FUNCTIONS *****
// --- returns pointer to Team with 0 in all values ---
Team *team_create();


// ***** VAR MANIPULATION FUNCTIONS *****
// --- free memory in pointer p ---
void delete_team(Team* p);


// ***** TEAM OPERATION FUNCTIONS *****
// --- set Team values to 0 --- 
void team_reset_stats(Team *t);

// --- Add values to goals and match result --- 
void team_add_match(Team *t, int goals_scored, int goals_conceded);

// --- Add Name and id to team ---
void assign_idname(Team *team, int id, char name[]);


// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- Returns team id ---
int team_id(Team *t);

// --- Returns team name ---
char *team_name(Team *t);

// --- Returns team wins ---
int team_w(Team *t);

// --- Returns team draws ---
int team_d(Team *t);

// --- Returns team losses ---
int team_l(Team *t);

// --- Returns team goals scored ---
int team_gs(Team *t);

// --- Returns team goals conceded ---
int team_gc(Team *t);

// --- Return team goal balance ---
int team_balance(Team *t);

// --- Return total points made by a team ---
int team_points(Team *t);


// ***** SORTING FUNCTIONS *****
// --- Sort criteria ---
int is_better(Team *a, Team *b);

#endif