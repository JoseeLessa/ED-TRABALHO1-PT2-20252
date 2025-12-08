
#include <stdio.h>
#include <stdlib.h>

#include "bdtimes.h"
#include "bdpartidas.h"
#include "menu.h"

int main() {
    BDTeams *bdt = bdteams_create();
    bdteams_load_csv(bdt, "entrada.txt");
    BDMatches *bdm = bdmatches_create();
    bdpartidas_load_csv(bdm, "partidas.txt");
    
    
    char opcao;
    do {
        
        clear_screen();
        show_menu();
        scanf(" %c", &opcao);
        
        bdpartidas_increase_in_team(bdm, bdt);
        
        switch (opcao) 
        {
            case '1': option_consult_team(bdt); break;
        //    case '2': opcao_consultar_partidas(bdp, bdt); break;
        //    case '3': opcao_atualizar_partida(bdp, bdt); break;
        //    case '4': opcao_remover_partida(bdp, bdt); break;
            case '5': option_insert_match(bdm, bdt); break;
            case '6': option_print_classification(bdt); break;
        }
        
        pause_screen();
    } while (opcao != 'Q');

    return 0;
}
