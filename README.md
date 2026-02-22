# metaStrain
## Brief Description:
metaStrain is the program for determining the strain composition of microbial communities from metagenomic sequencing data.
## Environment:
metaStrain is an integrated C++ package that requires a basic **UNIX/Linux environment**. The GCC compiler is required to be installed prior (we have tested successfully on version 8.4.0 and version 11.4.0). More details can be found [here](https://gcc.gnu.org/). Currently, metaStrain does not support Mac or Windows systems. The computational tools required in this pipeline also include [Kraken2](https://github.com/DerrickWood/kraken2), [minimap2](https://github.com/lh3/minimap2), and [vsearch](https://github.com/torognes/vsearch). 
| Tool | Purpose-| Installation |
|------|---------|-------------|
| [Kraken2](https://github.com/DerrickWood/kraken2) | Species composition profiling | Required |
| [minimap2](https://github.com/lh3/minimap2) | Sequence alignment | Required |
| [vsearch](https://github.com/torognes/vsearch) | Microbiome sequence processing | Required |
# Usage: #
## 1. Download metaStrain
The source code of metaStrain is freely available at <https://github.com/wqlyt17/metaStrain.git>.  
To install the metaStrain, first, download the zip file manually from GitHub or use the code below in Unix:

```bash
cd /your_path/
git clone https://github.com/wqlyt17/metaStrain.git
```
## 2. Run metaStrain
First create a folder named "patterns" and a folder named "run":

```bash
cd metaStrain
mkdir patterns
mkdir run
```

### 2.1 Pattern construction

```bash
cd metaStrain
path="/your_path/metaStrain"
bash pattern_construction.sh species_pattern.txt ${path}/reference ${path}/code/patterns ${path}/patterns
```
**Note 1:** `species_pattern.txt` contains the names of the species for which patterns will be constructed. Each row corresponds to a single species, and spaces in species names should be replaced with underscores. For additional details, please refer to the example species_pattern.txt file provided in the metaStrain folder.

Example:
```text
Bacteroides_fragilis
```
**Note 2:** ${path}/reference is the directory storing the genome references used for pattern construction. For each species, two files are required: a CDS reference (`species_cds.fa`) and a genome reference (`species.fa`). A bash script is provided to download reference files for the specified species, with instructions included in the example section. Users can provide CDS and genome references for specified strains according to their needs to construct their own patterns.

**Note 3:** ${path}/code/patterns contains the code used to construct patterns. ${path}/patterns is the directory where the resulting patterns are stored. After constructing patterns, this directory contains the pattern files `UP.fa` and `Com.fa`, where `UP.fa` includes the constructed UGAs and `Com.fa` includes the constructed CGAs. All other files in ${path}/patterns are required for the quadratic programming model of metaStrain. The `UP.fa` and `Com.fa` files are provided in standard FASTA format, where each header corresponds to a single constructed pattern.

For example, 
```text
>NC_006347.1_1
TCAGTCGTTTTCTTTTTCCACATCATGCCTTTGAGTTATTAAGCGGTATTGTTCGTCACTTCGAAAGCGGATGGCGTTTTCGTACCAGACATCATTGGCGGCCTGATACGCTTGTACACCGTTTATACGGTCTTCATCTATCAGTCGGGCAATAATGGCGGAACCTCTATAGGCGGTATCCCAGAACAAAGCTAAATCACCGATCCTGGGAGTCTGCTCTATATGGTCCGTTTCCTGACAGAAGAAATCTGAAAGATTCTCCGGTTCAAATGTGATTATTAACCTATTGTCTACAGCCTCAACAGAAGCATGGCGACATTCGGGGGGAATACTAAAGTTTTGTATCTTCATTTAATAGGCGATTGAATCATAGAACTGCCGATTACGCAAATACTCCTTTACCACATCCGATGAAGTGGCACGATCACCGATACGATCATGGATGTACTGGTACTTCTCAAAACTCATACCTGAGAGGATATCATCATTCATCTCTACGTTGCCGGCATAGATGCAACCGGCAACCGTAACTATGCTTATGATGACCGTAAACAGATGCTTGGAAAGACTATTCATGTTCTTCAT
>NC_006347.1_2
ATGAAAGAGTTATTTAATACCAAAGTAACCGTAAGGCTTCGTAAAGTCGAAAACCGTAAGGAATGGTATGTTTATATCGAAAGCTATCCCGTATTTGTTCCCGGTAAGAAAGTCCCACAACGCATACGCGAATACCTGAACCGCAGTGTTACCACAGTGGAATGGGATAAGAAACGAGTCGCCCGCACCGAAGCAGACGGAACGAAAACCTATAAACCCAAGTGTGATGATAACGGAATCATTGTTTGCCGAAGTGAAAAAGACCAAGAAAGTATGTTATATGCCGACGGCGTTCGCAAATTACGACAACGCGAATACGATAACGTCGATTTGTATAGCGAAACGGAGACTGCCCAAGCAGAACAAAGAGAACGCTCACAGCAGAATTTCATTGAGTACTTTGATGTCGTATCGAAAAAACGTCATGCTAACAGTTCGGAATCTATTATTGTGAATTGGCGGCGGACACACGAATTACTAAAGATTTTTGCGGGTGAGTATCTGCCATTTTC
```

**Note 4:** This step requires the tools minimap2 and vsearch. minimap2 is a versatile pairwise aligner for genomic and spliced nucleotide sequences and can be installed from its GitHub repository (https://github.com/lh3/minimap2). A brief installation guide is provided below.
```bash
curl -L https://github.com/lh3/minimap2/releases/download/v2.30/minimap2-2.30_x64-linux.tar.bz2 | tar -jxvf -
./minimap2-2.30_x64-linux/minimap2
```
vsearch is a versatile open-source tool for microbiome analysis and can be installed from its GitHub repository (https://github.com/torognes/vsearch). A brief installation guide is provided below.
```bash
wget https://github.com/torognes/vsearch/archive/v2.30.4.tar.gz
tar xzf v2.30.4.tar.gz
cd vsearch-2.30.4
./autogen.sh
./configure CFLAGS="-O2" CXXFLAGS="-O2"
make ARFLAGS="cr"
sudo make install
```
### 2.2 Run Kraken2 to acquire the species composition of a given metagenomic sample
```bash
cd metaStrain
kraken2 --db /your_path/database ${path}/data/metagenome_filename --threads 20 --use-mpa-style --report ${path}/meta_sample.report --output ${path}/meta_sample.txt
```
**Note 1:** /your_path/database is the directory containing the Kraken2 database, and ${path}/metagenome_filename specifies the path to the input metagenomic sample (e.g., B1.fastq).

**Note 2:** Kraken2 can be installed from its GitHub repository (https://github.com/DerrickWood/kraken2). A brief installation guide is provided below.
```bash
git clone https://github.com/DerrickWood/kraken2.git
cd kraken2
./install_kraken2.sh /your_path/kraken
cd /your_path/kraken
kraken2-build --download-library bacteria --threads 24 --db /your_path/kraken/database
kraken2-build --download-taxonomy --db /your_path/kraken/database
kraken2-build --build --threads 24 --db /your_path/database
```
For detailed configuration instructions, please refer to the official [Kraken2 GitHub repository](https://github.com/DerrickWood/kraken2).
### 2.3 Strain identification of a given metagenomic sample
```bash
cd metaStrain
bash strain_identifiy.sh ${path}/code ${path}/meta_sample.report ${path}/data/metagenome_filename ${path}/patterns/ s ${path}/run  
```
**Note 1:** ${path}/code contains the codes used for strain identification. meta_sample.report is the output file generated by Kraken2. ${path}/data/metagenome_filename is the path to the input metagenomic sample (e.g., B1.fastq). ${path}/patterns/ is the directory where the constructed patterns are stored. s denotes the species with the top s abundance according to Kraken2 (e.g., 1 indicates identifying strains from a single species).

**Note 2:** ${path}/run is the directory for output files. `output_sort.txt` contains the strain identification results for the given metagenomic sample.
## 3.  Example ##
Download [reference file 1](https://drive.google.com/file/d/1VBtQBlaQMEW-XqOHXjid9IqZ-sNjdTPG/view?usp=drive_link) and [reference file 2](https://drive.google.com/file/d/1MY_e0H5ePxnBwlNpkj9eUI8nnAaF-oKG/view?usp=drive_link) to the reference folder, and download [metagenomic sample](https://drive.google.com/file/d/1e2zYPeqPWmPs9ZJPE9O8m-KuDvfXT1_z/view?usp=drive_link) to the data folder.
```bash
cd /your_path/
git clone https://github.com/wqlyt17/metaStrain.git
cd metaStrain
mkdir patterns
mkdir run
path="/your_path/metaStrain"
bash pattern_construction.sh species_pattern.txt ${path}/reference ${path}/code/patterns ${path}/patterns
bash strain_identifiy.sh ${path}/code ${path}/meta_sample.report ${path}/data/B1.fastq ${path}/patterns/ 1 ${path}/run 
```
**Note:** We also provide a script to download the two reference files mentioned above. The `species_pattern.txt` file contains the names of the species for which reference sequences should be downloaded from NCBI. Each row corresponds to a single species, and spaces in species names should be replaced with underscores.  /your_path_for_reference/ specifies the directory where the downloaded reference files will be stored.
  ```bash
bash download_reference.sh species_pattern.txt /your_path/metastrain/code  /your_path_for_reference/
```
# Contact #
Any questions, problems, or bugs are welcome and should be reported to [Bingqiang Liu]( bingqiang@sdu.edu.cn) or [Qi Wang](wangqi1994_sdu@163.com).

