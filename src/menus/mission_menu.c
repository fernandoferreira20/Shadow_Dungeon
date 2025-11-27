#include "mission_menu.h"
#include "../combat/combat.h"
#include "../world/dungeon.h"
#include "../items/shop.h"
#include "../entities/player.h"
#include "../utils/input.h"
#include <stdio.h>

void display_mission_menu(Player *player, Dungeon *dungeon){
    int choice;

    do{
        printf("\n=== MISSION MENU ===\n");
        printf("Objectives: ");
        display_mission_goals(dungeon->mission_type);
        printf("Mission status: ");
        display_mission_status(dungeon,  player);
        printf("\n");

        printf("1. Explore Dungeon Room\n");
        printf("2. Shop\n");
        printf("3. Inventory\n");
        printf("4. Return to Village (Pay 50 Coins)\n");

        choice = get_valid_input(1, 4);

        switch(choice){
            case 1: 
                explore_dungeon_room(player, dungeon);
                break;
            case 2:
                open_shop(player);
                break;
            case 3:
                display_inventory(player);
                break;
            case 4:
                if(return_to_village(player, dungeon)){
                    return;
                }
                break;
        }
    } while (choice != 4 && player->life_points > 0);
}

void explore_dungeon_room(Player *player, Dungeon *dungeon){
    Room *current_room = get_current_room(dungeon);

    if(!current_room){
        printf("No more rooms to explore!\n");
        return;
    }

    printf("\nEntering room %d...\n", dungeon->current_room + 1);

    switch(current_room->type){
        case ROOM_EMPTY:
            printf("The room is empty. Nothing happens.\n");
            break;
        case ROOM_ENEMY:
            handle_enemy_room(player, (Enemy*)current_room->room_data);
            break;
        case ROOM_TRAP:
            handle_trap_room(player, (Trap*)current_room->room_data);
            break;
    }

    current_room->completed = true;
    move_to_next_room(dungeon);
}

bool return_to_village(Player *player, Dungeon *dungeon){
    if(check_mission_complete(dungeon, player)){
        printf("Mission completed! Return to village.\n");
        return true;
    } else if(player->coins >= 50){
        printf("Pay 50 coins to return to the village? [y/n]: ");
        if(get_yes_no_input()){
            player->coins -= 50;
            return true;
        }
    } else {
        printf("Mission not complete and not enough coins (need 50)!\n");
    }
    return false;
}