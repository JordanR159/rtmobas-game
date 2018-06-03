//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

CommandButton::CommandButton(int xposition, int yposition, int size, int type) {
    this->type = type;

    button_size = size;
    this->xposition = xposition;
    this->yposition = yposition;

    this->texture = get_texture();

    if(this->texture != nullptr) {
        vertices = generateVertices(this->xposition, this->yposition, button_size, button_size, *(this->texture));
    }

    this->highlight.setSize(sf::Vector2f(this->button_size, this->button_size));
    this->highlight.setPosition(this->xposition, this->yposition);

    this->highlight.setFillColor(sf::Color(0, 0, 0, 64));

    this->pressed = false;
}

Texture * CommandButton::get_texture() {
    switch(this->type) {
        case BACK_BUTTON:
            return textures[ui::BACK_COMMAND_TEXTURE];
        case BUILD_COLLECTORS:
            return textures[ui::BUILD_COLLECTORS_TEXTURE];
        case BUILD_FARM:
            return textures[ui::BUILD_FARM_TEXTURE];
        default:
            return textures[ui::MOVE_COMMAND_TEXTURE];
    }
}

void CommandButton::set(int type, int key) {
    this->type = type;

    if(this->type == CommandButton::NULL_BUTTON)
        return;

    this->key = key;

    Texture * tex = get_texture();

    if(this->texture == nullptr && tex != nullptr)
        vertices = generateVertices(this->xposition, this->yposition, this->button_size, this->button_size, *(this->texture));

    this->texture = tex;
}

void CommandButton::press() {
    this->pressed = true;
}

int CommandButton::click(EntityPanel * panel) {
    this->pressed = false;
    switch(this->type) {
        case BACK_BUTTON:
            switch(panel->type) {
                case EntityPanel::BASE_BUILD_COLLECTORS:
                    return EntityPanel::BASE;
                default:
                    return -1;
            }
        case BUILD_COLLECTORS:
            return EntityPanel::BASE_BUILD_COLLECTORS;
        case BUILD_FARM: {
            void * mem = rpmalloc(sizeof(Structure));
            Structure * structure = new(mem) Structure();

            //World::held_entity = structure;
            return EntityPanel::BASE;
        }
        default:
            return EntityPanel::BASE;
    }
}

void CommandButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = texture;
    target.draw(vertices, states);

    if(this->pressed) {
        target.draw(highlight);
    }
}