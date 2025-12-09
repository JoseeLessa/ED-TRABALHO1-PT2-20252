#include "bdtimes.h"
#include "time.h"
#include "bdpartidas.h"
#include "partida.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


// ***** STRUCTS DECLARATION *****

// --- TEAMS STRUCTS ---
// TAD BDTeam
struct bdteams {        
    Node *first;                                    // Pointer to first element in list
} ;

// TAD BDTeam Node
struct node {
    Team *info;
    Node *next;
} ;


// ***** VAR INITIATION FUNCTIONS *****
// --- Creates pointer to BDTeam struct ---
BDTeams *bdteams_create()
{
    BDTeams *bd = (BDTeams *)malloc(sizeof(BDTeams));
    bd->first = NULL;

    return bd;
}

// --- Create node ---
Node *create_node(Team *t)                      // Returns pointer to a List node with values
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->info = t;
    n->next = NULL;
    
    return n;
}

// --- Copy node ---
void append_node_copy(BDTeams *bdt, Node *n)
{
    if (bd_is_empty(bdt))
    {
        bdt->first = create_node(clone_team(n->info));
    } else {
        Node *pos = bdt->first;
        while (pos->next != NULL) pos = pos->next;
        pos->next = create_node(clone_team(n->info));
    }
}


// ***** VAR MANIPULATION FUNCTIONS *****
// --- free Node ---
void free_node(Node *n)
{
    delete_team(n->info);
    free(n);
}

// --- free memory in pointer p ---
void free_bdteams(BDTeams *bdt)
{
    Node *n = bdt->first;
    Node *aux;
    
    while (n != NULL)
    {
        aux = n;
        n = n->next;
        free_node(aux);
    }
    
    free(bdt);
}

// --- Insert match result in team with node ---
void node_add_match(Node *t, int goals1, int goals2)
{
    team_add_match(t->info, goals1, goals2);
}

// --- Remove values from goals and match result ---
void node_sub_match(Node *t, int goals_scored, int goals_conceded)
{
    team_sub_match(t->info, goals_scored, goals_conceded);
}

// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- is BD Empty? ---
int bd_is_empty(BDTeams *bdt)                   // Check if the 'first' pointer is NULL, indicating an empty list
{
   return bdt->first == NULL;
}

// --- size of BDTeams ---
int bdteams_size(BDTeams *bdt)
{
    int i = 0;
    Node *p = bdt->first;
    
    while (p != NULL)
    {
        p = p->next;
        i++;
    }
    return i;
}

// --- Returns node team name ---
char *node_team_name(Node *n)
{
    char *saida = team_name(n->info);
    return saida;
}

// --- Returns team name with ---
char *team_name_by_id(BDTeams *bdt, int id)
{
    if (!id_in_bdt(bdt, id)) return '\0';
    for (Node *n = bdt->first; n != NULL; n = n->next)
    {
        if (team_id(n->info) == id) return node_team_name(n);
    }
}

// --- Returns node team id ---
int node_team_id(Node *n)
{
    int saida = team_id(n->info);
    return saida;
}



// ***** SEARCH FUNCTIONS
// ---  Search using ID ---
Node *bdteams_search_by_id(BDTeams *bd, int id) 
{
    for (Node *ptr = bd->first; ptr!=NULL; ptr = ptr->next) 
    {
        if ( team_id(ptr->info) == id) return ptr;
    }
    return NULL;
}

// ---  Search using a prefix string (case-insensitive) Returns BDTeams with all teams found ---
BDTeams *bdteams_search_by_prefix(BDTeams *bd, const char *prefixo)
{ 
    BDTeams *founds = bdteams_create();
    Node *pos;
    for (Node *ptr = bd->first; ptr != NULL; ptr = ptr->next) 
    {
        if (is_prefix_ascii(prefixo, team_name(ptr->info))) 
        {
            append_node_copy(founds, ptr);
        }
    }
    return founds;
}

// --- Search for id and return int if exists in bdt ---
int id_in_bdt(BDTeams *bd, int id)
{
    for (Node *ptr = bd->first; ptr!=NULL; ptr = ptr->next) 
    {
        if ( team_id(ptr->info) == id) return 1;
    }
    return 0;
}


// ***** SORTING FUNCTIONS *****
// --- Sort BDTeams ---
BDTeams *sort_bdteams(BDTeams *bdt)
{
    BDTeams *sorted = bdteams_create();
    
    int i = 0;
    int size = bdteams_size(bdt);
    
    while ( i < size)
    {
        Node *p = bdt->first;
        while (id_in_bdt(sorted, team_id(p->info)) && p!= NULL) p = p->next;    // First node of bdt not in sorted
        
        for (Node *cmp = bdt->first; cmp != NULL; cmp = cmp->next)
        {
            
            if (!id_in_bdt(sorted, team_id(cmp->info)))
            {
                if (is_better(cmp->info, p->info)) p = cmp;
            }
        }
        append_node_copy(sorted, p);
        i++;
    }
    
    return sorted;
}


// ***** Printing Functions *****
// ---  Print Team ---
void print_team(Node *ptr)
{
        Team *t = ptr->info;
        printf("| %2d | %-19s | %2d | %2d | %2d | %2d | %2d | %4d | %2d |\n",
               team_id(t), team_name(t), team_w(t), team_d(t), team_l(t), team_gs(t), team_gc(t),
              
               team_balance(t), team_points(t));
}

// --- Print table ---
void bdteams_print_table(const BDTeams *bd)
{
    
    const int width = 3;
    const int name_w = 24;
    
    // formato para as tabelinhas
    printf("\n| ID | Time                |  V |  E |  D | GM | GS |   S  | PG |\n");
    printf("|----|---------------------|----|----|----|----|----|------|----|\n");

    for (Node *ptr = bd->first; ptr != NULL; ptr = ptr->next) 
    {
        print_team(ptr);
    }
}


// ***** ARCHIVE LOADING FUNCTIONS *****
// ---  Loads from path to *BDTeams ---
void bdteams_load_csv(BDTeams *bd, const char path[]) 
{ 
    FILE *file = fopen(path, "r");                  // Loads file from path

    if (file == NULL)                               // Verify file
    {
        printf("Error opening file\n");
        return;                                     // Return if error
    }
    
    char line[200];                                 // Sequence of non-blank characters
     
    fgets(line, 200, file);                         // Eliminate the header
    Node *ptr;
    
    while (fgets(line, 200, file) != NULL)          // Returns line or NULL (if reach the end of file)
    {
        Team *t = team_create();
        
        int id;
        char name[64];
        
        sscanf(line, "%d,%s", &id, name);           // Comma separated Values
        assign_idname(t, id, name);
        
        if (bd_is_empty(bd))
        {
            bd->first = create_node(t);
            ptr = bd->first;
        } else {
            ptr->next = create_node(t);
            ptr = ptr->next;
        }
    }
    
    printf("Success!!\n");
    
    fclose(file);
}


// ***** BD UPDATE FUNCTIONS *****
// --- Clear all teams data ---
void reset_bdteams(BDTeams *bdt)
{
    for (Node *ptr = bdt->first; ptr != NULL; ptr = ptr->next)
    {
        team_reset_stats(ptr->info);
    }
}




// ***** UTENSILS FUNCTIONS *****
// --- is prefix? (case insensitive) ---
int is_prefix_ascii(const char *a, const char *b) {
    if (!a || !b) return 0;

    while (*a && *b) {
        char ca = *a;
        char cb = *b;

        // converts A–Z to a–z (ASCII)
        if (ca >= 'A' && ca <= 'Z') ca += ('a' - 'A');
        if (cb >= 'A' && cb <= 'Z') cb += ('a' - 'A');

        if (ca != cb)
            return 0;

        a++;
        b++;
    }

    // if *a at '\0', returns true, else false
    return (*a == '\0') ? 1 : 0;
}
