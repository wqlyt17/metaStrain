# metaStrain
## Brief description:
metaStrain is a method for determining the strain composition of microbial communities based on metagenomic sequencing data.

![外链图片转存失败,源站可能有防盗链机制,建议将图片保存下来直接上传](https://img-home.csdnimg.cn/images/20230724024159.png?origin_url=figure%2FFigure1.jpg&pos_id=img-5RHQmuOy-1784454046842)
## Environment:
metaStrain is an integrated C++ package with a command-line interface and requires a **UNIX/Linux environment**. The GCC compiler is required for compiling the C++ source code, and metaStrain has been successfully tested with GCC versions 8.4.0 and 11.4.0. Please ensure that GCC is available in your system environment before installation.

The required computational tools for the metaStrain pipeline, including [Kraken2](https://github.com/DerrickWood/kraken2), [minimap2](https://github.com/lh3/minimap2), and [vsearch](https://github.com/torognes/vsearch), are automatically installed through the provided Conda environment configuration.

Currently, metaStrain has only been tested on Linux systems and does not support macOS or Windows systems.

| Tool | Purpose | Version |
|------|---------|---------|
| [Kraken2](https://github.com/DerrickWood/kraken2) | Taxonomic classification of metagenomic reads | 2.17.1 |
| [minimap2](https://github.com/lh3/minimap2) | Long-read and genome sequence alignment | 2.30 |
| [vsearch](https://github.com/torognes/vsearch) | Sequence clustering and processing | 2.30.4 |
## Usage: 
### 1. Installation
The source code of metaStrain is freely available at <https://github.com/wqlyt17/metaStrain.git>. You can either download the source code as a ZIP archive from the GitHub repository or clone it using Git. We recommend installing metaStrain using the provided Conda environment to ensure that all dependencies are installed correctly.

```bash
cd /your_path/
git clone https://github.com/wqlyt17/metaStrain.git
cd metaStrain
conda env create -f environment.yml
conda activate metastrain
pip install .
```
After installation, you can verify that metaStrain has been installed successfully by running:
```bash
metastrain -h
```
If the installation is successful, the command-line help message will be displayed.
### 2. Quick start (Example) 
You can run the commands below to perform single-species strain identification. Since the species is already known in this example, Kraken2 is not required and strain identification can be performed directly. More detailed instructions on software installation and the complete pipeline are provided in the Detailed pipeline of metaStrain section below.

Download [reference file 1](https://drive.google.com/file/d/1VBtQBlaQMEW-XqOHXjid9IqZ-sNjdTPG/view?usp=drive_link) and [reference file 2](https://drive.google.com/file/d/1MY_e0H5ePxnBwlNpkj9eUI8nnAaF-oKG/view?usp=drive_link) to the reference folder (metaStrain/reference), and download [metagenomic sample](https://drive.google.com/file/d/1e2zYPeqPWmPs9ZJPE9O8m-KuDvfXT1_z/view?usp=drive_link) to the data folder (metaStrain/data).
```bash
cd metaStrain
mkdir patterns
mkdir run
path="/your_path/metaStrain"

metastrain pattern --species ${path}/species_pattern.txt --reference ${path}/reference --code ${path}/code -o ${path}/patterns

metastrain identify --code ${path}/code --species ${path}/species_pattern.txt -i ${path}/data/B1.fastq --patterns ${path}/patterns/ -o ${path}/run 
```

### 3. Detailed pipeline of metaStrain
First create a folder named "patterns" and a folder named "run":

```bash
cd metaStrain
mkdir patterns
mkdir run
```
#### 3.1 Pattern construction
Download [reference file 1](https://drive.google.com/file/d/1VBtQBlaQMEW-XqOHXjid9IqZ-sNjdTPG/view?usp=drive_link) and [reference file 2](https://drive.google.com/file/d/1MY_e0H5ePxnBwlNpkj9eUI8nnAaF-oKG/view?usp=drive_link) to the reference folder, and download [metagenomic sample](https://drive.google.com/file/d/1e2zYPeqPWmPs9ZJPE9O8m-KuDvfXT1_z/view?usp=drive_link) to the data folder.

**Constructing patterns**:
```bash
cd metaStrain
path="/your_path/metaStrain"
metastrain pattern --species ${path}/species_pattern.txt --reference ${path}/reference --code ${path}/code -o ${path}/patterns
```

You can view all available options by running:
```bash
metastrain pattern -h
```
| Option | Description |
|--------|-------------|
| `--species` | Species composition file containing the target species for pattern construction |
| `--reference` | Directory storing the genome references used for pattern construction|
| `--code` | Directory containing the source code required for pattern construction|
| `-o` | Output directory for the constructed strain patterns. |

**Note 1:** `species_pattern.txt` contains the names of the species for which patterns will be constructed. Each row corresponds to a species, and spaces in species names should be replaced by underscores. For additional details, please refer to the example species_pattern.txt file provided in the metaStrain folder.

`species_pattern.txt` contains the names of the target species for pattern construction. Each row corresponds to one species, and spaces in species names should be replaced by underscores. When the target species are known, users can directly prepare this file for pattern construction. For metagenomic samples without prior species information, users can first perform species profiling using Kraken2 and generate `species_pattern.txt` through the codes described in the 3.2 section. An example `species_pattern.txt` file is provided in the metaStrain folder.


Example:
```text
Bacteroides_fragilis
```
**Note 2:** ${path}/reference is the directory storing the genome references used for pattern construction. For each species, two files are required: a CDS reference (`species_cds.fa`) and a genome reference (`species.fa`). Users can provide CDS and genome references for specified strains according to their needs to construct their own patterns. The `reference` module of metaStrain provides an automated way to download the required genome and CDS reference files for the specified species from NCBI, as shown below.
  ```bash
metastrain reference --species species_pattern.txt --code ${path}/code -o ${path}/reference
```

**Note 3:** ${path}/code contains the code used to construct patterns. ${path}/patterns is the directory where the resulting patterns are stored. After constructing patterns, this directory contains the pattern files `UP.fa` and `Com.fa`, where `UP.fa` includes the constructed UGAs and `Com.fa` includes the constructed CGAs. All other files in ${path}/patterns are required for the quadratic programming model of metaStrain. The `UP.fa` and `Com.fa` files are provided in standard FASTA format, where each header corresponds to a single constructed pattern.

For example, 
```text
>NC_006347.1_1
TCAGTCGTTTTCTTTTTCCACATCATGCCTTTGAGTTATTAAGCGGTATTGTTCGTCACTTCGAAAGCGGATGGCGTTTTCGTACCAGACATCATTGGCGGCCTGATACGCTTGTACACCGTTTATACGGTCTTCATCTATCAGTCGGGCAATAATGGCGGAACCTCTATAGGCGGTATCCCAGAACAAAGCTAAATCACCGATCCTGGGAGTCTGCTCTATATGGTCCGTTTCCTGACAGAAGAAATCTGAAAGATTCTCCGGTTCAAATGTGATTATTAACCTATTGTCTACAGCCTCAACAGAAGCATGGCGACATTCGGGGGGAATACTAAAGTTTTGTATCTTCATTTAATAGGCGATTGAATCATAGAACTGCCGATTACGCAAATACTCCTTTACCACATCCGATGAAGTGGCACGATCACCGATACGATCATGGATGTACTGGTACTTCTCAAAACTCATACCTGAGAGGATATCATCATTCATCTCTACGTTGCCGGCATAGATGCAACCGGCAACCGTAACTATGCTTATGATGACCGTAAACAGATGCTTGGAAAGACTATTCATGTTCTTCAT
>NC_006347.1_2
ATGAAAGAGTTATTTAATACCAAAGTAACCGTAAGGCTTCGTAAAGTCGAAAACCGTAAGGAATGGTATGTTTATATCGAAAGCTATCCCGTATTTGTTCCCGGTAAGAAAGTCCCACAACGCATACGCGAATACCTGAACCGCAGTGTTACCACAGTGGAATGGGATAAGAAACGAGTCGCCCGCACCGAAGCAGACGGAACGAAAACCTATAAACCCAAGTGTGATGATAACGGAATCATTGTTTGCCGAAGTGAAAAAGACCAAGAAAGTATGTTATATGCCGACGGCGTTCGCAAATTACGACAACGCGAATACGATAACGTCGATTTGTATAGCGAAACGGAGACTGCCCAAGCAGAACAAAGAGAACGCTCACAGCAGAATTTCATTGAGTACTTTGATGTCGTATCGAAAAAACGTCATGCTAACAGTTCGGAATCTATTATTGTGAATTGGCGGCGGACACACGAATTACTAAAGATTTTTGCGGGTGAGTATCTGCCATTTTC
```
#### 3.2 Run Kraken2 to acquire the species composition of a given metagenomic sample

Constructing Kraken2 database:
```bash
cd metaStrain
kraken2-build --download-taxonomy --db /your_path/kraken/database
kraken2-build --download-library bacteria --threads 24 --db /your_path/kraken/database
kraken2-build --build --threads 24 --db /your_path/kraken/database
```
Running Kraken2 and obtaining the species composition:
```bash
path="/your_path/metaStrain"
kraken2 --db /your_path/kraken/database ${path}/data/B1.fastq --threads 20 --use-mpa-style --report ${path}/meta_sample.report --output ${path}/meta_sample.txt

metastrain species --kreport meta_sample.report --mode top --value 1 -o species_pattern.txt
```

**Note 1:** For detailed configuration instructions for constructing Kraken2 databse, please refer to the official [Kraken2 GitHub repository](https://github.com/DerrickWood/kraken2).

**Note 2:** /your_path/kraken/database specifies the directory containing the Kraken2 database, while ${path}/data/B1.fastq specifies the path to the input metagenomic sample (here, B1.fastq is used as an example).

**Note 3:** If strain identification is required only for a specific species, this step can be skipped. Simply replace Bacteroides fragilis with the target species name in the species_pattern.txt file.

**Note 4:** Two species selection modes are supported. `top` selects the top N species according to relative abundance (e.g., `--mode top --value 1` selects the most abundant species), while `threshold` selects all species with relative abundance above the specified cutoff (e.g., `--mode threshold --value 0.1` selects species with relative abundance ≥ 0.1%).
#### 3.3 Strain identification of a given metagenomic sample
```bash
cd metaStrain
metastrain identify --code ${path}/code --species ${path}/species_pattern.txt -i ${path}/data/B1.fastq --patterns ${path}/patterns/ -o ${path}/run  
```
You can view all available options by running:
```bash
metastrain identify -h
```
| Option | Required | Description |
|--------|:--------:|-------------|
| `-i`| Yes | Input metagenomic sequencing reads in FASTQ format. |
| `-o`| Yes | Output directory for all strain identification results. |
| `--species` | Yes | Species composition file containing the target species for strain identification. |
| `--code` | Yes | Directory containing the source code required for strain identification. |
| `--patterns` | Yes | Directory containing the pre-built strain patterns. |

**Note 1:** ${path}/code contains the codes used for strain identification. ${path}/species_pattern.txt contains the names of the target species, which can be either specified by users or identified from the metagenomic sample using Kraken2. ${path}/data/metagenome_filename is the input metagenomic sample (e.g., B1.fastq). ${path}/patterns/ is the directory where the constructed patterns are stored.

**Note 2:** ${path}/run is the directory for output files. `output_sort.txt` contains the strain identification results for the given metagenomic sample. The first column lists the strain genome names, and the second column reports the corresponding abundance of each strain genome.
## Contact 
Any questions, problems, or bugs are welcome and should be reported to [Bingqiang Liu](bingqiang@sdu.edu.cn) or [Qi Wang](wangqi1994_sdu@163.com).

