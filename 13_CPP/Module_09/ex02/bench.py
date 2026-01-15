#!/usr/bin/env python3
"""
Simple helper to build and run PmergeMe on random permutations.

Usage:
  python3 bench.py [sizes...]
"""
import random
import subprocess
import sys
import re
import math
from pathlib import Path


ROOT = Path(__file__).resolve().parent
BIN = ROOT / "PmergeMe"

CMP_RE = re.compile(r"Comparisons with std::vector\s*:\s*(\d+)")


def ford_johnson_bound(n: int) -> int:
    total = 0
    for k in range(1, n + 1):
        total += math.ceil(math.log(0.75 * k, 2))
    return total

def build():
    if BIN.exists():
        return
    subprocess.run(["make"], cwd=ROOT, check=True)


def run_case(size: int):
    nums = random.sample(range(1, size + 1), size)
    cmd = [str(x) for x in nums]
    proc = subprocess.run([str(BIN), *cmd], cwd=ROOT, capture_output=True, text=True)
    if proc.returncode != 0:
        raise RuntimeError(f"PmergeMe failed (n={size}): {proc.stderr.strip()}")

    match = CMP_RE.search(proc.stdout)
    comps = int(match.group(1)) if match else None
    bound = ford_johnson_bound(size)
    return comps, bound


def main():
    sizes = [int(x) for x in sys.argv[1:]] if len(sys.argv) > 1 else [10, 21, 30, 50, 100]
    build()
    for n in sizes:
        comps, bound = run_case(n)
        if comps is None:
            print(f"n={n}\tcomparisons=not reported\tF(n) bound={bound}")
        else:
            print(f"n={n}\tcomparisons={comps}\tF(n) bound={bound}")


if __name__ == "__main__":
    main()
