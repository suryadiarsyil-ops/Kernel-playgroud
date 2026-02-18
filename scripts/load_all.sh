#!/bin/bash
# scripts/load_all.sh — Build and load all kernel modules

set -e

echo "=== Building all modules ==="
make -C "$(dirname "$0")/.." all

echo ""
echo "=== Loading modules ==="
for ko in modules/hello/hello.ko modules/chardev/chardev.ko modules/asm_module/asm_module.ko; do
    echo "  insmod $ko"
    sudo insmod "$ko"
done

echo ""
echo "=== dmesg output (last 20 lines) ==="
dmesg | tail -20
