export module atom.engine:rendering.buffer_layout;

import atom.core;
import std;

namespace atom::engine
{
    enum class shader_data_type
    {
        none,
        boolean,
        int1,
        int2,
        int3,
        int4,
        float1,
        float2,
        float3,
        float4,
        mat3,
        f32mat4,
    };

    constexpr auto get_shader_data_type_size(shader_data_type type) -> usize
    {
        switch (type)
        {
            case shader_data_type::none:    return 0;
            case shader_data_type::boolean: return 1;
            case shader_data_type::int1:    return 4 * 1;
            case shader_data_type::int2:    return 4 * 2;
            case shader_data_type::int3:    return 4 * 3;
            case shader_data_type::int4:    return 4 * 4;
            case shader_data_type::float1:  return 4;
            case shader_data_type::float2:  return 4 * 2;
            case shader_data_type::float3:  return 4 * 3;
            case shader_data_type::float4:  return 4 * 4;
            case shader_data_type::mat3:    return 4 * 3 * 3;
            case shader_data_type::f32mat4:    return 4 * 4 * 4;
            default:
            {
                contract_panic("invalid shader_data_type.");
                return 0;
            }
        }
    }

    class buffer_element
    {
    public:
        buffer_element(shader_data_type type, string_view name, bool is_normalized = false)
            : name(name)
            , type(type)
            , size(get_shader_data_type_size(type))
            , offset( 0 )
            , is_normalized(is_normalized)
        {}

    public:
        auto get_component_count() const -> u32
        {
            switch (type)
            {
                case shader_data_type::boolean: return 1;
                case shader_data_type::int1:    return 1;
                case shader_data_type::int2:    return 2;
                case shader_data_type::int3:    return 3;
                case shader_data_type::int4:    return 4;
                case shader_data_type::float1:  return 1;
                case shader_data_type::float2:  return 2;
                case shader_data_type::float3:  return 3;
                case shader_data_type::float4:  return 4;
                case shader_data_type::mat3:    return 3 * 3;
                case shader_data_type::f32mat4:    return 4 * 4;
                default:
                {
                    contract_panic("invalid shader_data_type.");
                    return 0;
                }
            }
        }

    public:
        string name;
        shader_data_type type;
        u32 size;
        u32 offset;
        bool is_normalized;
    };

    class buffer_layout
    {
    public:
        buffer_layout()
            : _elements()
            , _stride( 0 )
        {}

        buffer_layout(std::initializer_list<buffer_element> layout)
            : _elements(ranges::from(layout))
        {
            _calculate_offset_and_stride();
        }

    public:
        auto get_elements() const -> array_view<buffer_element>
        {
            return _elements;
        }

        auto get_stride() const -> u32
        {
            return _stride;
        }

    private:
        auto _calculate_offset_and_stride() -> void
        {
            u32 offset = 0;
            _stride = 0;
            for (buffer_element& elem : _elements)
            {
                elem.offset = offset;
                offset += elem.size;
                _stride += elem.size;
            }
        }

    private:
        dynamic_array<buffer_element> _elements;
        u32 _stride;
    };
}
