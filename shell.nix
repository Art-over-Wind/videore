let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs-channels/archive/nixos-unstable.tar.gz";

  pkgs = (import nixpkgs { }).pkgsCross.vc4;
  buildPkgs = (import nixpkgs { });

in
	pkgs.pkgsStatic.callPackage ({ mkShell }: mkShell {
	    nativeBuildInputs = with buildPkgs; [
	        cmake
	    ];
	}) {}
