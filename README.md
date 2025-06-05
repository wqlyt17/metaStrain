# metaStrain #
## Brief Description: ##
The metaStrain is the program for determining the strain composition of microbial communities from metagenomic sequencing data.
## Environment: ##
metaStrain is an integrated C++ package that requires a basic **UNIX/Linux environment**. The gcc compiler with **version 8.4.0** is required to be installed prior. More details can be found [here](https://gcc.gnu.org/). Currently, metaStrain does not support Mac or Windows systems. The computational tools required in this pipeline also include [Kraken2](https://github.com/DerrickWood/kraken2), [minimap2](https://github.com/lh3/minimap2), and [vsearch](https://github.com/torognes/vsearch). 
# Usage: #
## 1. Download metaStrain ##
The source code of metaStrain is freely available at <https://github.com/wqlyt17/metaStrain.git>.  
To install the metaStrain, first, download the zip file manually from GitHub or use the code below in Unix:

```bash
cd /your_path/
git clone https://github.com/wqlyt17/metaStrain.git
```



## 2. Run metaStrain ##
First create a folder named patterns and a folder named run:

```bash
cd metaStrain
mkdir patterns
mkdir run
```

1. Pattern database construction

```bash
cd metaStrain
path="/your_path/metaStrain"
bash pattern_construction.sh species_pattern.txt ${path}/reference ${path}/code/patterns ${path}/patterns
```

**Note 1:** species_pattern.txt records the name of the species for which the pattern needs to be built. One species in a row, and spaces in species names are replaced with underscores. More details can be found in the given species_pattern.txt in the metaStrain-master folder.
**Note 2:** ${path}/reference is the path that stores the species genome references used for pattern construction. Each species contains two files, including a CDS reference (species_cds.fa) and a genome reference (species.fa). More details can be found in the given reference folder in the metaStrain-master folder.
**Note 3:** ${path}/code/patterns stores the codes that are used to construct patterns; ${path}/patterns is the path for storing the constructed patterns.


2. Run Kraken2 to acquire the species composition of a given metagenomic sample

```bash
cd metaStrain
kraken2 --db /your_path/database ${path}/data/metagenome_filename --threads 20 --use-mpa-style --report ${path}/meta_sample.report --output ${path}/meta_sample.txt
```

**Note:** /your_path/database is the path of the database constructed by Kraken2. ${path}/metagenome_filename is the path of the given metagenomic sample (for example, we used B1.fastq).

3. Strain identification of a given metagenomic sample

```bash
cd metaStrain
bash strain_identifiy.sh ${path}/code ${path}/meta_sample.report ${path}/data/metagenome_filename ${path}/patterns/ s ${path}/run  
```

**Note 1:** ${path}/code stores the codes that are used to identify strains. meta_sample.report is the output file from Kraken2. ${path}/data/metagenome_filename is the path of the given metagenomic sample (for example, we used B1.fastq). ${path}/patterns/ is the path for storing the constructed patterns. s is the species with the top s abundance from Kraken2 (for example, we used 1).
**Note 2:** ${path}/run is the path of the output files. output_sort.txt stores the strain identification result of the given metagenomic sample.

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
# Contact #
Any questions, problems, or bugs are welcome and should be reported to [Bingqiang Liu]( bingqiang@sdu.edu.cn) or [Qi Wang](wangqi1994_sdu@163.com).

