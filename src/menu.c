#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "bdtimes.h"
#include "bdpartidas.h"

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

// ***** OPTION 1 - FUNCTIONS *****
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
        printf("Nenhum time encontrado para o prefixo: %s.\n", prefix);
        return;
    } else {
        bdteams_print_table(sort_bdteams(founds));
    }
    free_bdteams(founds);
}


// ***** OPTION 2 - FUNCTIONS *****
// --- Consult match by prefix ---
int option_consult_match(BDMatches *bdm, BDTeams *bdt)
{
    clear_screen();
    printf("\n=== Consultar Partida ===\n\n");
    printf("Escolha o modo de consulta:");
    printf("\n1-Por time mandante");
    printf("\n2-Por time visitante");
    printf("\n3-Por time mandante ou visitante");
    printf("\n4-Retornar ao menu principal\n");
    
    int opcao = 0;
    
    do
    {
        printf("\nInsira opção: ");
        scanf("%d", &opcao);
        if (opcao>=1 && opcao<=3)
        {
            char prefix[128];
            printf("\nDigite o nome ou prefixo do time: ");
            scanf("%s", prefix);
            BDTeams *founds = bdteams_search_by_prefix(bdt, prefix);
            
            switch (opcao)
            {
            case 1:
                home_matches(bdt, founds, bdm);
                free_bdteams(founds);
                return 1;
            break;
        
            case 2:
                away_matches(bdt, founds, bdm);
                free_bdteams(founds);
                return 1;
            break;
        
            case 3:
                matches(bdt, founds, bdm);
                free_bdteams(founds);
                return 1;
            break;
            }
        } else if (opcao != 4) {
            printf("\nERRO, Insira opção valida: ");
            scanf("%d", &opcao);
        }
    } while (opcao != 4);
    
    return 0;
}

// --- home matches with prefix ---
void home_matches(BDTeams *bdt, BDTeams *filtro, BDMatches *bdm)
{
    if (bdm_is_empty(bdm))
    {
        printf("Nenhuma partida registrada...");
        return;
    }
    
    int id, id_team1, id_team2, goals1, goals2;
    
    printf("\n| ID |      Time1      | Gols1 | Gols2 |      Time2      |\n");
    printf("|----|---------------------------------------------------|\n");
    
    for (MNode *m = first_node(bdm); m != NULL; m = next_node(m))
    {
        match_vals(m, &id, &id_team1, &id_team2, &goals1, &goals2);
        if (id_in_bdt(filtro, id_team1))
        {
            print_match(m, team_name_by_id(bdt, id_team1), team_name_by_id(bdt, id_team2));
        }
    }
}

// --- away matches with prefix ---
void away_matches(BDTeams *bdt, BDTeams *filtro, BDMatches *bdm)
{
    if (bdm_is_empty(bdm))
    {
        printf("Nenhuma partida registrada...");
        return;
    }
    
    int id, id_team1, id_team2, goals1, goals2;
    
    printf("\n| ID |      Time1      | Gols1 | Gols2 |      Time2      |\n");
    printf("|----|---------------------------------------------------|\n");
    
    for (MNode *m = first_node(bdm); m != NULL; m = next_node(m))
    {
        match_vals(m, &id, &id_team1, &id_team2, &goals1, &goals2);
        if (id_in_bdt(filtro, id_team2))
        {
            print_match(m, team_name_by_id(bdt, id_team1), team_name_by_id(bdt, id_team2));
        }
    }
}

// --- matches with prefix ---
void matches(BDTeams *bdt, BDTeams *filtro, BDMatches *bdm)
{
    if (bdm_is_empty(bdm))
    {
        printf("Nenhuma partida registrada...");
        return;
    }
    
    int id, id_team1, id_team2, goals1, goals2;
    
    printf("\n| ID |      Time1      | Gols1 | Gols2 |      Time2      |\n");
    printf("|----|---------------------------------------------------|\n");
    
    for (MNode *m = first_node(bdm); m != NULL; m = next_node(m))
    {
        match_vals(m, &id, &id_team1, &id_team2, &goals1, &goals2);
        if (id_in_bdt(filtro, id_team2) || id_in_bdt(filtro, id_team1))
        {
            print_match(m, team_name_by_id(bdt, id_team1), team_name_by_id(bdt, id_team2));
        }
    }
}


// ***** OPTION 3 - FUNCTIONS *****
// --- Update match ---
void option_update_match(BDMatches *bdm, BDTeams *bdt)
{
    if (!option_consult_match(bdm, bdt)) return;
    
    int busca, igoals1, igoals2;
    char goals1[10];
    char goals2[10];

    printf("\n=== Atualizar partida ===\n");

    printf("Digite o ID da partida a ser atualizada: ");
    scanf("%d", &busca);

    printf("Digite os novos gols do time 1 ( '-' para manter ): ");
    scanf("%s", goals1);

    printf("Digite os novos gols do time 2 ( '-' para manter ): ");
    scanf("%s", goals2);
    
    if (id_in_bdm(bdm, busca))
    {
        MNode *match = bdmatches_search_by_id(bdm, busca);
        int id, id_t1, id_t2, g1, g2;
        match_vals(match, &id, &id_t1, &id_t2, &g1, &g2);
        
        // Converts str numbers inputed into int
        if ( goals1[0] == '-') 
        {
            igoals1 = g1;
        } else {
            if (sscanf(goals1, "%d", &igoals1) != 1) 
            {
                printf("\nERROR ENTRADA GOALS 1 INVALIDA");
                return;
            }
        }
        
        if ( goals2[0] == '-')
        {
            igoals2 = g2;
        } else {
            if (sscanf(goals2, "%d", &igoals2) != 1) 
            {
                printf("\nERROR ENTRADA GOALS 2 INVALIDA");
                return;
            }
        }
        
        printf("\n| ID |      Time1      | Gols1 | Gols2 |      Time2      |\n");
        printf("|----|---------------------------------------------------|\n");
        printf("| %2d | %15s   %5d X %-5d   %-15s |\n",
               id, team_name_by_id(bdt, id_t1), igoals1, igoals2, team_name_by_id(bdt, id_t2));
        
        int i;
        printf("\nDeseja confirmar a alteracao da partida acima? (1 - Sim/0 - Nao)?\n");
        scanf("%d", &i);
        
        if (i == 1) 
        {
            Node *t1 = bdteams_search_by_id(bdt, id_t1);
            Node *t2 = bdteams_search_by_id(bdt, id_t2);
            
            node_sub_match(t1, g1, g2);
            node_sub_match(t2, g2, g1);
            
            update_match_by_id(bdm, busca, igoals1, igoals2);
            
            node_add_match(t1, igoals1, igoals2);
            node_add_match(t2, igoals2, igoals1);
            
            printf("Partida atualizada com sucessor!");
        } else {
            printf("\n--- ATUALIZACAO DE PARTIDA CANCELADA ---\n");
        }
        
    } else {
        printf("ERRO - Partida não encontrada.");
        return;
    }
}


// ***** OPTION 4 - FUNCTIONS *****
// --- Remove match ---
void option_remove_match(BDMatches *bdm, BDTeams *bdt)
{
    if (!option_consult_match(bdm, bdt)) return;
    
    int busca;
    
    printf("\nDigite o ID do registro a ser removido:");
    scanf("%d", &busca);
    
    if (id_in_bdm(bdm, busca))
    {
        printf("\n| ID |      Time1      | Gols1 | Gols2 |      Time2      |\n");
        printf("|----|---------------------------------------------------|\n");
        
        MNode *match = bdmatches_search_by_id(bdm, busca);
        int id, t1, t2, g1, g2;
        match_vals(match, &id, &t1, &t2, &g1, &g2);
        
        print_match(match, team_name_by_id(bdt, t1), team_name_by_id(bdt, t2));
        int i;
        
        printf("\nTem certeza que deseja excluir a partida acima? (1 - Sim/0 - Nao)?\n");
        scanf("%d", &i);
        
        if (i == 1) 
        {
            node_sub_match(bdteams_search_by_id(bdt, t1), g1, g2);
            node_sub_match(bdteams_search_by_id(bdt, t2), g2, g1);
            explode_mnode_by_id(bdm, busca);
            if (!id_in_bdm(bdm, busca))
            {
                printf("\nRegistro removido com sucesso.");
            } else {
                printf("\nErro ao excluir registro.");
            }
        } else {
            printf("\n--- REMOCAO DE PARTIDA CANCELADA ---\n");
        }
    } else {
        printf("ERRO - Partida não encontrada.");
        return;
    }
}


// ***** OPTION 5 - FUNCTIONS *****
// --- Insert new match ---
void option_insert_match(BDMatches *bdm, BDTeams *bdt)
{
    clear_screen();
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
    
    int id = new_id_bdm(bdm);
    
    if (!id_in_bdt(bdt, id_team1) || !id_in_bdt(bdt, id_team2) || id_team1 == id_team2 || goals_team1<0 || goals_team2<0)
    {
        printf("\nERROR ABORTANDO...\n");
        return;
    }
    MNode *new = create_mnode_with_vals(id, id_team1, id_team2, goals_team1, goals_team2);
    
    print_match(create_mnode_with_vals(id, id_team1, id_team2, goals_team1, goals_team2), team_name_by_id(bdt, id_team1), team_name_by_id(bdt, id_team2));
    printf("\nConfirmar nova partida? (1 - Sim/0 - Nao)?\n");
    int i;
    scanf("%d", &i);
    if (i == 1)
    {
        append_mnode_copy(bdm, new);
        printf("\nRegistro criado com sucesso.\n");
        Node *t1 = bdteams_search_by_id(bdt, id_team1);
        Node *t2 = bdteams_search_by_id(bdt, id_team2);
        
        node_add_match(t1, goals_team1, goals_team2);
        node_add_match(t2, goals_team2, goals_team1);
    } else {
        printf("\n--- NOVA PARTIDA CANCELADA ---\n");
    }
}


// ***** OPTION 6 - FUNCTIONS *****
// --- Print table, sorted by points, victories, goals balance,  ---
void option_print_classification(BDTeams *bdt)
{
    bdteams_print_table(sort_bdteams(bdt));
}


// ***** UPDATE DBTEAMS *****
// --- Updates every team info in BDteams using all matches ---
void bdpartidas_increase_in_team(BDMatches *bdm, BDTeams *bdt) 
{  
    reset_bdteams(bdt);
    
    int id, id1, id2, goals1, goals2;
    for (MNode *mn = first_node(bdm); mn != NULL; mn = next_node(mn)) 
    {
        
        match_vals(mn, &id, &id1, &id2, &goals1, &goals2);
        
        Node *t1 = bdteams_search_by_id(bdt, id1);
        Node *t2 = bdteams_search_by_id(bdt, id2);
        
        node_add_match(t1, goals1, goals2);
        node_add_match(t2, goals2, goals1);
    }
}
