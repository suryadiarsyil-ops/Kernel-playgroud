# 🧪 Kernel Playground

A hands-on repository for **Linux Kernel Module (LKM) development** targeting **Android Common Kernel (ACK) GKI 5.10 — ARM64**.

Includes a fully automated GitHub Actions CI/CD pipeline that builds the kernel image, installs modules, and packages a flashable ZIP via **AnyKernel3**.

---

## 📁 Project Structure

```
Kernel-playground/
├── .github/
│   └── workflows/
│       └── build.yml         # CI/CD — build ACK GKI 5.10 ARM64
├── modules/                  # Out-of-tree LKM source files
│   ├── hello/                # Basic hello world LKM
│   ├── chardev/              # Character device driver
│   └── asm_module/           # LKM with inline ARM64 Assembly
├── asm/                      # Standalone Assembly experiments
│   ├── x86/                  # x86-64 Assembly snippets
│   └── arm/                  # ARM64 Assembly snippets
├── scripts/                  # Helper shell scripts
├── docs/                     # Documentation & notes
├── Makefile                  # Top-level build system
└── README.md
```

---

## 🚀 CI/CD — GitHub Actions

Push ke branch `main` atau trigger manual via **Actions → Run workflow** akan:

1. Clone **ACK GKI 5.10** (`android12-5.10`)
2. Configure kernel (`defconfig` + custom tweaks)
3. Build `Image.gz` dan kernel modules dengan **ccache**
4. Package flashable ZIP via **AnyKernel3**
5. Upload artifact: `Kernel-Playground-ARM64-YYYYMMDD.zip`

---

## 🛠️ Build Lokal (ARM64 Cross-Compile)

### Prerequisites

```bash
sudo apt update
sudo apt install -y \
  gcc-aarch64-linux-gnu build-essential bc bison flex \
  libssl-dev libelf-dev dwarves git make python3 rsync kmod cpio ccache
```

### Clone & Build ACK

```bash
git clone --depth=1 --branch android12-5.10 \
  https://android.googlesource.com/kernel/common linux-src

cd linux-src
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc) Image.gz
```

### Build Out-of-Tree Modules

```bash
cd modules/hello
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- \
     KDIR=../../linux-src
```

---

## 📦 Modules

| Module        | Description                              |
|---------------|------------------------------------------|
| `hello`       | Basic LKM — init/exit lifecycle          |
| `chardev`     | Character device dengan read/write ops   |
| `asm_module`  | LKM dengan inline ARM64 Assembly         |

---

## ⚠️ Warning

Selalu test di **virtual machine** atau device test. Kernel module yang buggy bisa crash seluruh sistem.

---

## 📚 Resources

- [Android Common Kernel](https://android.googlesource.com/kernel/common)
- [AnyKernel3](https://github.com/osm0sis/AnyKernel3)
- [Linux Kernel Module Programming Guide](https://sysprog21.github.io/lkmpg/)
- [Kernel Newbies](https://kernelnewbies.org/)
