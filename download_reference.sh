#!/bin/bash

path=$3; #/you_path/metaStrain/reference
path1=$2;#/you_path/metaStrain/code


for species in $(cat $1)
do
	cd ${path}
	filename="assembly_summary_${species}.txt" ##yes remove
	filename_ftp="assembly_summary_${species}_ftp.txt" ##yes remove
	filename_cds="${species}_cds_1.fa" ##yes remove
	filename_genome="${species}_1.fa" ##yes remove
	filename_nc="${species}_NC.txt" ##yes remove
	filename_nc_all="${species}_NC_all.txt"  ##yes remove
	filename_nc_genome="${species}.fa"  ## yes
	filename_nc_cds="${species}_cds.fa"  #==Streptococcus-pneumoniae_14_gene.fa
	directory="${species}_reference" ##yes
	
	mkdir -p "$directory"
	wget -O $filename "https://ftp.ncbi.nlm.nih.gov/genomes/refseq/bacteria/${species}/assembly_summary.txt"
	
	${path1}/assembly_select $filename $filename_ftp

    if [ -s $filename_ftp ] ## add 0814-check whether ftp file is empty 
    then
    	cd ${path}
    	for url in $(cat $filename_ftp)
    	do
    		genomeurl="${url}_genomic.fna.gz"  
    		wget -c -P ${path}/$directory/ $genomeurl
    	done
	
    	cd ${path}/$directory/
    	gzip -d *.gz
    	cat *.fna > $filename_genome;
    	rm *.fna
	
	    #NC genome sequences
    	grep -E ">NC_|>NZ_" $filename_genome | grep -v "plasmid" > $filename_nc_all    #add remove plasmid complets genomes
    	
    	${path1}/extract_genome $filename_nc_all $filename_genome $filename_nc_genome
	
    	##extract NC num not plasmid
    	sed 's/ /\t/g' $filename_nc_all | awk '{print $1}' | sed 's/>//g' > $filename_nc
	
	  
    	cd ${path}/
    	for url in $(cat $filename_ftp)
    	do
    		ftpurl="${url}_cds_from_genomic.fna.gz"
    		wget -c -P ${path}/$directory/ $ftpurl
    	done
	
        rm $filename $filename_ftp
	
    	cd ${path}/$directory/
    	gzip -d *.gz
    	cat *.fna > $filename_cds;
    	rm *.fna
         
        sed -i -e 's/lcl|/lcl\t/g' -e 's/_/\t/2' $filename_cds
    	
    	${path1}/extract_cds $filename_nc $filename_cds $filename_nc_cds
    	sed -i -e 's/lcl\t/lcl|/g' -e 's/\t/_/g' $filename_nc_cds

    	rm $filename_genome $filename_cds
    	rm $filename_nc_all
	
		rm ${filename_nc}  
    else
        echo "RefSeq have no genomes for the $species"  ##0813 add
    fi
done
