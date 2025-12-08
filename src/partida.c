#include "partida.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ***** STRUCTS DECLARATION *****

// --- MATCHES STRUCTS ---
// TAD Match info
struct match {        
    int id;                     // Match ID int
    int id_team1;                  // Team1 ID int
    int id_team2;                  // Team2 ID int
    int goals_team1;            // Team1 goals in match int
    int goals_team2;            // Team2 goals in match int
};


// ***** VAR INITIATION FUNCTIONS *****
// --- returns pointer to Match with all values ---
Match *create_match(int id, int id_team1, int id_team2, int goals_team1, int goals_team2)
{
    Match *p = malloc(sizeof(struct match));

    if (p == NULL)
    {
        printf("Erro de alocação de memória da partida\n");
        return NULL;
    }
    p->id = id;
    p->id_team1 = id_team1;
    p->id_team2 = id_team2;
    p->goals_team1 =goals_team1;
    p->goals_team2 = goals_team2;
    
    return p;
}

// ***** VAR manipulation FUNCTIONS *****
// --- free memory in pointer p ---
void delete_match(Match* p)
{
    free(p);
}

// --- Change match id ---
void change_matchid(Match* p, int new_id)
{
    p->id = new_id;
}


// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- Returns match id ---
int match_id(Match* p)
{
    return p->id;
}

// --- Returns match team1 id ---
int match_id_team1(Match* p)
{
    return p->id_team1;
}

// --- Returns match team2 id ---
int match_id_team2(Match* p)
{
    return p->id_team2;
}

// --- Returns team1 goals ---
int match_goals_team1(Match* p)
{
    return p->goals_team1;
}

// --- Returns team2 goals ---
int match_goals_team2(Match* p)
{
    return p->goals_team2;
}
