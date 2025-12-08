#include "time.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


// ***** STRUCTS DECLARATION *****
// --- TEAMS STRUCTS ---
// TAD Team info
struct team {          
    int id;                    // Team ID int
    char name[64];             // Team name
    int w;                     // Victories
    int d;                     // Draws
    int l;                     // Losses
    int gs;                    // Goals scored
    int gc;                    // Goals conceded
} ;


// ***** VAR INITIATION FUNCTIONS *****
// --- return a Team var with 0 in all values ---
Team *team_create()
{
    Team *t = (Team *)malloc(sizeof(Team));
    t->w = 0;       // victories
    t->d = 0;       // draws
    t->l = 0;       // losses
    t->gs = 0;
    t->gc = 0;
    
    return t;
}


// ***** VAR MANIPULATION FUNCTIONS *****
// --- free memory in pointer p ---
void delete_team(Team* p){
    free(p);
}


// ***** OPERATION FUNCTIONS *****

// --- set Team values to 0 ---
void team_reset_stats(Team *t)
{ 
    t->w = 0; t->d = 0; t->l = 0; t->gs = 0; t->gc = 0;
}

// --- Add values to goals and match result ---
void team_add_match(Team *t, int goals_scored, int goals_conceded) 
{
    t->gs += goals_scored;
    t->gc += goals_conceded; 

    if (goals_scored > goals_conceded) 
    {
        t->w++;
    } else if (goals_scored == goals_conceded) {
        t->d++;
    } else {
        t->l++;
    }
}

// -- Add values to id and name ---
void assign_idname(Team *team, int id, char name[])
{
    team->id = id;
    strcpy(team->name, name);
}


// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- Returns team id ---
int team_id(Team *t)
{
    return t->id;
}

// --- Returns team name ---
char *team_name(Team *t)
{
    return t->name;
}

// --- Returns team wins ---
int team_w(Team *t)
{
    return t->w;
}

// --- Returns team draws ---
int team_d(Team *t)
{
    return t->d;
}

// --- Returns team losses ---
int team_l(Team *t)
{
    return t->l;
}

// --- Returns team goals scored ---
int team_gs(Team *t)
{
    return t->gs;
}

// --- Returns team goals conceded ---
int team_gc(Team *t)
{
    return t->gc;
}

// --- Return team goal balance ---
int team_balance(Team *t)
{
    return t->gs - t->gc;
}

// --- Return total points made by a team ---
int team_points(Team *t)
{     
    return t->w * 3 + t->d;
}


// ***** SORTING FUNCTIONS *****
// --- Sort criteria ---
int is_better(Team *a, Team *b)
{
    // 1. Pontos
    if (team_points(a) != team_points(b))
        return team_points(a)>team_points(b);  // decrescente

    // 2. Vitórias
    if (team_w(a) != team_w(b))
        return team_w(a) > team_w(b);

    // 3. Saldo de gols
    if (team_balance(a) != team_balance(b))
        return team_balance(a) > team_balance(b);

    // 4. Gols marcados
    if (team_gs(a) != team_gs(b))
        return team_gs(a) > team_gs(b);

    return 0;
}


