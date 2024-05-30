module;
#include "glslang/Public/ShaderLang.h"
#include "glslang/Public/ResourceLimits.h"
#include "glslang/SPIRV/GlslangToSpv.h"

module atom.engine:shaders.shader_compiler.impl;

import atom.core;
import :shaders;

namespace atom::engine
{
    auto _convert_shader_stage_to_glslang(shader_stage stage) -> EShLanguage
    {
        switch (stage)
        {
            case shader_stage::vertex_shader:   return EShLangVertex;
            case shader_stage::fragment_shader: return EShLangFragment;
            case shader_stage::compute_shader:  return EShLangCompute;
            case shader_stage::geometry_shader: return EShLangGeometry;
            default:
            {
                contract_panic("invalid value.");
            }
        }
    }

    auto shader_compiler::initialize() -> void
    {
        glslang::InitializeProcess();
    }

    auto shader_compiler::finalize() -> void
    {
        glslang::FinalizeProcess();
    }

    auto shader_compiler::compile_to_spirv(string_view source,
        shader_stage stage) -> result<dynamic_buffer<>, shader_compilation_error>
    {
        EShLanguage glslang_shader_stage = _convert_shader_stage_to_glslang(stage);
        glslang::TShader shader{ glslang_shader_stage };

        const char* strings = source.get_data();
        const int strings_sizes = source.get_size();
        shader.setStringsWithLengths(&strings, &strings_sizes, 1);

        int client_input_semantics_version = 100;
        glslang::EShTargetClientVersion client_version = glslang::EShTargetOpenGL_450;
        glslang::EShTargetLanguageVersion target_version = glslang::EShTargetSpv_1_0;

        shader.setEnvInput(glslang::EShSourceGlsl, glslang_shader_stage, glslang::EShClientOpenGL,
            client_input_semantics_version);
        shader.setEnvClient(glslang::EShClientOpenGL, client_version);
        shader.setEnvTarget(glslang::EShTargetSpv, target_version);

        const TBuiltInResource* resources = GetDefaultResources();
        EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgDefault);

        if (not shader.parse(resources, 100, false, messages))
        {
            return shader_compilation_error{
                string{ create_with_join, "glsl parsing failed: {}.", shader.getInfoLog() }
            };
        }

        std::vector<u32> out;
        glslang::GlslangToSpv(*shader.getIntermediate(), out);

        return dynamic_buffer{ create_from_std_vector, out };
    }
}
