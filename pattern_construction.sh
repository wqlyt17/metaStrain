#!/usr/bin/bash




filename=$1;#the species need to be constrcuted patterns
path_pattern=$4;# the storage path of patterns
path_1=$2;# the path of reference 
path_code=$3; #the path of code
u=75;#vclust path
c=10;# mapping coverage 
length=4; # length of patterns



for species in $(cat $filename)
do
	cd $path_1
	input_1="${species}_cds.fa";
	input_2="${species}_cds_1.fa";
	input_3="${species}.fa";
	
	grep '>lcl|NC_\|>lcl|NZ_' $input_1 | sed 's/>lcl|//g' | sed 's/_cds_/ /g' | sed 's/\[//g' | sed 's/\]//g' | sed 's/ /\t/g' | sed 's/=/\t/g' | sed 's/(/\t/g' | sed 's/)/\t/g' | sed 's/\.\./\t/g' | sed 's/<//g' | sed 's/>//g' | sed 's/,/\t/g' | sed 's/\t\t/\t/g' > $input_2
	
	
	cd $path_code
	g++ Solve_uclust_output_1.cc -o uclust_1
	g++ Solve_uclust_output_2.cc -o uclust_2
	g++ Solve_uclust_output_3.cc -o uclust_3
	g++ Minimal_Unique_Substrings_0221.cc -o minimal
	g++ Extract_centroid_sequence-1004.cc -o centroid
	g++ analysis_1.cc -o analysis_1
	g++ analysis_2.cc -o analysis_2
	g++ Extract_mus_reduced_0828.cc -o musadd
	g++ Extract_unique_pattern_0810.cc -o upadd

	
	#cd /fs/ess/PAS1475/wangqi/wangqi/VSEARCH/test-vsearch
	cd ${path_pattern}
	mkdir ${species}  #the path of up/cp sequences
	cd ./${species}
	
	
	
	#Clustering
	vsearch -cluster_fast $path_1/$input_1 -id 0.$u -uc output_75.uc
	#/fs/ess/PAS147usearch -cluster_fast $path_1/$input_1 -id 0.$u -uc output_75.uc
	sed 's/ /-/g' output_75.uc > output_75_copy.uc



	#Output all clusters along with their containing genes
	$path_code/uclust_1 output_75_copy.uc cluster_75.txt

	#Rename each gene sequence based on the cluster that they belong to
	$path_code/uclust_2 cluster_75.txt name_75.txt
	sed -i 's/>cluster_//g' name_75.txt

	grep '>' $path_1/$input_1 | awk '{print $1}' > gene_onlyname.fa
	sed -i 's/>//g' gene_onlyname.fa

	#Output gene arrangement of all genomes
	$path_code/uclust_3 name_75.txt $path_1/$input_2 gene_onlyname.fa genome_arrangement.txt

	#UGA [2] 求解极小特异子串+解决反向互补问题
	$path_code/minimal genome_arrangement.txt mus_noreverse.txt $length


	#UP [1] 提取代表每个cluster的centroid sequences
	cp $path_1/$input_1 gene_0.fa
	sed -i 's/>lcl/>\tlcl/g' gene_0.fa

	$path_code/centroid output_75.uc gene_0.fa centroid.txt

	#UP [2] 合成Unique patterns
	$path_code/upadd centroid.txt mus_noreverse.txt UP_noreverse.fa UP_location_noreverse.txt 0.$c


	#UP [3] 对Unique patterns进行筛选
	#Map patterns to reference genome
	minimap2 -ax asm5 $path_1/$input_3 UP_noreverse.fa > UP_reference.sam
	#Remove those patterns that are not exactly mapped to its corresponding one genome
	$path_code/analysis_1 UP_reference.sam analysis_out_1.txt

	sed 's/_/\t/2' analysis_out_1.txt > analysis_out_1_0.txt
	$path_code/analysis_2 analysis_out_1_0.txt analysis_out_2.txt

	sed -i -e 's/NC_/>NC_/g' -e 's/NZ_/>NZ_/g' analysis_out_2.txt 
	#Based on selected patterns, redesign unique patterns
	$path_code/musadd mus_noreverse.txt analysis_out_2.txt mus_reduced.txt 5

	$path_code/upadd centroid.txt mus_reduced.txt UP.fa UP_location.txt 0.$c
	
	#Common
	g++ /$path_code/Supplementary_method_0813.cc
	./a.out mus_reduced.txt genome_arrangement.txt matrix_B.txt matrix_A.txt pseudo_gene_arrangements.txt strain_num.txt 2 $species 10

	g++ $path_code/Extract_unique_pattern_supple.cc
	./a.out centroid.txt pseudo_gene_arrangements.txt Com.fa Com_location.txt
	
	##intraspecies filtering
	minimap2 -ax asm5 $path_1/$input_3 Com.fa > Com_reference.sam
	sed -i 's/_/\t/2' Com_reference.sam
	
	sed -e 's/>NC_/NC_/g' -e 's/>NZ_/NZ_/g' strain_num.txt > strain_num_new.txt
	g++ $path_code/interspecies_cga_check.cc
	./a.out strain_num_new.txt Com_reference.sam matrix_B.txt matrix_A.txt analysis_out.txt $species

	g++ $path_code/Extract_cga_reduced_0825.cc
	./a.out analysis_out.txt pseudo_gene_arrangements.txt pseudo_gene_arrangements_reduced.txt
	
	
	g++ /$path_code/Extract_unique_pattern_supple_0828.cc
	./a.out centroid.txt pseudo_gene_arrangements_reduced.txt Com.fa Com_location.txt 0.$c 
	
	rm a.out
	rm analysis_out.txt analysis_out_1.txt analysis_out_1_0.txt analysis_out_2.txt
	rm centroid.txt cluster_75.txt Com_reference.sam gene_0.fa gene_onlyname.fa genome_arrangement.txt
	rm mus_noreverse.txt name_75.txt output_75.uc output_75_copy.uc pseudo_gene_arrangements.txt strain_num_new.txt
	rm UP_location_noreverse.txt UP_noreverse.fa UP_reference.sam
	rm $path_1/$input_2
	rm pseudo_gene_arrangements_reduced.txt
		
done





