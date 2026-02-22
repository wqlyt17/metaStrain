#!/usr/bin/bash



filename_kraken=$2;#meta_sample.report
pattern_path=$4;#/pattern_path/
threshold=$5;#species with top abundance
path_1=$6;#running path
path_code=$1;#code path
metagenome_filename=$3;  #/fs/ess/PCON0022/zhaoqianliu/wangqi/WQ/metaStrain/data/B1.fastq

cd $path_code
g++ Extract_mapping_location.cc -o map_location
g++ Identification_simple_design_0213.cc -o iden
g++ Identification_statistic.cc -o statistic
g++ Identification_abundance_1_nomulti.cc -o abundance_nomulti
g++ Identification_abundance_2_new.cc -o abundance_2
g++ Statistics_0301.cc -o statis_0301


cd $path_1/
mkdir file

path_2=$path_1/file
cd $path_1/file/
mkdir UP
mkdir Common



cd $path_1/
#0 select species from kraken output file
grep '|s__' ${filename_kraken} | sed 's/|s__/\ts__/g' | sed 's/ /_/g' | awk '{print $2,$3}' | sort -k 2rn > meta_sample_species.txt
sed -i 's/s__//g' meta_sample_species.txt
g++ $path_code/species_path.cc
./a.out meta_sample_species.txt $pattern_path $threshold kraken2_species.txt
#./a.out ${filename_kraken} $pattern_path $threshold kraken2_species.txt
##0 end


filename="kraken2_species.txt";#the path of patterns
length=4;
u=75;
c=10;

#cat UP.fa; UP_location.txt; mus_reduced.txt
cd $path_1/
: > UP.fa
: > UP_location.txt
: > mus_reduced.txt
: > Com.fa
: > Com_location.txt
: > matrix_B.txt
: > matrix_A.txt
: > strain_num.txt

for url in $(cat $filename)
do
	cat $url/UP.fa >> UP.fa
	cat $url/UP_location.txt >> UP_location.txt
	cat $url/mus_reduced.txt >> mus_reduced.txt
	cat $url/Com.fa >> Com.fa
	cat $url/Com_location.txt >> Com_location.txt
	cat $url/matrix_B.txt >> matrix_B.txt
	cat $url/matrix_A.txt >> matrix_A.txt
	cat $url/strain_num.txt >> strain_num.txt
done
		
sed -i -e 's/>NC_/>\tNC_/g' -e 's/>NZ_/>\tNZ_/g' UP_location.txt
sed -i -e 's/>NC_/>\tNC_/g' -e 's/>NZ_/>\tNZ_/g' Com_location.txt
sed -i -e 's/>NC_/NC_/g' -e 's/>NZ_/NZ_/g' strain_num.txt


## UP alignment
cd $path_2/UP/
minimap2 -ax map-pb $path_1/UP.fa $metagenome_filename > reduced.sam

$path_code/map_location reduced.sam Location_reduced.txt
$path_code/iden $path_1/UP_location.txt Location_reduced.txt Identificaiton.txt

#sed 's/_/\t/3' Identificaiton.txt > Identificaiton_0.txt
sed 's/\(.*\)_/\1\t/' Identificaiton.txt > Identificaiton_0.txt


$path_code/statistic Identificaiton_0.txt output_read.txt output_genome.txt output_genome_nomulti.txt
awk '$2 == "b" || $2 == "c"' output_read.txt > output_read_multi.txt

$path_code/abundance_nomulti output_read_multi.txt Identificaiton.txt output_pattern_nomulti.txt
sed 's/_/\t/2' output_pattern_nomulti.txt > output_pattern_nomulti_0.txt

$path_code/abundance_2 output_pattern_nomulti_0.txt output_abundance_nomulti.txt output_pattern_read.txt

sed -i -e 's/>NC_/NC_/g' -e 's/>NZ_/NZ_/g' $path_1/mus_reduced.txt
$path_code/statis_0301 $path_1/mus_reduced.txt $path_1/mus_reduced.txt output_genome_nomulti.txt output_pattern_read.txt output_abundance_nomulti.txt statistics.txt
sort -n -k 7 -r statistics.txt > statistics_sort.txt


## Common alignment
cd $path_2/Common/
minimap2 -ax map-pb $path_1/Com.fa $metagenome_filename > reduced.sam
$path_code/map_location reduced.sam Location_reduced.txt
$path_code/iden $path_1/Com_location.txt Location_reduced.txt Identificaiton.txt

#sed 's/_/\t/3' Identificaiton.txt > Identificaiton_0.txt
sed 's/\(.*\)_/\1\t/' Identificaiton.txt > Identificaiton_0.txt

$path_code/statistic Identificaiton_0.txt output_read.txt output_genome.txt output_genome_nomulti.txt
awk '$2 == "b" || $2 == "c"' output_read.txt > output_read_multi.txt
$path_code/abundance_nomulti output_read_multi.txt Identificaiton.txt output_pattern_nomulti.txt
sed -i 's/_/\t/2' output_pattern_nomulti.txt


cd $path_2/
g++ $path_code/Constants_obtained_2.cc
./a.out $path_1/strain_num.txt ./UP/statistics_sort.txt $path_1/matrix_B.txt ./Common/output_pattern_nomulti.txt $path_1/matrix_A.txt Constant_UP_abundance.txt Constant_pseudo_reads.txt Constant_ce.txt Constant_CE.txt Constant_G.txt Constant_CI.txt

cd $path_code/convex-quadratic-programming/
g++ Strain_mathfind.cc Array.cc QuadProg++.cc -o SolveQuadProg
./SolveQuadProg $path_2/Constant_G.txt $path_2/Constant_CE.txt $path_2/Constant_ce.txt $path_2/Constant_CI.txt $path_2/QuadProg_output.txt

#rm $path_2/Constant_G.txt $path_2/Constant_CE.txt $path_2/Constant_ce.txt $path_2/Constant_CI.txt 
#rm $path_2/Constant_UP_abundance.txt $path_2/Constant_pseudo_reads.txt


cd $path_2/
g++ $path_code/evaluation_1.cc
./a.out ./UP/statistics_sort.txt $path_1/strain_num.txt QuadProg_output.txt output_evaluation.txt
sort -n -k 2 -r output_evaluation.txt > output_evaluation_sort.txt

cp $path_2/output_evaluation_sort.txt $path_1/output_sort.txt
rm -rf $path_2
#rm a.out
#rm output_evaluation.txt
#rm QuadProg_output.txt
#rm -rf $path_2/UP/
#rm -rf $path_2/Common/

rm $path_1/UP.fa
rm $path_1/UP_location.txt
rm $path_1/mus_reduced.txt
rm $path_1/Com.fa
rm $path_1/Com_location.txt
rm $path_1/matrix_B.txt
rm $path_1/matrix_A.txt
rm $path_1/strain_num.txt
rm $path_1/a.out
rm $path_1/kraken2_species.txt
rm $path_1/meta_sample_species.txt


