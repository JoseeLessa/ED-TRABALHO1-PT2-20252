#include "partida.h"
#include "bdpartidas.h"
#include "bdtimes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ***** STRUCTS DECLARATION *****
// --- MATCHES STRUCTS ---
// TAD BDMatches
struct bdmatches {
	MNode *first;
} ;

// Matches Node
struct match_node {
	Match *info;
	MNode *next;
} ;


// ***** VAR INITIATION FUNCTIONS *****
// --- Creates pointer to BDTeam struct ---
BDMatches *bdmatches_create()
{
	BDMatches *bdm = (BDMatches *)malloc(sizeof(BDMatches));
	bdm->first = NULL;

	return bdm;
}

// --- Create node ---
MNode *create_mnode(Match *m)                      // Returns pointer to a List node with values
{
	MNode *n = (MNode *)malloc(sizeof(MNode));
	n->info = m;
	n->next = NULL;

	return n;
}

// --- Create node 2.0 ---
MNode *create_mnode_with_vals(int id, int id_team1, int id_team2, int goals_team1, int goals_team2)                      // Returns pointer to a List node with values
{
	MNode *n = (MNode *)malloc(sizeof(MNode));
	n->info = create_match(id, id_team1, id_team2, goals_team1, goals_team2);
	n->next = NULL;

	return n;
}

// --- Copy node ---
void append_mnode_copy(BDMatches *bdm, MNode *n)
{
	if (bdm_is_empty(bdm))
	{
		bdm->first = create_mnode(n->info);
	} else {
		MNode *pos = bdm->first;
		while (pos->next != NULL) pos = pos->next;
		pos->next = create_mnode(n->info);
	}
}

// --- Extract Node from bdmatches ---
void explode_mnode_by_id(BDMatches *bdm, int id)
{
	if (bdm_is_empty(bdm)) return;

	MNode *prev = NULL;
	MNode *cur  = bdm->first;

	while (cur != NULL)
	{
		if (match_id(cur->info) == id)
		{
			if (prev == NULL)
			{
				bdm->first = cur->next;  // Removing first element
			}
			else
			{
				prev->next = cur->next;
			}
			delete_match(cur->info);
			free(cur);
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

// ***** VAR manipulation FUNCTIONS *****
// --- free memory in pointer p ---
void delete_all_matches(BDMatches *bdm)
{
	MNode *p = bdm->first;

	while (p != NULL)
	{
		delete_match(p->info);
		MNode *aux = p;
		p = p->next;
		free(aux);
	}
}

// --- update match values ---
void update_match_by_id(BDMatches *bdm, int id, int goals1, int goals2)
{
	MNode *m = bdmatches_search_by_id(bdm, id);
	update_match(m->info, goals1, goals2);
}


// ***** Printing Functions *****
// ---  Print Match ---
void print_match(MNode *ptr, char nome1[], char nome2[])
{
	Match *m = ptr->info;
	printf("| %2d | %15s   %5d X %-5d   %-15s |\n",
	       match_id(m), nome1, match_goals_team1(m), match_goals_team2(m), nome2);
}


// ***** SEARCH FUNCTIONS *****
// ---  Search using ID ---
MNode *bdmatches_search_by_id(BDMatches *bdp, int id)
{
	for (MNode *ptr = bdp->first; ptr != NULL; ptr = ptr->next)
	{
		if (match_id(ptr->info) == id)
		{
			return ptr;
		}
	}
	return NULL;
}

// --- Search for id and return int if exists in bdt ---
int id_in_bdm(BDMatches *bdm, int id)
{
	for (MNode *ptr = bdm->first; ptr!=NULL; ptr = ptr->next)
	{
		if ( match_id(ptr->info) == id) return 1;
	}
	return 0;
}


// ***** VALUE EXTRACTOR FUNCTIONS *****
// --- is BDMatches Empty? ---
int bdm_is_empty(BDMatches *bdm)                   // Check if the 'first' pointer is NULL, indicating an empty list
{
	return bdm->first == NULL;
}

// --- BDMatches->first ---
MNode *first_node(BDMatches *bdm)
{
	return bdm->first;
}

// --- Mnode->next ---
MNode *next_node(MNode *mn)
{
	return mn->next;
}

// --- MNode Match id ---
int node_matchid(MNode *mn)
{
	return match_id(mn->info);
}

// --- change all vals to match values ---
void match_vals(MNode *mn, int *id, int *id1, int *id2, int *goals1, int *goals2)
{
	*id = match_id(mn->info);
	*id1 = match_id_team1(mn->info);
	*id2 = match_id_team2(mn->info);
	*goals1 = match_goals_team1(mn->info);
	*goals2 = match_goals_team2(mn->info);
}

// --- Number of elements em bdm ---
int new_id_bdm(BDMatches *bdm)
{
	if (bdm_is_empty(bdm)) return 0;
	int i = 0;
	MNode *p = bdm->first;
	while (p->next != NULL)
	{
		p = p->next;
		i++;
	}
	return i + 1;
}



// ***** ARCHIVE LOADING FUNCTIONS *****
// ---  Loads from path to *BDPartidas ---
void bdpartidas_load_csv(BDMatches *bdm, const char path[])
{
	FILE *file = fopen(path, "r");                   // Loads file from path

	if (file == NULL)                                // Verify file
	{
		printf("Error opening file\n");
		return;                                      // Return if error
	}

	int line_count = 0;
	char line[200];                                  // sequence of non-blank characters
	MNode *ptr;

	fgets(line, 200, file);                          // Eliminate header

	while (fgets(line, 200, file) != NULL)           // returns line or NULL (if reach the end of file)
	{
		int id, id_team1, id_team2, goals_team1, goals_team2;

		sscanf(line, "%d,%d,%d,%d,%d", &id, &id_team1, &id_team2, &goals_team1, &goals_team2);

		if (bdm_is_empty(bdm))
		{
			bdm->first = create_mnode(create_match(id, id_team1, id_team2, goals_team1, goals_team2));
			ptr = bdm->first;
		} else {
			ptr->next = create_mnode(create_match(id, id_team1, id_team2, goals_team1, goals_team2));
			ptr = ptr->next;
		}
	}

	printf("\nTotal de partidas lidas: %d\n", line_count);

	fclose(file);
}



