{
    description = "atom.engine";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
        nixpkgs_glfw3.url = "github:nixos/nixpkgs/7a339d87931bba829f68e94621536cad9132971a";

        atom_core.url = "github:shifu-dev/atom.core";
        atom_core.inputs.nixpkgs.follows = "nixpkgs";

        atom_logging.url = "github:shifu-dev/atom.logging";
        atom_logging.inputs.atom_core.follows = "atom_core";
        atom_logging.inputs.nixpkgs.follows = "nixpkgs";
    };

    outputs = { self, nixpkgs, nixpkgs_glfw3, atom_core, atom_logging }:
    let
        system = "x86_64-linux";
        pkgs = nixpkgs.legacyPackages.${system};
        lib = pkgs.lib;
        stdenv = pkgs.llvmPackages_18.libcxxStdenv;
        atom_core_pkg = atom_core.packages.${system}.default;
        atom_logging_pkg = atom_logging.packages.${system}.default;
        glfw3 = nixpkgs_glfw3.legacyPackages.${system}.pkgs.glfw;

        imgui = stdenv.mkDerivation rec {
            pname = "imgui";
            version = "docking";

            src = pkgs.fetchFromGitHub {
                owner = "ocornut";
                repo = "imgui";
                rev = version;
                # sha256 = "";
                # sha256 = "sha256-rJMWCPVhho34NcPvJZaB5d6EbZkJyLXEfeotplOOaiA=";
                sha256 = "sha256-QZaHHg/cHPjI7P1Ggw2zfJNW1gnOA4zvmLv/cGjVk/M=";
            };

            dontBuild = true;

            installPhase = ''
                mkdir -p $out/include/imgui

                cp *.h $out/include/imgui
                cp *.cpp $out/include/imgui
                cp -a backends $out/include/imgui/
                cp -a misc $out/include/imgui/
            '';

            meta = with lib; {
                description = "Bloat-free Graphical User interface for C++ with minimal dependencies";
                homepage = "https://github.com/ocornut/imgui";
                license = licenses.mit;
                maintainers = with maintainers; [ wolfangaukang ];
                platforms = platforms.all;
            };
        };

        derivation = stdenv.mkDerivation rec {

            name = "atom.engine";

            src = ./.;

            buildInputs = [
                atom_core_pkg
                atom_logging_pkg
                glfw3
                imgui

                pkgs.catch2_3
                pkgs.fmt
                pkgs.magic-enum
                pkgs.glm
                pkgs.entt
                pkgs.stb

                pkgs.cmake
                pkgs.cmake-format
                pkgs.ninja
                pkgs.git
            ];

            configurePhase = ''
                cmake -S . -B build
            '';

            buildPhase = ''
                cmake --build build --target atom.engine
            '';

            installPhase = ''
                cmake --install build --prefix $out
            '';

            imgui_DIR = "${imgui}/include/imgui";
            stb_include_dir = "${pkgs.stb}/include";

            CXXFLAGS = lib.strings.concatStrings [
                " -I ${atom_core_pkg}/include"
                " -I ${glfw3}/include"
                " -I ${pkgs.glm}/include"
                " -I ${pkgs.entt}/include"
                " -I ${stb_include_dir}"
                " -I /nix/store/csml9b5w7z51yc7hxgd2ax4m6vj36iyq-libcxx-18.1.5-dev/include"
                " -I /nix/store/2sf9x4kf8lihldhnhp2b8q3ybas3p83l-compiler-rt-libc-18.1.5-dev/include"
                " -I /nix/store/hrssqr2jypca2qcqyy1xmfdw71nv6n14-catch2-3.5.2/include"
                " -I /nix/store/zc8xnz48ca61zjplxc3zz1ha3zss046p-fmt-10.2.1-dev/include"
                " -I /nix/store/2j35qpxbprdgcixyg70lyy6m0yay9352-magic-enum-0.9.5/include"
                " -I /nix/store/k3701zl6gmx3la7y4dnflcvf3xfy88kh-python3-3.11.9/include"
                " -I /nix/store/csml9b5w7z51yc7hxgd2ax4m6vj36iyq-libcxx-18.1.5-dev/include/c++/v1"
                " -I /nix/store/fymdqlxx6zsqvlmfwls3h2fly9kz0vcf-clang-wrapper-18.1.5/resource-root/include"
                " -I /nix/store/s3pvsv4as7mc8i2nwnk2hnsyi2qdj4bq-glibc-2.39-31-dev/include"
            ];

            CMAKE_GENERATOR = "Ninja";
            CMAKE_BUILD_TYPE = "Debug";
            CMAKE_EXPORT_COMPILE_COMMANDS = "true";
        };
    in
    {
        devShells.${system}.default = derivation;
        packages.${system}.default = derivation;
    };
}
