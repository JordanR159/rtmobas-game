//
// Created by jorda on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

UserInterface::UserInterface(World * world, int width, int height) {

    resources::load(resources::ui::ENTITY_PANEL_TEXTURE);
    resources::load(resources::ui::MINIMAP_PANEL_TEXTURE);

    resources::load(resources::ui::BACK_COMMAND_TEXTURE);

    resources::load(resources::ui::BUILD_COLLECTORS_TEXTURE);
    resources::load(resources::ui::BUILD_FARM_TEXTURE);

    resources::load(resources::ui::MOVE_COMMAND_TEXTURE);

    resources::load(resources::ui::SELECT_BOX_TEXTURE);
    resources::load(resources::ui::MINIMAP_RETICLE_TEXTURE);

    this->create_panel(world, nullptr, 0, 0, 0, width, height, resources::load(resources::ui::INTERFACE_TEXTURE));

    this->children.emplace_back(new(rpmalloc(sizeof(CommandPanel))) CommandPanel(this->world, this, CommandPanel::BASE, 531, 11, 128));

    this->children.emplace_back(new(rpmalloc(sizeof(MinimapPanel))) MinimapPanel(this->world, this, 11, 11, 128));
}