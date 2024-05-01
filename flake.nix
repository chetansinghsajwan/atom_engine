{
    description = "atom-engine";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
        nixpkgs_glfw3.url = "github:nixos/nixpkgs/7a339d87931bba829f68e94621536cad9132971a";
    };

    outputs = { self, nixpkgs, nixpkgs_glfw3 }:
    let
        system = "x86_64-linux";
        pkgs = nixpkgs.legacyPackages.${system};
        pkgs_glfw3 = nixpkgs_glfw3.legacyPackages.${system};
    in
    {
        devShells.${system}.default = pkgs.mkShell {

            packages = with pkgs; [
                clang_18
                clang-tools_18
                cmake
                cmake-format
                gnumake
                ninja
                pkgs_glfw3.glfw
            ];
        };
    };
}
