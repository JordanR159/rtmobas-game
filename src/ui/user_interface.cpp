//
// Created by jorda on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

UserInterface::UserInterface(World * world, int width, int height) {

    resources::load(resources::ui::ENTITY_PANEL_TEXTURE);
    resources::load(resources::ui::MINIMAP_PANEL_TEXTURE);

    resources::load(resources::ui::COMMAND_BUTTONS_TEXTURE);

    resources::load(resources::ui::SELECT_BOX_TEXTURE);
    resources::load(resources::ui::MINIMAP_RETICLE_TEXTURE);

    this->create_panel(world, nullptr, 0, 0, 0, width, height, resources::load(resources::ui::INTERFACE_TEXTURE));

    this->children.emplace_back(new(rpmalloc(sizeof(CommandPanel))) CommandPanel(this->world, this, BASE_PANEL, 531, 11, 128));

    this->children.emplace_back(new(rpmalloc(sizeof(MinimapPanel))) MinimapPanel(this->world, this, 0, 0, 150));
}

Panel * UserInterface::getPanel(int panel_type) {
    for(auto &child : this->children){
        if(child->panel_type == panel_type)
            return child;
    }
    return nullptr;
}