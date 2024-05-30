{
    description = "atom-engine";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
        nixpkgs_glfw.url = "github:nixos/nixpkgs/7a339d87931bba829f68e94621536cad9132971a";

        atom_core = {
            url = "github:shifu-dev/atom.core";
            inputs.nixpkgs.follows = "nixpkgs";
        };

        atom_logging = {
            url = "github:shifu-dev/atom.logging";
            inputs.atom_core.follows = "atom_core";
            inputs.nixpkgs.follows = "nixpkgs";
        };

        imgui = {
            url = "github:ocornut/imgui/docking";
            flake = false;
        };
    };

    outputs = inputs:
    let
        system = "x86_64-linux";
        pkgs = inputs.nixpkgs.legacyPackages.${system};
        lib = pkgs.lib;
        stdenv = pkgs.llvmPackages_18.libcxxStdenv;
        glfw_pkg = inputs.nixpkgs_glfw.legacyPackages.${system}.pkgs.glfw;
        atom_core_env = inputs.atom_core.env.${system}.default;
        atom_core_pkg = inputs.atom_core.packages.${system}.default;
        atom_logging_env = inputs.atom_logging.env.${system}.default;
        atom_logging_pkg = inputs.atom_logging.packages.${system}.default;

        imgui_pkg = stdenv.mkDerivation rec {
            pname = "imgui";
            version = "docking";

            src = inputs.imgui;

            dontBuild = true;

            installPhase = ''
                mkdir -p $out/include/imgui

                cp *.h $out/include/imgui
                cp *.cpp $out/include/imgui
                cp -a backends $out/include/imgui/
                cp -a misc $out/include/imgui/
            '';
        };
    in rec
    {
        env.${system}.default = rec {

            name = "atom-engine";

            src = ./.;

            propagatedBuildInputs = with pkgs; [
                atom_core_pkg
                atom_logging_pkg
                glfw_pkg
                imgui_pkg
                glm
                entt
                stb
                box2d
                glslang
                spirv-cross
            ];

            nativeBuildInputs = with pkgs; [
                cmake
                cmake-format
                ninja
                git
            ];

            configurePhase = ''
                cmake -S . -B build \
                    -D ATOM_ENGINE_ASSETS_DIR=$out/assets \
                    -D CMAKE_INSTALL_PREFIX=$out \
                    -D box2d_DIR=${pkgs.box2d} \
                    -D EnTT_DIR=${pkgs.entt} \
                    -D glm_DIR=${pkgs.glm} \
                    -D glfw3_DIR=${glfw_pkg};
            '';

            buildPhase = ''
                cmake --build build --target atom.engine;
            '';

            installPhase = ''
                cmake --install build;
            '';

            clang_scan_deps_include_paths = [
                "${glfw_pkg}/include"
                "${pkgs.glm}/include"
                "${pkgs.entt}/include"
                "${pkgs.box2d}/include"
                "${pkgs.stb}/include"
                "${pkgs.glslang}/include"
            ];

            envVars = {
                CXXFLAGS = lib.strings.concatMapStrings (v: " -I " + v) (
                    atom_core_env.clang_scan_deps_include_paths ++
                    atom_logging_env.clang_scan_deps_include_paths ++
                    clang_scan_deps_include_paths);
                CMAKE_GENERATOR = "Ninja";
                CMAKE_BUILD_TYPE = "Debug";
                CMAKE_EXPORT_COMPILE_COMMANDS = "true";

                imgui_DIR = "${imgui_pkg}/include/imgui";
                stb_include_dir = "${pkgs.stb}/include";
            };
        };

        devShells.${system}.default = with env.${system}.default; stdenv.mkDerivation ({
            inherit name;
            inherit src;
            inherit propagatedBuildInputs;
            inherit nativeBuildInputs;
        } // envVars);

        packages.${system}.default = with env.${system}.default; stdenv.mkDerivation ({
            inherit name;
            inherit src;
            inherit propagatedBuildInputs;
            inherit nativeBuildInputs;
            inherit configurePhase;
            inherit buildPhase;
            inherit installPhase;
        } // envVars);
    };
}
