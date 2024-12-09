# Build cmake from the nix environment.
#
# Original source: https://gist.github.com/pmenke-de/2fed80213c48c2fe80891678f4fa3b42#file-nix-cmake-sh

BUILDERSCRIPT=build.sh
BASEDIR="$(dirname $0)"

$BASEDIR/nix-run.sh cmake "$@"