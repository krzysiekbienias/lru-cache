#!/usr/bin/env bash
set -e

ninja -C cmake-build-debug lru_cache_tests
./cmake-build-debug/lru_cache_tests ${1:+--gtest_filter="$1.*"}