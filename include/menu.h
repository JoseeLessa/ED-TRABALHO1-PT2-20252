#ifndef MENU_H
#define MENU_H

#include "bdtimes.h"
#include "bdpartidas.h"

// ***** ONLY OUTPUT FUNCTIONS *****
// --- Show menu and options ---
void show_menu();

// --- Pause screen ---
void pause_screen();

// --- Clear screen ---
void clear_screen();


// ***** USER OPTIONS FUNCTIONS *****

// ***** OPTION 1 - FUNCTIONS *****
// --- Consult team by prefix (case insensitive) ---
void option_consult_team(BDTeams *bdt);


// ***** OPTION 2 - FUNCTIONS *****
// --- Consult match by prefix ---
int option_consult_match(BDMatches *bdm, BDTeams *bdt);

// --- home matches with prefix ---
void home_matches(BDTeams *bdt, BDTeams *filtro, BDMatches *bdm);

// --- away matches with prefix ---
void away_matches(BDTeams *bdt, BDTeams *filtro, BDMatches *bdm);

// --- matches with prefix ---
void matches(BDTeams *bdt, BDTeams *filtro, BDMatches *bdm);


// ***** OPTION 3 - FUNCTIONS *****
// --- Update match ---
void option_update_match(BDMatches *bdp, BDTeams *bdt);


// ***** OPTION 4 - FUNCTIONS *****
// --- Remove match ---
void option_remove_match(BDMatches *bdp, BDTeams *bdt);


// ***** OPTION 5 - FUNCTIONS *****
// --- Insert new match ---
void option_insert_match(BDMatches *bdp, BDTeams *bdt);


// ***** OPTION 6 - FUNCTIONS *****
// --- Print table, sorted by points, victories, goals balance,  ---
void option_print_classification(BDTeams *bdt);


// ***** UPDATE DBTEAMS *****
// --- Updates every team info in BDteams using all matches ---
void bdpartidas_increase_in_team(BDMatches *bdm, BDTeams *bdt);


#endif
