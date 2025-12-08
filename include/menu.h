#ifndef MENU_H
#define MENU_H


// ***** ONLY OUTPUT FUNCTIONS *****
// --- Show menu and options ---
void show_menu();

// --- Pause screen ---
void pause_screen();

// --- Clear screen ---
void clear_screen();


// ***** USER OPTIONS FUNCTIONS *****
// --- Consult team by prefix (case insensitive) ---
void option_consult_team(BDTeams *bdt);

// --- Consult team by prefix (case insensitive) ---
void option_consult_match(BDMatches *bdp, BDTeams *bdt);

// --- Consult match by prefix or id (case insensitive) ---
void option_insert_match(BDMatches *bdp, BDTeams *bdt);

// --- Update match ---
void option_update_match(BDMatches *bdp, BDTeams *bdt);

// --- Remove match ---
void option_remove_match(BDMatches *bdp, BDTeams *bdt);


// --- Matches in home prefix ---
void matches_home(BDTeams *bdt, BDMatches *bdm);


// --- BDTeams by prefix ---
BDTeams *bdteams_by_prefix(BDTeams *bdt);


// --- Print table, sorted by points, victories, goals balance,  ---
void option_print_classification(BDTeams *bdt);



// --- Updates every team info in BDteams using all matches ---
void bdpartidas_increase_in_team(BDMatches *bdm, BDTeams *bdt);

// --- BDTeams by prefix ---
BDTeams *bdteams_by_prefix(BDTeams *bdt);

// ***** SCREEN FUNCTIONS *****
// --- Pause screen ---
void pause_screen();

// --- Clear screen ---
void clear_screen();


#endif