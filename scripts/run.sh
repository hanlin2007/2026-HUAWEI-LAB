#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$project_root"

if [[ ! -f build/wsl-debug/CTestTestfile.cmake ]]; then
    echo "Build the project first: bash scripts/build.sh" >&2
    exit 1
fi

ctest --preset wsl-debug --no-tests=error
