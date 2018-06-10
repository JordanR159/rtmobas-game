//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

CommandPanel::CommandPanel(World * world, Panel * parent, int type, int xpos, int ypos, int size) {

    sf::Texture * texture = new(rpmalloc(sizeof(sf::Texture))) sf::Texture();

    texture->loadFromFile("../resources/textures/entity_panel.png");

    this->create_panel(world, parent, type, xpos, ypos, size * 2, size, texture);

    for(int x = this->x + this->width / 16; x < this->x + this->width * 14 / 16; x += this->width * 3/16) {
        for (int y = this->y + this->height / 16; y < this->y + this->height * 14 / 16; y += this->height * 5 / 16) {
            this->children.emplace_back(new(rpmalloc(sizeof(CommandButton))) CommandButton(world, this, CommandButton::NULL_BUTTON, x, y, size / 4));
        }
    }

    set_options();
}

void CommandPanel::clear_options() {
    for(auto &child : this->children) {
        child->set_panel_type(CommandButton::NULL_BUTTON);
    }
}

void CommandPanel::set_options() {
    clear_options();

    switch(this->panel_type) {
        case BASE:
            this->children.at(0)->set_panel_type(CommandButton::BUILD_COLLECTORS);
            break;
        case BASE_BUILD_COLLECTORS:
            this->children[0]->set_panel_type(CommandButton::BACK_BUTTON);
            this->children[1]->set_panel_type(CommandButton::BUILD_FARM);
        default:
            break;
    }
}

void CommandPanel::set_panel_type(int new_panel_type) {
    this->panel_type = new_panel_type;

    set_options();
}