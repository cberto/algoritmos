#!/usr/bin/env bash
set -euo pipefail

# Resolver las rutas desde el script, aunque se invoque desde otra carpeta.
project_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$project_dir"

case "$(uname -s)" in
    Linux)
        build_dir="build/linux"
        compiler="g++"
        ;;
    Darwin)
        build_dir="build/macos"
        compiler="clang++"
        ;;
    *)
        printf 'Sistema no compatible con este script. En Windows usa compilar.bat.\n' >&2
        exit 1
        ;;
esac

cmake -S . -B "$build_dir" -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER="$compiler"
cmake --build "$build_dir" --parallel

printf '\nCompilacion completada: %s/%s/bin/tp_integrador\n' "$project_dir" "$build_dir"
