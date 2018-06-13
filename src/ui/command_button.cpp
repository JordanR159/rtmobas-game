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

    this->texture = resources::textures[resources::ui::COMMAND_BUTTONS_TEXTURE];

    this->vao = generateVertices(this->x, this->y, width, height, *(this->texture));

    float texSize = this->texture->getSize().x / WIDTH_OF_BUTTON_TEXTURE;

    float x_tex1 = (this->panel_type % (WIDTH_OF_BUTTON_TEXTURE)) * texSize;
    float x_tex2 = x_tex1 + texSize;

    float y_tex1 = (this->panel_type / (WIDTH_OF_BUTTON_TEXTURE)) * texSize;
    float y_tex2 = y_tex1 + texSize;

    std::cout << x_tex1 << " " << x_tex2 << " " << y_tex1 << " " << y_tex2 << " " << this->panel_type << std::endl;

    this->vao[0].texCoords = sf::Vector2f(x_tex1, y_tex1);
    this->vao[1].texCoords = sf::Vector2f(x_tex1, y_tex2);
    this->vao[2].texCoords = sf::Vector2f(x_tex2, y_tex2);
    this->vao[3].texCoords = sf::Vector2f(x_tex2, y_tex1);

    this->key = get_key();

    this->highlight.setSize(sf::Vector2f(this->width, this->height));
    this->highlight.setPosition(this->x, this->y);

    this->highlight.setFillColor(sf::Color(0, 0, 0, 64));

    this->pressed = false;
}

int CommandButton::get_key() {
    return KEY_BACK_COMMAND + this->panel_type - 1;
}

void CommandButton::press() {
    this->pressed = true;
}

void CommandButton::click() {
    this->pressed = false;
    switch(this->panel_type) {
        case COMMAND_BACK:
            switch(this->parent->panel_type) {
                case BASE_BUILD_COLLECTORS:
                    this->parent->set_panel_type(BASE_PANEL);
                    break;
                default:
                    break;
            }
            break;
        case COMMAND_BUILD_COLLECTORS:
            this->parent->set_panel_type(BASE_BUILD_COLLECTORS);
            break;
        case COMMAND_BUILD_FARM: {

            this->world->held_entity = new(rpmalloc(sizeof(Farm))) Farm(this->world, COLLECTOR_FOOD);

            this->parent->set_panel_type(BASE_PANEL);
            break;
        }
        default:
            this->parent->set_panel_type(BASE_PANEL);
    }
}

void CommandButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = texture;
    target.draw(this->vao, states);

    if(this->pressed) {
        target.draw(highlight);
    }
}

void CommandButton::update() {
    if(this->panel_type != COMMAND_NULL) {
        if(settings::input_mapping[this->key]->pressed) {
            press();
        }

        if(settings::input_mapping[this->key]->clicked) {
            std::cout << "CLICKED" << std::endl;
            click();
        }
    }
}

void CommandButton::set_panel_type(int new_panel_type) {
    this->panel_type = new_panel_type;

    this->key = get_key();

    float texSize = this->texture->getSize().x / WIDTH_OF_BUTTON_TEXTURE;

    float x_tex1 = (this->panel_type % (WIDTH_OF_BUTTON_TEXTURE)) * texSize;
    float x_tex2 = x_tex1 + texSize;

    float y_tex1 = (this->panel_type / (WIDTH_OF_BUTTON_TEXTURE)) * texSize;
    float y_tex2 = y_tex1 + texSize;

    std::cout << x_tex1 << " " << x_tex2 << " " << y_tex1 << " " << y_tex2 << " " << this->panel_type << std::endl;

    this->vao[0].texCoords = sf::Vector2f(x_tex1, y_tex1);
    this->vao[1].texCoords = sf::Vector2f(x_tex1, y_tex2);
    this->vao[2].texCoords = sf::Vector2f(x_tex2, y_tex2);
    this->vao[3].texCoords = sf::Vector2f(x_tex2, y_tex1);

    this->pressed = false;
}