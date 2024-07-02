export module atom.engine.sandbox:sandbox2d_layer;

import atom_core;
import atom_logging;
import atom.engine;

using namespace atom;

export class sandbox2d_layer: public engine::layer
{
public:
    sandbox2d_layer();

    ~sandbox2d_layer();

public:
    virtual auto on_attach() -> void override;

    virtual auto on_deattach() -> void override;

    virtual auto on_update(engine::time_step time) -> void override;

private:
    logging::logger* _logger = nullptr;
    engine::window* _window = nullptr;
    engine::keyboard* _keyboard = nullptr;
    engine::mouse* _mouse = nullptr;

    engine::world* _world = nullptr;
    engine::entity_manager* _entity_manager = nullptr;
    engine::entity_id _camera_entity;
    engine::entity_id _box1_entity;
    engine::entity_id _box2_entity;
    engine::texture2d* _cherno_texture;
};
