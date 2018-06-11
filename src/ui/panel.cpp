//
// Created by Killian Le Clainche on 6/8/2018.
//

#include "helper.hpp"

Panel::~Panel() {
    for(auto &child : this->children) {
        rpfree(child);
        child->~Panel();
    }
}

void Panel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = this->texture;
    target.draw(this->vao, states);

    for(auto &child : this->children) {
        if(child->panel_type != MINIMAP_PANEL)
            target.draw(*child);
    }
}

void Panel::create_panel(World * world, Panel * panel, int type, int x, int y, int w, int h, sf::Texture * texture) {
    this->world = world;
    this->parent = panel;

    this->panel_type = type;

    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;

    this->texture = texture;

    this->vao = generateVertices(this->x, this->y, this->width, this->height, *(this->texture));

}

void Panel::update() {
    for(auto &child : this->children) {
        child->update();
    }
}

void Panel::set_panel_type(int new_panel_type) {
    this->panel_type = new_panel_type;
}