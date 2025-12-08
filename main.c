
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
    
    bdpartidas_increase_in_team(bdm, bdt);
    
    char opcao;
    do {
        
        clear_screen();
        show_menu();
        scanf(" %c", &opcao);
        
        switch (opcao) 
        {
            case '1': option_consult_team(bdt); break;
            case '2': int a = option_consult_match(bdm, bdt); break;
            case '3': option_update_match(bdm, bdt); break;
            case '4': option_remove_match(bdm, bdt); break;
            case '5': option_insert_match(bdm, bdt); break;
            case '6': option_print_classification(bdt); break;
            default: printf("Opção inválida, tente novamente.\n"); break;
        }
        
        pause_screen();
    } while (opcao != 'Q');

    return 0;
}
