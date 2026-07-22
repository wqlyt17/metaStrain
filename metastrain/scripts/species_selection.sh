#!/bin/bash

kraken2=$1
output=$2
mode=$3
value=$4


tmp="meta_sample_species.txt"
relative="meta_sample_species_relative.txt"


# Extract species abundance
grep '|s__' ${kraken2} \
| sed 's/|s__/\ts__/g' \
| sed 's/ /_/g' \
| awk '{print $2,$3}' \
| sort -k2rn > ${tmp}


# Calculate relative abundance (%)
total=$(awk '{sum+=$2} END{print sum}' ${tmp})

awk -v total=${total} \
'{printf "%s\t%.6f\n",$1,$2/total*100}' \
${tmp} \
| sort -k2rn > ${relative}



# Select species
if [ "$mode" == "top" ]; then

    # TOP N relative abundance species
    head -n ${value} ${relative} \
    | cut -f1 \
    | sed 's/s__//g' > ${output}


elif [ "$mode" == "threshold" ]; then

    # Relative abundance >= threshold (%)
    awk -v t=${value} '$2>=t {print $1}' ${relative} \
    | sed 's/s__//g' > ${output}

else

    echo "Usage:"
    echo "$0 kraken2.report top N"
    echo "$0 kraken2.report threshold abundance(%)"
    exit 1

fi

rm ${tmp}
rm ${relative}