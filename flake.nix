{
  description = "atom_engine";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs_glfw.url = "github:nixos/nixpkgs/7a339d87931bba829f68e94621536cad9132971a";

    atom_doc = {
        url = "github:shifu-dev/atom-doc";
        inputs.nixpkgs.follows = "nixpkgs";
    };

    atom_core = {
      url = "github:shifu-dev/atom_core";
      inputs.atom_doc.follows = "atom_doc";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    atom_logging = {
      url = "github:shifu-dev/atom_logging";
      inputs.atom_doc.follows = "atom_doc";
      inputs.atom_core.follows = "atom_core";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    imgui = {
      url = "github:ocornut/imgui/docking";
      flake = false;
    };

    msdfgen = {
      url = "github:Chlumsky/msdfgen";
      flake = false;
    };

    msdf_atlas_gen = {
      url = "github:Chlumsky/msdf-atlas-gen";
      flake = false;
    };
  };

  outputs = inputs:
    let
      system = "x86_64-linux";
      pkgs = inputs.nixpkgs.legacyPackages.${system};
      lib = pkgs.lib;
      stdenv = pkgs.llvmPackages_18.libcxxStdenv;

      atom_doc_pkg = inputs.atom_doc.packages.${system}.default;
      atom_core_env = inputs.atom_core.env.${system}.default;
      atom_core_pkg = inputs.atom_core.packages.${system}.default;
      atom_logging_env = inputs.atom_logging.env.${system}.default;
      atom_logging_pkg = inputs.atom_logging.packages.${system}.default;

      glfw_pkg = inputs.nixpkgs_glfw.legacyPackages.${system}.pkgs.glfw;
      glslang_pkg = pkgs.glslang.override { inherit stdenv; };

      imgui_pkg = (pkgs.imgui.override {
        glfw = glfw_pkg;
        IMGUI_BUILD_GLFW_BINDING = true;
        IMGUI_BUILD_OPENGL3_BINDING = true;
      }).overrideAttrs (old: {
        src = inputs.imgui;
      });

      msdfgen_pkg = stdenv.mkDerivation rec {
        name = "msdfgen";
        src = inputs.msdfgen;

        nativeBuildInputs = with pkgs; [
          cmake
          ninja
        ];

        propagatedBuildInputs = with pkgs; [
          freetype
          tinyxml-2
          libpng
        ];

        configurePhase = ''
          cmake -S . -B . -G Ninja \
            -D CMAKE_INSTALL_PREFIX=$out \
            -D MSDFGEN_USE_VCPKG=OFF \
            -D MSDFGEN_USE_SKIA=OFF \
            -D MSDFGEN_INSTALL=ON;
        '';
      };

      msdf_atlas_gen_pkg = stdenv.mkDerivation rec {
        name = "msdf-atlas-gen";
        src = inputs.msdf_atlas_gen;

        nativeBuildInputs = with pkgs; [
          cmake
          ninja
        ];

        propagatedBuildInputs = with pkgs; [
          msdfgen_pkg
          freetype
          tinyxml-2
          libpng
        ];

        configurePhase = ''
          cmake -S . -B . -G Ninja \
            -D CMAKE_INSTALL_PREFIX=$out \
            -D MSDF_ATLAS_MSDFGEN_EXTERNAL=ON \
            -D MSDF_ATLAS_NO_ARTERY_FONT=ON \
            -D MSDF_ATLAS_USE_VCPKG=OFF \
            -D MSDF_ATLAS_USE_SKIA=OFF \
            -D MSDF_ATLAS_INSTALL=ON;
        '';
      };
    in rec
    {
      env.${system}.default = rec {
        name = "atom_engine";
        src = ./.;

        propagatedBuildInputs = with pkgs; [
          atom_core_pkg
          atom_logging_pkg
          glfw_pkg
          imgui_pkg
          glslang_pkg
          msdfgen_pkg
          msdf_atlas_gen_pkg

          glm
          entt
          stb
          box2d
        ];

        nativeBuildInputs = with pkgs; [
          atom_doc_pkg
          doxygen
          graphviz
          cmake
          cmake-format
          ninja
          git
        ];

        configurePhase = ''
          cmake -S . -B build \
            -D ATOM_ENGINE_ASSETS_DIR=$out/assets \
            -D CMAKE_INSTALL_PREFIX=$out;
        '';

        buildPhase = ''
          cmake --build build --target atom_engine;
        '';

        installPhase = ''
          cmake --install build;
        '';

        clang_scan_deps_include_paths = [
          "${atom_core_pkg}/include"
          "${atom_logging_pkg}/include"
          "${glfw_pkg}/include"
          "${imgui_pkg}/include"
          "${glslang_pkg}/include"
          "${msdfgen_pkg}/include"
          "${msdf_atlas_gen_pkg}/include"
          "${pkgs.glm}/include"
          "${pkgs.entt}/include"
          "${pkgs.stb}/include"
          "${pkgs.box2d}/include"
        ];

        envVars = {
          CMAKE_GENERATOR = "Ninja";
          CMAKE_BUILD_TYPE = "Debug";
          CMAKE_EXPORT_COMPILE_COMMANDS = "true";

          CXXFLAGS = lib.strings.concatMapStrings (v: " -I " + v) (
            atom_core_env.clang_scan_deps_include_paths ++
            atom_logging_env.clang_scan_deps_include_paths ++
            clang_scan_deps_include_paths
          );

          ATOM_DOC_DOXYFILE_DIR = atom_doc_pkg;
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
