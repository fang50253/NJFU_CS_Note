#!/usr/bin/env python3
"""
Step 1: Extract WRKY gene chromosomal coordinates from NCBI GFF annotation.
Maps each WRKY XP_ protein ID to chromosome, start, end, strand, and gene location tag.
"""

import re
import os
import sys

# Paths
BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INPUT_DIR = os.path.join(BASE, 'input')
OUTPUT_DIR = os.path.join(BASE, 'output')
PROJECT_DIR = r'D:\Documents\Github\CladeCheck\task3'

WRKY_IDS_FILE = os.path.join(PROJECT_DIR, 'final_WRKY_ids.txt')
GFF_FILE = r'D:\Documents\Github\CladeCheck\task3\ncbi_populus_extracted\ncbi_dataset_Populus_trichocarpa\ncbi_dataset\data\GCF_000002775.5\genomic.gff'

os.makedirs(INPUT_DIR, exist_ok=True)
os.makedirs(OUTPUT_DIR, exist_ok=True)

def load_wrky_ids():
    """Load all WRKY gene IDs."""
    ids = set()
    with open(WRKY_IDS_FILE) as f:
        for line in f:
            line = line.strip()
            if line:
                ids.add(line)
    print(f"Loaded {len(ids)} WRKY IDs")
    return ids

def parse_gff_for_wrky(wrky_ids, gff_path):
    """
    Parse GFF file to find chromosomal locations for each WRKY gene.
    NCBI GFF has CDS entries with protein_id=XP_... format.
    """
    wrky_locations = {}  # XP_ID -> {chrom, start, end, strand, gene_id, description}
    
    # First, find the parent gene for each WRKY CDS
    cds_to_gene = {}  # XP_ID -> (chrom, gene_start, gene_end, strand, gene_id)
    
    # Buffer lines for efficiency
    cds_pattern = re.compile(r'protein_id=([^;]+)')
    gene_pattern = re.compile(r'ID=gene-([^;]+)')
    wrky_pattern = re.compile(r'WRKY', re.IGNORECASE)
    
    gene_info = {}  # gene_id -> (chrom, start, end, strand)
    
    print("Scanning GFF for WRKY genes (this may take a moment)...")
    
    with open(gff_path, 'r', encoding='utf-8') as f:
        for line in f:
            if line.startswith('#'):
                continue
            parts = line.strip().split('\t')
            if len(parts) < 9:
                continue
            
            chrom = parts[0]
            feature_type = parts[2]
            start = int(parts[3])
            end = int(parts[4])
            strand = parts[6]
            attributes = parts[8]
            
            # Collect all gene boundaries (for protein-coding genes)
            if feature_type == 'gene':
                if 'gene_biotype=protein_coding' in attributes:
                    m = gene_pattern.search(attributes)
                    if m:
                        gene_id = m.group(1)
                        gene_info[gene_id] = (chrom, start, end, strand)
            
            # Find CDS entries with WRKY XP_ IDs
            elif feature_type == 'CDS':
                if 'protein_id=XP_' in attributes:
                    m = cds_pattern.search(attributes)
                    if m:
                        prot_id = m.group(1)
                        if prot_id in wrky_ids:
                            # Check if WRKY keyword in product
                            is_wrky = bool(wrky_pattern.search(attributes))
                            if is_wrky:
                                if prot_id not in wrky_locations:
                                    wrky_locations[prot_id] = {
                                        'chrom': chrom,
                                        'cds_start': start,
                                        'cds_end': end,
                                        'strand': strand,
                                        'full_attr': attributes
                                    }
                                else:
                                    # Extend CDS range
                                    loc = wrky_locations[prot_id]
                                    loc['cds_start'] = min(loc['cds_start'], start)
                                    loc['cds_end'] = max(loc['cds_end'], end)
    
    # Now map to gene-level coordinates
    result = {}
    for prot_id, loc in wrky_locations.items():
        # Extract gene ID from CDS attribute
        attr = loc['full_attr']
        gene_match = re.search(r'gene=([^;]+)', attr)
        if gene_match:
            gene_id = gene_match.group(1)
            if gene_id in gene_info:
                chrom, gstart, gend, gstrand = gene_info[gene_id]
                result[prot_id] = {
                    'chrom': chrom,
                    'gene_start': gstart,
                    'gene_end': gend,
                    'strand': gstrand,
                    'gene_id': gene_id,
                    'midpoint': (gstart + gend) // 2
                }
            else:
                # Fall back to CDS coordinates
                result[prot_id] = {
                    'chrom': loc['chrom'],
                    'gene_start': loc['cds_start'],
                    'gene_end': loc['cds_end'],
                    'strand': loc['strand'],
                    'gene_id': gene_id if 'gene_match' in dir() else 'unknown',
                    'midpoint': (loc['cds_start'] + loc['cds_end']) // 2
                }
                print(f"  Warning: No gene entry found for {prot_id} (gene={gene_id})")
    
    return result

def write_output(wrky_locations, output_dir):
    """Write WRKY gene coordinates to files."""
    # Write detailed table
    coords_file = os.path.join(output_dir, 'WRKY_chromosome_coordinates.tsv')
    with open(coords_file, 'w') as f:
        f.write("Protein_ID\tChromosome\tGene_Start\tGene_End\tStrand\tGene_ID\tMidpoint\n")
        for prot_id in sorted(wrky_locations.keys()):
            loc = wrky_locations[prot_id]
            f.write(f"{prot_id}\t{loc['chrom']}\t{loc['gene_start']}\t{loc['gene_end']}\t"
                   f"{loc['strand']}\t{loc['gene_id']}\t{loc['midpoint']}\n")
    print(f"Written: {coords_file}")
    
    # Write GFF format for MCScanX-like tools
    gff_out = os.path.join(output_dir, 'WRKY_genes.gff')
    with open(gff_out, 'w') as f:
        f.write("##gff-version 3\n")
        for prot_id in sorted(wrky_locations.keys()):
            loc = wrky_locations[prot_id]
            f.write(f"{loc['chrom']}\tWRKY_analysis\tgene\t{loc['gene_start']}\t{loc['gene_end']}\t"
                   f".\t{loc['strand']}\t.\tID={prot_id};Name={loc['gene_id']}\n")
    print(f"Written: {gff_out}")
    
    # Write BED format
    bed_out = os.path.join(output_dir, 'WRKY_genes.bed')
    with open(bed_out, 'w') as f:
        for prot_id in sorted(wrky_locations.keys()):
            loc = wrky_locations[prot_id]
            f.write(f"{loc['chrom']}\t{loc['gene_start']-1}\t{loc['gene_end']}\t{prot_id}\t.\t{loc['strand']}\n")
    print(f"Written: {bed_out}")
    
    # Write chromosome distribution summary
    chrom_counts = {}
    for prot_id, loc in wrky_locations.items():
        chrom = loc['chrom']
        chrom_counts[chrom] = chrom_counts.get(chrom, 0) + 1
    
    dist_file = os.path.join(output_dir, 'WRKY_chromosome_distribution.tsv')
    with open(dist_file, 'w') as f:
        f.write("Chromosome\tWRKY_Count\n")
        for chrom in sorted(chrom_counts.keys()):
            f.write(f"{chrom}\t{chrom_counts[chrom]}\n")
    print(f"Written: {dist_file}")
    
    return coords_file

def main():
    wrky_ids = load_wrky_ids()
    wrky_locations = parse_gff_for_wrky(wrky_ids, GFF_FILE)
    
    print(f"\nFound {len(wrky_locations)} WRKY genes with chromosomal locations")
    
    # Check for missing IDs
    found_ids = set(wrky_locations.keys())
    missing = wrky_ids - found_ids
    if missing:
        print(f"\nWarning: {len(missing)} WRKY IDs not found in GFF:")
        for m in sorted(missing):
            print(f"  {m}")
    
    write_output(wrky_locations, OUTPUT_DIR)
    print("\nStep 1 complete!")

if __name__ == '__main__':
    main()
