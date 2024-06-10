export module atom.engine:shaders.shader_utils;

import std;
import atom.core;

namespace atom::engine
{
    export enum class shader_stage
    {
        vertex,
        fragment,
        geometry,
        compute,
        mesh,
        task,
        tessellation_control,
        tessellation_evaluation,
        ray_generation,
        ray_intersection,
        ray_any_hit,
        ray_closest_hit,
        ray_miss,
        ray_callable,

        COUNT,
    };

    export class shader_utils
    {
    public:
        static auto get_extension_strings() -> array_view<string_view>
        {
            static constexpr string_view extensions[] = {
                "vert",
                "frag",
                "geom",
                "comp",
                "mesh",
                "task",
                "tesc",
                "tese",
                "rgen",
                "rint",
                "rahit",
                "rchit",
                "rmiss",
                "rcall",
            };

            return array_view<string_view>{ extensions };
        }

        static auto get_stages() -> array_view<shader_stage>
        {
            static constexpr shader_stage stages[] = {
                shader_stage::vertex,
                shader_stage::fragment,
                shader_stage::geometry,
                shader_stage::compute,
                shader_stage::mesh,
                shader_stage::task,
                shader_stage::tessellation_control,
                shader_stage::tessellation_evaluation,
                shader_stage::ray_generation,
                shader_stage::ray_intersection,
                shader_stage::ray_any_hit,
                shader_stage::ray_closest_hit,
                shader_stage::ray_miss,
                shader_stage::ray_callable,
            };

            return array_view<shader_stage>{ stages };
        }

        static auto consteval get_stage_count() -> usize
        {
            return (usize)shader_stage::COUNT;
        }

        static auto get_file_extension_for_stage(shader_stage stage) -> string_view
        {
            switch (stage)
            {
                case shader_stage::vertex:                  return "vert";
                case shader_stage::fragment:                return "frag";
                case shader_stage::geometry:                return "geom";
                case shader_stage::compute:                 return "comp";
                case shader_stage::mesh:                    return "mesh";
                case shader_stage::task:                    return "task";
                case shader_stage::tessellation_control:    return "tesc";
                case shader_stage::tessellation_evaluation: return "tese";
                case shader_stage::ray_generation:          return "rgen";
                case shader_stage::ray_intersection:        return "rint";
                case shader_stage::ray_any_hit:             return "rahit";
                case shader_stage::ray_closest_hit:         return "rchit";
                case shader_stage::ray_miss:                return "rmiss";
                case shader_stage::ray_callable:            return "rcall";
                default:
                {
                    contract_panic("invalid value.");
                }
            }
        }
    };
}
