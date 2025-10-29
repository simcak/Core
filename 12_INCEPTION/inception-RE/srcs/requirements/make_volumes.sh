#!/bin/bash
DATA_DIR="/home/${USER}/data"

if [ ! -d "$DATA_DIR" ]; then
	mkdir -p "$DATA_DIR/mariadb" "$DATA_DIR/wordpress"
fi