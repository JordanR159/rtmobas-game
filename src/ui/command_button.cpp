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

    this->highlight.setSize(sf::Vector2f(this->width, this->height));
    this->highlight.setPosition(this->width, this->height);

    this->highlight.setFillColor(sf::Color(0, 0, 0, 64));

    this->pressed = false;
}

Texture * CommandButton::get_texture() {
    switch(this->panel_type) {
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

void CommandButton::set(int type, int key) {
    this->panel_type = type;

    if(this->panel_type == CommandButton::NULL_BUTTON)
        return;

    this->key = key;

    Texture * tex = get_texture();

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
                    CommandPanel::BASE;
                default:
                    -1;
            }
        case BUILD_COLLECTORS:
            CommandPanel::BASE_BUILD_COLLECTORS;
        case BUILD_FARM: {
            void * mem = rpmalloc(sizeof(Structure));
            Structure * structure = new(mem) Structure();

            //World::held_entity = structure;
            CommandPanel::BASE;
        }
        default:
            CommandPanel::BASE;
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