{
  description = "atom-engine";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs_glfw.url = "github:nixos/nixpkgs/7a339d87931bba829f68e94621536cad9132971a";

    atom_core = {
      url = "github:shifu-dev/atom_core";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    atom_logging = {
      url = "github:shifu-dev/atom_logging";
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

      glslang_pkg = stdenv.mkDerivation rec {
        pname = "glslang";
        version = "14.2.0";

        src = pkgs.fetchFromGitHub {
          owner = "KhronosGroup";
          repo = "glslang";
          rev = version;
          hash = "sha256-B6jVCeoFjd2H6+7tIses+Kj8DgHS6E2dkVzQAIzDHEc=";
        };

        # These get set at all-packages, keep onto them for child drvs
        passthru = {
          spirv-tools = pkgs.spirv-tools;
          spirv-headers = pkgs.spirv-headers;
        };

        nativeBuildInputs = with pkgs; [
          cmake
          python3
          bison
          jq
        ];

        postPatch = ''
          cp --no-preserve=mode -r "${pkgs.spirv-tools.src}" External/spirv-tools
          ln -s "${pkgs.spirv-headers.src}" External/spirv-tools/external/spirv-headers
        '';

        # This is a dirty fix for lib/cmake/SPIRVTargets.cmake:51 which includes this directory
        postInstall = ''
          mkdir $out/include/External
        '';

        # Fix the paths in .pc, even though it's unclear if these .pc are really useful.
        postFixup = ''
          substituteInPlace $out/lib/pkgconfig/*.pc \
          --replace '=''${prefix}//' '=/'

          # add a symlink for backwards compatibility
          ln -s $out/bin/glslang $out/bin/glslangValidator
        '';
      };

      msdfgen_pkg = stdenv.mkDerivation rec {
        pname = "msdfgen";
        version = "v1.12";

        src = pkgs.fetchFromGitHub {
          owner = "Chlumsky";
          repo = "msdfgen";
          rev = version;
          hash = "sha256-QLzfZP9Xsc5HBvF+riamqVY0pYN5umyEsiJV7W8JNyI=";
        };

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
          cmake \
            -S . \
            -B . \
            -G Ninja \
            -D CMAKE_INSTALL_PREFIX=$out \
            -D MSDFGEN_USE_VCPKG=OFF \
            -D MSDFGEN_USE_SKIA=OFF \
            -D MSDFGEN_INSTALL=ON;
        '';
      };

      msdf-atlas-gen_pkg = stdenv.mkDerivation rec {
        pname = "msdf-atlas-gen";
        version = "v1.3";

        src = pkgs.fetchFromGitHub {
          owner = "Chlumsky";
          repo = "msdf-atlas-gen";
          rev = version;
          hash = "sha256-SfzQ008aoYI8tkrHXsXVQq9Qq+NIqT1zvSIHK1LTbLU=";
          fetchSubmodules = true;
          leaveDotGit = true;
        };

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
          cmake \
            -S . \
            -B . \
            -G Ninja \
            -D CMAKE_INSTALL_PREFIX=$out \
            -D MSDF_ATLAS_MSDFGEN_EXTERNAL=ON \
            -D MSDF_ATLAS_NO_ARTERY_FONT=ON \
            -D MSDF_ATLAS_USE_VCPKG=OFF \
            -D MSDF_ATLAS_USE_SKIA=OFF \
            -D MSDF_ATLAS_INSTALL=ON;
        '';
      };

    in
    rec
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
          glslang_pkg
          msdfgen_pkg
          msdf-atlas-gen_pkg
        ];

        nativeBuildInputs = with pkgs; [
          cmake
          cmake-format
          ninja
          git
        ];

        configurePhase = ''
          cmake \
            -S . \
            -B build \
            -D ATOM_ENGINE_ASSETS_DIR=$out/assets \
            -D CMAKE_INSTALL_PREFIX=$out \
            -D box2d_DIR=${pkgs.box2d} \
            -D EnTT_DIR=${pkgs.entt} \
            -D glm_DIR=${pkgs.glm} \
            -D glslang_DIR=${glslang_pkg} \
            -D glfw3_DIR=${glfw_pkg} \
            -D msdfgen_DIR=${msdfgen_pkg};
            -D msdf-atlas-gen_DIR=${msdf-atlas-gen_pkg};
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
          "${glslang_pkg}/include"
          "${msdfgen_pkg}/include"
          "${msdf-atlas-gen_pkg}/include"
        ];

        envVars = {
          CXXFLAGS = lib.strings.concatMapStrings (v: " -I " + v) (
            atom_core_env.clang_scan_deps_include_paths ++
            atom_logging_env.clang_scan_deps_include_paths ++
            clang_scan_deps_include_paths
          );
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
