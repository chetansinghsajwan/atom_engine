export module atom_engine:inputs.input_device;

import atom_core;

namespace atom::engine
{
    export class input_device_id
    {
    public:
        input_device_id(usize num)
            : num(num)
        {}

    public:
        usize num;
    };

    export enum class input_device_type
    {
        keyboard,
        mouse,
        gamepad,
        joystick,
        touchpad,
        lightpen
    };

    export class input_device
    {
    public:
        input_device(input_device_id id, input_device_type type, string name)
            : _id(id)
            , _type(type)
            , _name(move(name))
        {}

        virtual ~input_device() = default;

    public:
        auto get_id() const -> input_device_id
        {
            return _id;
        }

        auto get_type() const -> input_device_type
        {
            return _type;
        }

        auto get_name() const -> string_view
        {
            return _name;
        }

    private:
        const input_device_id _id;
        const input_device_type _type;
        const string _name;
    };
}
