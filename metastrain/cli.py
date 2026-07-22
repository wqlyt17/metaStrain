#metastrain/cli.py

import argparse
import subprocess
import os
import sys
import time
from pathlib import Path


# =========================
# 全局路径
# =========================
BASE_DIR = Path(__file__).resolve().parent
SCRIPTS_DIR = BASE_DIR / "scripts"


# =========================
# run_cmd（统一执行器）
# =========================
def run_cmd(cmd):
    print(f"[metaStrain] Running: {cmd}")
    start = time.time()

    result = subprocess.run(
        cmd,
        text=True,
        capture_output=True
    )

    print(result.stdout)
    print(result.stderr)

    if result.returncode != 0:
        print("[metaStrain] ERROR: command failed")
        sys.exit(1)

    #print(f"[metaStrain] Done in {time.time() - start:.2f} s")

# -----------------------------
# identify 模块
# -----------------------------
def run_identify(args):

    script = SCRIPTS_DIR / "strain_identify.sh"

    if not script.exists():
        print(f"[metaStrain] ERROR: script not found: {script}")
        sys.exit(1)

    if not os.path.exists(args.input):
        print("[metaStrain] ERROR: input FASTQ not found")
        sys.exit(1)

    if not os.path.exists(args.species):
        print("[metaStrain] ERROR: species file not found")
        sys.exit(1)

    os.makedirs(args.output, exist_ok=True)

    cmd = [
        "bash",
        str(script),
        args.code,
        args.species,
        args.input,
        args.patterns,
        args.output
    ]

    run_cmd(cmd)


# -----------------------------
# reference 模块
# -----------------------------
def run_reference(args):

    script = SCRIPTS_DIR / "download_reference.sh"

    if not script.exists():
        print(f"[metaStrain] ERROR: script not found: {script}")
        sys.exit(1)

    if not os.path.exists(args.species):
        print("[metaStrain] ERROR: species file not found")
        sys.exit(1)

    os.makedirs(args.output, exist_ok=True)

    cmd = [
        "bash",
        str(script),
        args.species,
        args.code,
        args.output
    ]

    run_cmd(cmd)


# -----------------------------
# pattern 模块
# bash pattern_construction.sh species_pattern.txt ${path}/reference ${path}/code/patterns ${path}/patterns
# -----------------------------
def run_pattern(args):

    script = SCRIPTS_DIR / "pattern_construction.sh"

    if not script.exists():
        print(f"[metaStrain] ERROR: script not found: {script}")
        sys.exit(1)

    species_file = Path(args.species)
    if not species_file.exists():
        print("[metaStrain] ERROR: species file not found")
        sys.exit(1)

    ref_dir = Path(args.reference)
    if not ref_dir.exists():
        print("[metaStrain] ERROR: reference directory not found")
        sys.exit(1)

    code = Path(args.code)
    if not code.exists():
        print("[metaStrain] ERROR: code directory not found")
        sys.exit(1)

    out_dir = Path(args.output)
    out_dir.mkdir(parents=True, exist_ok=True)

    cmd = [
        "bash",
        str(script),
        str(species_file),
        str(ref_dir),
        str(code),
        str(out_dir)
    ]

    run_cmd(cmd)


# -----------------------------
# species selection 模块
# -----------------------------
def run_species(args):

    script = SCRIPTS_DIR / "species_selection.sh"

    if not script.exists():
        print(f"[metaStrain] ERROR: script not found: {script}")
        sys.exit(1)

    if not os.path.exists(args.kreport):
        print("[metaStrain] ERROR: Kraken report not found")
        sys.exit(1)

    if args.mode == "top":
        value = int(args.value)
    else:
        value = float(args.value)

    cmd = [
        "bash",
        str(script),
        args.kreport,
        args.output,
        args.mode,
        str(value)
    ]

    run_cmd(cmd)






# -----------------------------
# 主入口
# -----------------------------
def main():
    parser = argparse.ArgumentParser(
        prog="metastrain",
        description="metaStrain: strain identification algorithm"
    )

    subparsers = parser.add_subparsers(dest="command")

    # =========================
    # identify
    # =========================
    p_id = subparsers.add_parser("identify", help="strain identification")
    p_id.add_argument("-i", "--input", required=True, help="input metagenomic sequencing reads (FASTQ format)")
    p_id.add_argument("-o", "--output", required=True, help="output directory for all identification results")
    p_id.add_argument("--species", required=True, help="species composition file")
    p_id.add_argument("--code", required=True, help="path to the code file")
    p_id.add_argument("--patterns", required=True, help="directory containing the pre-built strain patterns")
    p_id.set_defaults(func=run_identify)

    # =========================
    # pattern
    # =========================
    p_pat = subparsers.add_parser("pattern", help="pattern construction")
    p_pat.add_argument("--species", required=True, help="species composition file")
    p_pat.add_argument("--reference", required=True, help="directory storing the genome references used for pattern construction")
    p_pat.add_argument("--code", required=True, help="path to the code file")
    p_pat.add_argument("-o", "--output", required=True, help="output directory for constructed patterns")
    p_pat.set_defaults(func=run_pattern)


    # =========================
    # reference
    # =========================
    p_ref = subparsers.add_parser("reference", help="reference download")
    p_ref.add_argument("--species", required=True, help="species composition file")
    p_ref.add_argument("--code", required=True, help="path to the code file")
    p_ref.add_argument("-o", "--output", required=True, help="output directory for downloaded reference genomes")
    p_ref.set_defaults(func=run_reference)


    # =========================
    # species selection
    # =========================
    p_sp = subparsers.add_parser("species", help="species selection from Kraken2 report")

    p_sp.add_argument("--kreport", required=True, help="Kraken2 report file")
    p_sp.add_argument("-o", "--output", required=True, help="output species selection file")
    p_sp.add_argument("--mode", required=True, choices=["top", "threshold"], help="selection mode: top N or relative abundance threshold")
    p_sp.add_argument("--value", required=True, help="TOP number or relative abundance threshold (%%)")

    p_sp.set_defaults(func=run_species)


    # =========================
    # run
    # =========================
    args = parser.parse_args()

    if not hasattr(args, "func"):
        parser.print_help()
        sys.exit(1)

    args.func(args)


# -----------------------------
# entry point
# -----------------------------
if __name__ == "__main__":
    main()
  
  
