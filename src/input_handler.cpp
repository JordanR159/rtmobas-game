//
// Created by jorda on 6/11/2018.
//

#include "helper.hpp"

using namespace settings;

void handleControlGroups() {
    int group_num = 0;

    if(input_mapping[KEY_CONTROL_ONE]->just_pressed) group_num = 1;
    else if(input_mapping[KEY_CONTROL_TWO]->just_pressed) group_num = 2;
    else if(input_mapping[KEY_CONTROL_THREE]->just_pressed) group_num = 3;
    else if(input_mapping[KEY_CONTROL_FOUR]->just_pressed) group_num = 4;
    else if(input_mapping[KEY_CONTROL_FIVE]->just_pressed) group_num = 5;
    else if(input_mapping[KEY_CONTROL_SIX]->just_pressed) group_num = 6;
    else if(input_mapping[KEY_CONTROL_SEVEN]->just_pressed) group_num = 7;
    else if(input_mapping[KEY_CONTROL_EIGHT]->just_pressed) group_num = 8;
    else if(input_mapping[KEY_CONTROL_NINE]->just_pressed) group_num = 9;
    else if(input_mapping[KEY_CONTROL_ZERO]->just_pressed) group_num = 10;

    if(group_num != 0) {
        /** Delete old control group and create a new one */
        if(input_mapping[KEY_CREATE_CONTROL]->pressed) {
            if(!selector->selected_entities.empty()) {
                selector->control_groups_entities[group_num - 1].clear();
                for (auto &entity : selector->selected_entities) {
                    selector->control_groups_entities[group_num - 1].emplace_back(entity);
                }
            }
            if(!selector->selected_tile_entities.empty()) {
                selector->control_groups_tile_entities[group_num - 1].clear();
                for (auto &entity : selector->selected_tile_entities) {
                    selector->control_groups_tile_entities[group_num - 1].emplace_back(entity);
                }
            }
        }
        /** Add to control group, create if necessary */
        else if(input_mapping[KEY_ADD_CONTROL]->pressed) {
            if(!selector->selected_entities.empty()) {
                for (auto &entity : selector->selected_entities) {
                    bool contains = false;
                    for (auto &element : selector->control_groups_entities[group_num - 1]) {
                        if (entity == element) {
                            contains = true;
                            break;
                        }
                    }
                    if (!contains)
                        selector->control_groups_entities[group_num - 1].emplace_back(entity);
                }
            }
            if(!selector->selected_tile_entities.empty()) {
                for (auto &entity : selector->selected_tile_entities) {
                    bool contains = false;
                    for (auto &element : selector->control_groups_tile_entities[group_num - 1]) {
                        if (entity == element) {
                            contains = true;
                            break;
                        }
                    }
                    if (!contains)
                        selector->control_groups_tile_entities[group_num - 1].emplace_back(entity);
                }
            }
        }
        /** Remove from control group */
        else if(input_mapping[KEY_REMOVE_CONTROL]->pressed) {
            if(!selector->selected_entities.empty()) {
                for (auto &entity : selector->selected_entities) {
                    std::vector<Entity *> new_control_group;
                    for (auto &element : selector->control_groups_entities[group_num - 1]) {
                        if (entity != element) {
                            new_control_group.emplace_back(element);
                        }
                    }
                    selector->control_groups_entities[group_num - 1] = new_control_group;
                }
            }
            if(!selector->selected_tile_entities.empty()) {
                for (auto &entity : selector->selected_tile_entities) {
                    std::vector<TileEntity *> new_control_group;
                    for (auto &element : selector->control_groups_tile_entities[group_num - 1]) {
                        if (entity != element) {
                            new_control_group.emplace_back(element);
                        }
                    }
                    selector->control_groups_tile_entities[group_num - 1] = new_control_group;
                }
            }
        }
        /** Select control group */
        else {
            for (auto &entity : selector->selected_entities) {
                entity->info.selected = false;
            }
            selector->selected_entities.clear();
            for (auto &entity : selector->control_groups_entities[group_num - 1]) {
                entity->info.selected = true;
                selector->selected_entities.emplace_back(entity);
            }
            for (auto &entity : selector->selected_tile_entities) {
                entity->info.selected = false;
            }
            selector->selected_tile_entities.clear();
            for (auto &entity : selector->control_groups_tile_entities[group_num - 1]) {
                entity->info.selected = true;
                selector->selected_tile_entities.emplace_back(entity);
            }
        }
    }
}
