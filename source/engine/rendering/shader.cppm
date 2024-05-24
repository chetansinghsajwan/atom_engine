export module atom.engine:rendering.shader;

import atom.core;
import :math;

namespace atom::engine
{
    export class shader
    {
    public:
        virtual ~shader() {}

    public:
        virtual auto bind() -> void = 0;
        virtual auto unbind() -> void = 0;

        virtual auto set_uniform_int(string_view name, i32 value) -> void = 0;
        virtual auto set_uniform_float(string_view name, float value) -> void = 0;
        virtual auto set_uniform_float4(string_view name, const f32vec4& vec) -> void = 0;
        virtual auto set_uniform_mat4(string_view name, const f32mat4& mat) -> void = 0;
        virtual auto set_int_array(string_view name, const int* array, usize count) -> void = 0;
    };
}
