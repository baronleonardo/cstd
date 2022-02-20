{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
    name = "cstd-env";
    hardeningDisable = [ "all" ];
    packages = with pkgs; [
        gcc
        cmake
        gdb
        valgrind
    ];
}