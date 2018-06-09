//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

CommandPanel::CommandPanel(World * world, Panel * parent, int type, int xpos, int ypos, int size) {

    Texture * texture = new(rpmalloc(sizeof(Texture))) Texture();

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
        CommandButton * button = static_cast<CommandButton *>(child);
        if(button->panel_type != CommandButton::NULL_BUTTON) {
            button->set(CommandButton::NULL_BUTTON, 0);
            button->pressed = false;
        }
    }
}

void CommandPanel::set_options() {
    clear_options();

    switch(this->panel_type) {
        case BASE:
            static_cast<CommandButton *>(this->children.at(0))->set(CommandButton::BUILD_COLLECTORS, settings::Key::HOTKEY_BUILD_COLLECTORS);
            break;
        case BASE_BUILD_COLLECTORS:
            static_cast<CommandButton *>(this->children.at(0))->set(CommandButton::BACK_BUTTON, settings::Key::HOTKEY_BACK_COMMAND);
            static_cast<CommandButton *>(this->children.at(1))->set(CommandButton::BUILD_FARM, settings::Key::HOTKEY_BUILD_FARM);
        default:
            break;
    }
}