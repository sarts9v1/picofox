#!/bin/sh

cmake -DPICO_PLATFORM=rp2350 -DPICO_BOARD=pico2 -S . -B out/build
