//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

CommandPanel::CommandPanel(World * world, Panel * parent, int type, int xpos, int ypos, int size) {

    sf::Texture * texture = new(rpmalloc(sizeof(sf::Texture))) sf::Texture();

    texture->loadFromFile("../resources/textures/entity_panel.png");

    this->create_panel(world, parent, type, xpos, ypos, size * 2, size, texture);

    this->current_state = this->panel_type;

    for(int x = this->x + this->width / 16; x < this->x + this->width * 14 / 16; x += this->width * 3/16) {
        for (int y = this->y + this->height / 16; y < this->y + this->height * 14 / 16; y += this->height * 5 / 16) {
            this->children.emplace_back(new(rpmalloc(sizeof(CommandButton))) CommandButton(world, this, COMMAND_NULL, x, y, size / 4));
        }
    }
    set_options();
}

void CommandPanel::clear_options() {
    for(auto &child : this->children) {
        child->set_panel_type(COMMAND_NULL);
    }
}

void CommandPanel::set_options() {
    clear_options();

    switch(this->panel_type) {
        case BASE_PANEL:
            this->children.at(0)->set_panel_type(COMMAND_BUILD_COLLECTORS);
            break;
        case BASE_BUILD_COLLECTORS:
            this->children.at(0)->set_panel_type(COMMAND_BACK);
            this->children.at(1)->set_panel_type(COMMAND_BUILD_FARM);
            this->children.at(4)->set_panel_type(COMMAND_BUILD_GOLD_MINE);
            this->children.at(7)->set_panel_type(COMMAND_BUILD_METAL_MINE);
            this->children.at(10)->set_panel_type(COMMAND_BUILD_CRYSTAL_HARVESTER);
        default:
            break;
    }
}

void CommandPanel::update() {
    for(auto &child : this->children) {
        child->update();
    }

    if(this->current_state != this->panel_type) {
        this->panel_type = this->current_state;
        set_options();
    }
}

void CommandPanel::set_panel_type(int new_panel_type) {
    this->current_state = new_panel_type;
}