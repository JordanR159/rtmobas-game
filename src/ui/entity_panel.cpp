//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

EntityPanel::EntityPanel(int xposition, int yposition, int size, int type) {
    this->type = type;
    this->xposition = xposition;
    this->yposition = yposition;
    this->panel_size_x = 2 * size;
    this->panel_size_y = size;

    for(int x = xposition + panel_size_x / 16; x < xposition + panel_size_x * 14 / 16; x += panel_size_x * 3/16) {
        for (int y = yposition + panel_size_y / 16; y < yposition + panel_size_y * 14 / 16; y += panel_size_y * 5 / 16) {
            commands.emplace_back(CommandButton(x, y, size / 4, CommandButton::NULL_BUTTON));
        }
    }

    set_options();

    texture.loadFromFile("../resources/textures/entity_panel.png");
    vertices = generateVertices(this->xposition, this->yposition, panel_size_x, panel_size_y, texture);
}

void EntityPanel::clear_options() {
    for(auto &button : commands) {
        if(button.type != CommandButton::NULL_BUTTON) {
            button.set(CommandButton::NULL_BUTTON, 0);
            button.pressed = false;
        }
    }
}

void EntityPanel::set_options() {
    clear_options();

    switch(this->type) {
        case BASE:
            commands.at(0).set(CommandButton::BUILD_COLLECTORS, settings::Key::HOTKEY_BUILD_COLLECTORS);
            break;
        case BASE_BUILD_COLLECTORS:
            commands.at(0).set(CommandButton::BACK_BUTTON, settings::Key::HOTKEY_BACK_COMMAND);
            commands.at(1).set(CommandButton::BUILD_FARM, settings::Key::HOTKEY_BUILD_FARM);
        default:
            break;
    }
}

void EntityPanel::update() {
    for (auto &button : commands) {
        if(button.type != CommandButton::NULL_BUTTON && settings::input_mapping[button.key]->pressed) {
            button.press();
        }

        if(button.type != CommandButton::NULL_BUTTON && settings::input_mapping[button.key]->clicked) {

            this->type = button.click(this);
            set_options();
        }
    }
}

void EntityPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
    for(CommandButton c : commands) {
        if(c.type != CommandButton::NULL_BUTTON)
            target.draw(c);
    }
}