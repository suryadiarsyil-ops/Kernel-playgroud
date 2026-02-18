#!/bin/bash
# scripts/unload_all.sh — Unload all kernel modules

echo "=== Unloading modules ==="
for mod in asm_module chardev hello; do
    if lsmod | grep -q "^$mod"; then
        echo "  rmmod $mod"
        sudo rmmod "$mod"
    else
        echo "  $mod not loaded, skipping"
    fi
done

echo ""
echo "=== dmesg output (last 10 lines) ==="
dmesg | tail -10
