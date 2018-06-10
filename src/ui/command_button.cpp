//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

CommandButton::CommandButton(World * world, Panel * parent, int type, int xpos, int ypos, int size) {
    this->world = world;
    this->parent = parent;
    this->panel_type = type;

    this->x = xpos;
    this->y = ypos;
    this->width = size;
    this->height = size;

    this->texture = get_texture();

    if(this->texture != nullptr) {
        this->vao = generateVertices(this->x, this->y, width, height, *(this->texture));
    }

    this->key = get_key();

    this->highlight.setSize(sf::Vector2f(this->width, this->height));
    this->highlight.setPosition(this->x, this->y);

    this->highlight.setFillColor(sf::Color(0, 0, 0, 64));

    this->pressed = false;
}

sf::Texture * CommandButton::get_texture() {
    switch(this->panel_type) {
        case NULL_BUTTON:
            return nullptr;
        case BACK_BUTTON:
            return resources::textures[resources::ui::BACK_COMMAND_TEXTURE];
        case BUILD_COLLECTORS:
            return resources::textures[resources::ui::BUILD_COLLECTORS_TEXTURE];
        case BUILD_FARM:
            return resources::textures[resources::ui::BUILD_FARM_TEXTURE];
        default:
            return resources::textures[resources::ui::MOVE_COMMAND_TEXTURE];
    }
}

int CommandButton::get_key() {
    switch(this->panel_type) {
        case NULL_BUTTON:
            return -1;
        case BACK_BUTTON:
            return KEY_BACK_COMMAND;
        case BUILD_COLLECTORS:
            return KEY_BUILD_COLLECTORS;
        case BUILD_FARM:
            return KEY_BUILD_FARM;
    }
}

void CommandButton::set(int type, int key) {
    this->panel_type = type;

    if(this->panel_type == CommandButton::NULL_BUTTON)
        return;

    this->key = key;

    sf::Texture * tex = get_texture();

    if(this->texture == nullptr && tex != nullptr)
        this->vao = generateVertices(this->x, this->y, this->width, this->height, *(this->texture));

    this->texture = tex;
}

void CommandButton::press() {
    this->pressed = true;
}

void CommandButton::click() {
    this->pressed = false;
    switch(this->panel_type) {
        case BACK_BUTTON:
            switch(this->parent->panel_type) {
                case CommandPanel::BASE_BUILD_COLLECTORS:
                    this->parent->set_panel_type(CommandPanel::BASE);
                    break;
                default:
                    break;
            }
        case BUILD_COLLECTORS:
            this->parent->set_panel_type(CommandPanel::BASE_BUILD_COLLECTORS);
            break;
        case BUILD_FARM: {

            this->world->held_entity = new(rpmalloc(sizeof(Farm))) Farm(this->world, COLLECTOR_FOOD);

            this->parent->set_panel_type(CommandPanel::BASE);
            break;
        }
        default:
            this->parent->set_panel_type(CommandPanel::BASE);
    }
}

void CommandButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(this->texture != nullptr) {
        states.texture = texture;
        target.draw(this->vao, states);
    }

    if(this->pressed) {
        target.draw(highlight);
    }
}

void CommandButton::update() {
    if(this->panel_type != CommandButton::NULL_BUTTON) {
        if(settings::input_mapping[this->key]->pressed) {
            press();
        }

        if(settings::input_mapping[this->key]->clicked) {
            click();
        }
    }
}

void CommandButton::set_panel_type(int new_panel_type) {
    this->panel_type = new_panel_type;

    this->key = get_key();

    sf::Texture * tex = get_texture();

    if(this->texture == nullptr && tex != nullptr)
        this->vao = generateVertices(this->x, this->y, this->width, this->height, *(tex));

    this->texture = tex;

    this->pressed = false;
}