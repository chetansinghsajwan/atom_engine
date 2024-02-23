export module atom.engine:input_device;
import atom.core;

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

    export class input_device
    {
    public:
        input_device(input_device_id id, string name)
            : _id(id)
            , _name(name)
        {}

        virtual ~input_device() = default;

    public:
        auto get_id() const -> input_device_id
        {
            return _id;
        }

        auto get_name() const -> string_view
        {
            return _name;
        }

    private:
        const input_device_id _id;
        const string _name;
    };
}
