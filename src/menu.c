#include <stdlib.h>
#include <stdio.h>
#include "bdtimes.h"
#include "bdpartidas.h"

// ***** ONLY OUTPUT FUNCTIONS *****
// --- Show menu and options ---
void show_menu(){
    printf("\n===================== ======================\n");
    printf("   Sistema de Gerenciamento de Partidas\n");
    printf("======================= ====================\n");
    printf("1 - Consultar time\n");
    printf("2 - Consultar partidas\n");
    printf("3 - Atualizar partida\n");
    printf("4 - Remover partida\n");
    printf("5 - Inserir partida\n");
    printf("6 - Imprimir tabela de classificação\n"); 
    printf("Q - Sair\n");
    printf("\nOpção: ");
}


// ***** USER OPTIONS FUNCTIONS *****
// --- Consult team by prefix (case insensitive) ---
void option_consult_team(BDTeams *bdt)
{
    char prefix[128];
    printf("\nDigite o nome ou prefixo do time: ");
    scanf("%s", prefix);
    
    if (prefix[0]=='\0'){
        printf("Prefixo Vazio.\n");
        return;
    }
    
    BDTeams *founds = bdteams_search_by_prefix(bdt, prefix);
    
    if (bd_is_empty(founds))
    {
        printf("Nenhum time encontrado para o prefixo: %s.\n");
        return;
    } else {
        bdteams_print_table(sort_bdteams(founds));
    }
    free_bdteams(founds);
}


// --- Consult match by prefix (case insensitive) ---
/*
void option_consult_match(BDPartidas *bdp, BDTeams *bdt)
{
    printf("Escolha o modo de consulta:");
    printf("\n1-Por time mandante");
    printf("\n2-Por time visitante");
    printf("\n3-Por time mandante ou visitante");
    printf("\n4-Retornar ao menu principal");
    
    char opcao;
    while (opcao != '4')
    {
        printf("\nInsira opção: ");
        scanf("%c", &opcao);
        
        switch (opcao)
        {
            case '1':
            
                break;
            
            case '2': break;
            
            case '3': break;
            
            default: printf("Opcao invalida."); break;
        }
    }
}
*/


// --- Insert new match ---
void option_insert_match(BDMatches *bdm, BDTeams *bdt)
{
    int id_team1, id_team2;
    int goals_team1, goals_team2;

    printf("\n=== Inserir nova partida ===\n");
    
    printf("\nDigite o ID do time 1: ");
    scanf("%d", &id_team1);

    printf("\nDigite o ID do time 2: ");
    scanf("%d", &id_team2);

    printf("\nGols do time %d: ", id_team1);
    scanf("%d", &goals_team1);

    printf("\nGols do time %d: ", id_team2);
    scanf("%d", &goals_team2);
    
    int id = len_bdm(bdm);
    
    if (!id_in_bdt(bdt, id_team1) || !id_in_bdt(bdt, id_team2))
    {
        printf("\nErro, time não achado.");
        return;
    }

    append_mnode_copy(bdm, create_mnode_with_vals(id, id_team1, id_team2, goals_team1, goals_team2));

    printf("\nRegistro criado com sucesso.\n");
}

/*
// --- Update match ---
void option_update_match(BDPartidas *bdp, BDTeams *bdt)
{
    int id, goals_team1, goals_team2;

    printf("\n=== Atualizar partida ===\n");

    printf("Digite o ID da partida: ");
    scanf("%d", &id);

    printf("Digite os novos gols do time 1: ");
    scanf("%d", &goals_team1);

    printf("Digite os novos gols do time 2: ");
    scanf("%d", &goals_team2);

    // chamada aqui
   
    printf("Atualização solicitada.\n");
}


// --- Remove match ---
void option_remove_match(BDPartidas *bdp, BDTeams *bdt);
*/
// --- Print table, sorted by points, victories, goals balance,  ---
void option_print_classification(BDTeams *bdt)
{
    BDTeams *saida = sort_bdteams(bdt);
    bdteams_print_table(saida);
    
    free_bdteams(saida);
}




// --- BDTeams by prefix ---
BDTeams *bdteams_by_prefix(BDTeams *bdt)
{
    char prefix[128];
    printf("\nDigite o nome ou prefixo do time: ");
    scanf("%s", prefix);
    
    if (prefix[0]=='\0'){
        printf("Prefixo Vazio.\n");
        return NULL;
    }
    
    BDTeams *founds = bdteams_search_by_prefix(bdt, prefix);
    
    return founds;
}

//
// --- Updates every team info in BDteams using all matches ---
void bdpartidas_increase_in_team(BDMatches *bdm, BDTeams *bdt) 
{  
    reset_bdteams(bdt);
    
    int id1, id2, goals1, goals2;
    for (MNode *mn = first_node(bdm); mn != NULL; mn = next_node(mn)) 
    {
        
        match_vals(mn, &id1, &id2, &goals1, &goals2);
        
        Node *t1 = bdteams_search_by_id(bdt, id1);
        Node *t2 = bdteams_search_by_id(bdt, id2);
        
        node_add_match(t1, goals1, goals2);
        node_add_match(t2, goals2, goals1);
    }
}


// ***** SCREEN FUNCTIONS *****
// --- Pause screen ---
void pause_screen() 
{
#ifdef _WIN32
    system("pause");
#else
    printf("\nPressione ENTER para continuar...");
    getchar();                          // reads \n
    getchar();                          // Waits enter
#endif
}

// --- Clear screen ---
void clear_screen() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

