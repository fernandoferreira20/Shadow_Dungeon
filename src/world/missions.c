#include "missions.h" // Include our own header
#include <stddef.h> // for NULL

// marks a specific mission as complete in the hero's status.
// hero A pointer to the hero whose mission will be marked.
// mission_to_complete The ID of the mission to mark as complete.
void mark_mission_complete(Hero* hero, MissionID mission_to_complete){
    if(hero == NULL){
        return; // safety check
    }
    
    switch(mission_to_complete){
        case ROTTING_SWAMP:
            hero->missions.rotting_swamp = 1;
        break;
        case HAUNTED_MANSION:
            hero->missions.haunted_mansion = 1;
        break;
        case CRYSTAL_CAVE:
            hero->missions.crystal_cave = 1;
        break;
    }
}

// hecks if all 3 preliminary missions are complete.
// hero A pointer to the hero to check.
// 1 (true) if all 3 missions are complete, 0 (false) otherwise.
int are_all_missions_complete(const Hero* hero){
    if(hero == NULL){
        return 0; // safety check
    }
    
    // checks if all three mission flags are 1
    if(hero->missions.rotting_swamp && hero->missions.haunted_mansion && hero->missions.crystal_cave){
        return 1; // All complete
    }else{
        return 0; // Not all completed
    }


}