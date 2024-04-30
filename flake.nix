{
    description = "atom-engine";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    };

    outputs = { self, nixpkgs }:
    let
        system = "x86_64-linux";
        pkgs = nixpkgs.legacyPackages.${system};
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
                glfw
            ];
        };
    };
}
