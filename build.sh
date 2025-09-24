#!/bin/bash

set -e

python3 generate-form.py
python3 generate-maps.py
python3 generate-script.py
make -j$(nproc)