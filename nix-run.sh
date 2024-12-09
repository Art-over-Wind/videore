# Run anything in Nix environment.
#
# Usage: ./nix-run.sh <COMMAND>
#
# Original source: https://gist.github.com/pmenke-de/2fed80213c48c2fe80891678f4fa3b42#file-nix-run-sh

if [ "$(basename "$0")" != "nix-run.sh" ]; then
  COMMAND="$(basename "$0")"
fi

# If this script ran already in the Nix env, then just execute the command.
if [ -n "$IS_NIX_ENV" ]; then
  exec "$COMMAND" "$@"
else
  DIR=$(dirname "$0")
  ARGS=$(printf '"%s" ' "$@")
  IS_NIX_ENV=1 nix-shell \
    --pure \
    --keep IS_NIX_ENV \
    --run "$COMMAND $ARGS" \
    $DIR

  exit $?
fi