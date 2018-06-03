//
// Created by jorda on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

InterfacePanels::InterfacePanels(int width, int height, World * world) {

    this->texture = load(ui::PANEL_TEXTURE);

    load(ui::BACK_COMMAND_TEXTURE);

    load(ui::BUILD_COLLECTORS_TEXTURE);
    load(ui::BUILD_FARM_TEXTURE);

    load(ui::MOVE_COMMAND_TEXTURE);

    this->world = world;

    //texture.loadFromFile("../resources/textures/interface_panels.png");
    interface_width = width;
    interface_height = height;
    entity_panel = EntityPanel(531, 11, 128, EntityPanel::BASE, this->world);
    minimap = MinimapPanel(11, 11, 128, this->world);
    vertices = generateVertices(0, 0, interface_width, interface_height, *this->texture);
}

InterfacePanels::~InterfacePanels() {
    /*flush(ui::PANEL_TEXTURE);

    flush(ui::BACK_COMMAND_TEXTURE);

    flush(ui::BUILD_COLLECTORS_TEXTURE);
    flush(ui::BUILD_FARM_TEXTURE);

    flush(ui::MOVE_COMMAND_TEXTURE);*/
}

void InterfacePanels::update() {
    entity_panel.update();
    minimap.update();
}

void InterfacePanels::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = this->texture;
    target.draw(vertices, states);
    target.draw(minimap);
    target.draw(entity_panel);
}