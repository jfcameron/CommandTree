#!/usr/bin/env bash

# Demo
DEMO_SOURCE_ROOT_DIR="../demo"

# Lib
SOURCE_ROOT_DIR="../src"
PUBLIC_HEADER_DIR="../include"
PRIVATE_HEADER_DIR="${SOURCE_ROOT_DIR}/include"

g++ \
    "${DEMO_SOURCE_ROOT_DIR}"/*.cpp \
    "${SOURCE_ROOT_DIR}"/*.cpp \
    -I"${PUBLIC_HEADER_DIR}" \
    -I"${PRIVATE_HEADER_DIR}" \
    -std=c++17

