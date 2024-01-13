{
    description = "atom-engine";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    };

    outputs = { self, nixpkgs }:
    let
        system = "x86_64-linux";
        pkgs = nixpkgs.legacyPackages.${system};

        atom-core = pkgs.fetchFromGitHub {
            owner = "shifu-dev";
            repo = "Atom.Core";
            rev = "dev";
            sha256 = "sha256-XuGBLoVDY6NxVcTD0cYzX71bMV2opQ77FRlvdtgHAHE";
        };
        
        atom-logging = pkgs.fetchFromGitHub {
            owner = "shifu-dev";
            repo = "Atom.Logging";
            rev = "dev";
            sha256 = "sha256-q/+IyMVXi7FCA6Hj+rvr6n9reQNuR1a5W52WLhaJcOg";
        };
    in
    {
        devShells.${system}.default = pkgs.mkShell {
            
            packages = with pkgs; [
                cmake
                gnumake
                ninja
                glfw
                catch2
            ];

            env = {
                "ATOM_CORE" = atom-core;
                "ATOM_LOGGING" = atom-logging;
            };
        };
    };
}