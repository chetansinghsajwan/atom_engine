module;
#include "glslang/Public/ShaderLang.h"
#include "glslang/Public/ResourceLimits.h"
#include "glslang/SPIRV/GlslangToSpv.h"

module atom.engine:shaders.spirv_compiler.impl;

import atom.core;
import :shaders.spirv_compiler;
import :shaders.shader_utils;

namespace atom::engine
{
    auto spirv_compiler::initialize() -> void
    {
        contract_expects(not is_initialized(), "already initialized.");

        _is_initialized = true;
        glslang::InitializeProcess();
    }

    auto spirv_compiler::finalize() -> void
    {
        contract_expects(is_initialized(), "not initialized yet.");

        _is_initialized = false;
        glslang::FinalizeProcess();
    }

    auto spirv_compiler::is_initialized() -> bool
    {
        return _is_initialized;
    }

    auto _convert_stage_to_glslang(shader_stage stage) -> EShLanguage
    {
        switch (stage)
        {
            case shader_stage::vertex:   return EShLangVertex;
            case shader_stage::fragment: return EShLangFragment;
            case shader_stage::compute:  return EShLangCompute;
            case shader_stage::geometry: return EShLangGeometry;
            default:
            {
                contract_panic("invalid value.");
            }
        }
    }

    auto _compile_shader(shader_stage stage, string_view source)
        -> result<dynamic_buffer, shader_compilation_error, shader_linking_error>
    {
        const char* shader_strings[1];
        shader_strings[0] = source.get_data();

        EShLanguage glslang_shader_stage = _convert_stage_to_glslang(stage);
        glslang::TShader shader(glslang_shader_stage);

        const char* strings = source.get_data();
        const int strings_sizes = source.get_size();

        shader.setStringsWithLengths(&strings, &strings_sizes, 1);
        shader.setEnvInput(
            glslang::EShSourceGlsl, glslang_shader_stage, glslang::EShClientOpenGL, 450);
        shader.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);
        shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);
        shader.setAutoMapLocations(true);

        auto resource = GetDefaultResources();
        bool parse_sucess = shader.parse(resource, 450, false, EShMsgDefault);
        if (not parse_sucess)
        {
            return shader_compilation_error{
                string{ create_with_join, "glsl parsing failed: {}.", shader.getInfoLog() }
            };
        }

        glslang::TProgram program;
        program.addShader(&shader);

        bool link_success = program.link(EShMsgDefault);
        if (not link_success)
        {
            return shader_linking_error{};
        }

        std::vector<uint32_t> spirv;
        glslang::GlslangToSpv(*program.getIntermediate(glslang_shader_stage), spirv);

        return dynamic_buffer{ create_from_std_vector, spirv };
    }

    auto spirv_compiler::compile(
        shader_stage stage, string_view source) -> spirv_compilation_result
    {
        contract_debug_expects(is_initialized(), "not initialized yet.");

        return _compile_shader(stage, source);
    }

    bool spirv_compiler::_is_initialized = false;
}
