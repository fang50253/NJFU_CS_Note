#!/usr/bin/env python3
"""
Step 2: Classify WRKY gene duplication events using:
  - Chromosomal proximity for tandem duplications (within 200kb, same chromosome)
  - Self-BLAST results for paralog detection
  - Segmental duplication identification via multi-gene collinear blocks
"""

import os
import re
import sys
from collections import defaultdict, OrderedDict

# Paths
BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUTPUT_DIR = os.path.join(BASE, 'output')
PROJECT_DIR = r'D:\Documents\Github\CladeCheck\task3'

BLAST_FILE = os.path.join(PROJECT_DIR, 'WRKY_self_blast.txt')
COORDS_FILE = os.path.join(OUTPUT_DIR, 'WRKY_chromosome_coordinates.tsv')
KAKS_FILE = os.path.join(PROJECT_DIR, 'kaks_results.csv')

TANDEM_DISTANCE = 200000  # 200 kb for tandem duplication

os.makedirs(OUTPUT_DIR, exist_ok=True)

def load_coordinates():
    """Load WRKY gene coordinates."""
    coords = {}
    with open(COORDS_FILE) as f:
        header = f.readline().strip().split('\t')
        for line in f:
            parts = line.strip().split('\t')
            if len(parts) >= 7:
                prot_id = parts[0]
                coords[prot_id] = {
                    'chrom': parts[1],
                    'start': int(parts[2]),
                    'end': int(parts[3]),
                    'strand': parts[4],
                    'gene_id': parts[5],
                    'midpoint': int(parts[6])
                }
    print(f"Loaded coordinates for {len(coords)} WRKY genes")
    return coords

def load_blast_results():
    """Parse WRKY self-BLAST results (format: standard BLAST tabular)."""
    # Format: query, subject, identity, align_len, mismatches, gaps, q_start, q_end, s_start, s_end, evalue, bitscore
    pairs = []
    with open(BLAST_FILE) as f:
        for line in f:
            parts = line.strip().split('\t')
            if len(parts) >= 12:
                qry = parts[0]
                sbj = parts[1]
                pident = float(parts[2])
                alen = int(parts[3])
                evalue = float(parts[10])
                bitscore = float(parts[11])
                
                # Skip self-hits
                if qry == sbj:
                    continue
                
                pairs.append({
                    'query': qry,
                    'subject': sbj,
                    'identity': pident,
                    'align_len': alen,
                    'evalue': evalue,
                    'bitscore': bitscore
                })
    
    print(f"Loaded {len(pairs)} BLAST pairs (non-self)")
    return pairs

def identify_tandem_duplications(coords, blast_pairs):
    """
    Identify tandem duplications: WRKY genes within 200kb on same chromosome.
    Consider gene pairs that are at distinct loci (different gene_id).
    """
    # Build a quick lookup for BLAST pairs (only between distinct protein IDs)
    blast_lookup = {}
    for bp in blast_pairs:
        q, s = bp['query'], bp['subject']
        if q == s:
            continue
        key = (q, s) if q < s else (s, q)
        if key not in blast_lookup or bp['evalue'] < blast_lookup[key]['evalue']:
            blast_lookup[key] = bp
    
    # Group distinct gene loci by chromosome (use gene_id to merge isoforms)
    by_chrom = defaultdict(list)
    gene_loci = {}  # gene_id -> (prot_id, chrom, midpoint)
    for prot_id, loc in coords.items():
        gid = loc['gene_id']
        if gid not in gene_loci:
            gene_loci[gid] = (prot_id, loc['chrom'], loc['midpoint'])
    
    for gid, (prot_id, chrom, midpoint) in gene_loci.items():
        by_chrom[chrom].append((prot_id, midpoint, gid))
    
    for chrom in by_chrom:
        by_chrom[chrom].sort(key=lambda x: x[1])  # sort by midpoint
    
    tandem_pairs = []
    
    # Find distinct gene loci within TANDEM_DISTANCE on same chromosome
    chrom_genes = list(by_chrom.items())
    for chrom, genes in chrom_genes:
        for i in range(len(genes)):
            for j in range(i+1, len(genes)):
                dist = genes[j][1] - genes[i][1]
                if dist <= TANDEM_DISTANCE:
                    g1, g2 = genes[i][0], genes[j][0]
                    if g1 == g2:
                        continue  # skip same gene
                    key = (g1, g2) if g1 < g2 else (g2, g1)
                    blast_info = blast_lookup.get(key)
                    
                    if blast_info is not None:
                        tandem_pairs.append({
                            'gene1': g1,
                            'gene2': g2,
                            'chrom': chrom,
                            'distance': dist,
                            'identity': blast_info['identity'],
                            'evalue': blast_info['evalue']
                        })
                else:
                    break  # Since sorted, further genes will be even farther
    
    print(f"Identified {len(tandem_pairs)} tandem duplication pairs")
    return tandem_pairs

def identify_segmental_duplications(coords, blast_pairs, tandem_pairs):
    """
    Identify segmental duplications:
    - Gene pairs on different chromosomes (interchromosomal)
    - Or far apart on same chromosome (> 2Mb, intrachromosomal distant)
    - Using only distinct gene loci (merge isoforms)
    - With significant BLAST evidence
    """
    tandem_set = set()
    for tp in tandem_pairs:
        tandem_set.add((tp['gene1'], tp['gene2']))
        tandem_set.add((tp['gene2'], tp['gene1']))
    
    # Map gene_id -> representative protein, chrom, midpoint
    gene_loci = {}
    for prot_id, loc in coords.items():
        gid = loc['gene_id']
        if gid not in gene_loci:
            gene_loci[gid] = (prot_id, loc['chrom'], loc['midpoint'])
    
    # Build representative list
    rep_proteins = {v[0]: v for v in gene_loci.values()}  # prot_id -> (prot_id, chrom, midpoint)
    
    # Build BLAST lookup between distinct gene loci
    # Use best hit between any isoforms of two loci
    best_blast = {}
    for bp in blast_pairs:
        qry, sbj = bp['query'], bp['subject']
        if qry not in coords or sbj not in coords:
            continue
        gid1, gid2 = coords[qry]['gene_id'], coords[sbj]['gene_id']
        if gid1 == gid2:
            continue  # skip same gene isoforms
        
        # Use representative proteins
        rep1 = gene_loci[gid1][0]
        rep2 = gene_loci[gid2][0]
        pair_key = (rep1, rep2) if rep1 < rep2 else (rep2, rep1)
        if pair_key not in best_blast or bp['bitscore'] > best_blast[pair_key]['bitscore']:
            best_blast[pair_key] = bp
    
    segmental_pairs = []
    
    for (qry, sbj), bp in best_blast.items():
        # Both must be representative
        if qry not in rep_proteins or sbj not in rep_proteins:
            continue
        
        # Skip if already classified as tandem
        if (qry, sbj) in tandem_set:
            continue
        
        loc1, loc2 = coords[qry], coords[sbj]
        
        if loc1['chrom'] != loc2['chrom']:
            segmental_pairs.append({
                'gene1': qry, 'gene2': sbj,
                'chrom1': loc1['chrom'], 'pos1': loc1['midpoint'],
                'chrom2': loc2['chrom'], 'pos2': loc2['midpoint'],
                'identity': bp['identity'], 'evalue': bp['evalue'],
                'bitscore': bp['bitscore'], 'type': 'interchromosomal'
            })
        else:
            dist = abs(loc2['midpoint'] - loc1['midpoint'])
            if dist > 2000000:
                segmental_pairs.append({
                    'gene1': qry, 'gene2': sbj,
                    'chrom1': loc1['chrom'], 'pos1': loc1['midpoint'],
                    'chrom2': loc2['chrom'], 'pos2': loc2['midpoint'],
                    'identity': bp['identity'], 'evalue': bp['evalue'],
                    'bitscore': bp['bitscore'], 'distance': dist,
                    'type': 'intrachromosomal_distant'
                })
    
    print(f"Identified {len(segmental_pairs)} segmental duplication pairs")
    return segmental_pairs

def build_collinear_blocks(coords, blast_pairs, tandem_pairs):
    """
    Build collinear blocks from inter-chromosomal BLAST hits.
    Uses a simplified approach: group genes that form conserved synteny 
    across chromosome pairs.
    """
    # Use distinct gene loci only
    gene_loci = {}
    for prot_id, loc in coords.items():
        gid = loc['gene_id']
        if gid not in gene_loci:
            gene_loci[gid] = (prot_id, loc['chrom'], loc['midpoint'], loc['start'], loc['end'])
    
    # Build gene lists per chromosome (distinct loci)
    by_chrom = defaultdict(list)
    for gid, (prot_id, chrom, midpoint, start, end) in gene_loci.items():
        by_chrom[chrom].append((prot_id, midpoint, start, end))
    
    for chrom in by_chrom:
        by_chrom[chrom].sort(key=lambda x: x[1])  # sort by position
    
    # Collect best inter-chromosomal BLAST hits between distinct loci
    rep_proteins = {v[0] for v in gene_loci.values()}
    
    best_blast = {}
    for bp in blast_pairs:
        qry, sbj = bp['query'], bp['subject']
        if qry not in coords or sbj not in coords:
            continue
        gid1, gid2 = coords[qry]['gene_id'], coords[sbj]['gene_id']
        if gid1 == gid2:
            continue
        
        # Get representatives
        rep1 = gene_loci[gid1][0]
        rep2 = gene_loci[gid2][0]
        
        loc1, loc2 = coords[rep1], coords[rep2]
        if loc1['chrom'] == loc2['chrom']:
            continue  # skip same-chromosome for collinear blocks
        
        pair_key = (rep1, rep2) if rep1 < rep2 else (rep2, rep1)
        if pair_key not in best_blast or bp['bitscore'] > best_blast[pair_key]['bitscore']:
            best_blast[pair_key] = bp
    
    # Group inter-chromosomal hits by chromosome pair
    chrom_pairs = defaultdict(list)
    for (g1, g2), bp in best_blast.items():
        if bp['evalue'] >= 1e-5:
            continue
        loc1, loc2 = coords[g1], coords[g2]
        if loc1['chrom'] < loc2['chrom']:
            cp = (loc1['chrom'], loc2['chrom'])
            chrom_pairs[cp].append({
                'gene1': g1, 'gene2': g2,
                'pos1': loc1['midpoint'], 'pos2': loc2['midpoint'],
                'identity': bp['identity'], 'bitscore': bp['bitscore']
            })
        else:
            cp = (loc2['chrom'], loc1['chrom'])
            chrom_pairs[cp].append({
                'gene1': g2, 'gene2': g1,
                'pos1': loc2['midpoint'], 'pos2': loc1['midpoint'],
                'identity': bp['identity'], 'bitscore': bp['bitscore']
            })
    
    # Sort each chromosome pair's hits by position
    for cp in chrom_pairs:
        chrom_pairs[cp].sort(key=lambda x: (x['pos1'], x['pos2']))
    
    # Find collinear blocks using a sliding window approach
    # A block = contiguous segment where the relative order of genes is conserved
    all_blocks = []
    
    for cp, hits in chrom_pairs.items():
        if len(hits) < 2:
            continue
        
        i = 0
        while i < len(hits):
            # Start a potential block
            block = [hits[i]]
            j = i + 1
            while j < len(hits):
                last = block[-1]
                current = hits[j]
                # Check if order is conserved (both positions increase)
                if current['pos1'] > last['pos1'] and current['pos2'] > last['pos2']:
                    # Allow gap of up to 5 unassigned genes between block members
                    block.append(current)
                elif current['pos1'] < last['pos1']:
                    # Order broken - end this block
                    break
                j += 1
            
            if len(block) >= 2:
                all_blocks.append({
                    'chrom_pair': cp,
                    'hits': block,
                    'size': len(block),
                    'chrom1_range': (block[0]['pos1'], block[-1]['pos1']),
                    'chrom2_range': (block[0]['pos2'], block[-1]['pos2'])
                })
                i = j  # Move past this block
            else:
                i += 1
    
    # Deduplicate and filter
    seen_sigs = set()
    unique_blocks = []
    for block in all_blocks:
        sig = (block['chrom_pair'], block['chrom1_range'], block['chrom2_range'])
        if sig not in seen_sigs:
            seen_sigs.add(sig)
            unique_blocks.append(block)
    
    print(f"Found {len(unique_blocks)} collinear blocks across chromosome pairs")
    return unique_blocks

def load_kaks():
    """Load KaKs results if available."""
    kaks_data = {}
    if not os.path.exists(KAKS_FILE):
        return kaks_data
    
    # Try different encodings since file may contain Chinese characters
    for enc in ['utf-8-sig', 'gbk', 'gb18030', 'latin-1']:
        try:
            with open(KAKS_FILE, encoding=enc) as f:
                header = f.readline().strip().split(',')
                for line in f:
                    parts = line.strip().split(',')
                    if len(parts) >= 5:
                        g1, g2 = parts[0], parts[1]
                        try:
                            ka = float(parts[2]) if parts[2] != 'NA' else None
                            ks = float(parts[3]) if parts[3] != 'NA' else None
                            ka_ks = float(parts[4]) if parts[4] != 'NA' else None
                            kaks_data[(g1, g2)] = {'Ka': ka, 'Ks': ks, 'Ka_Ks': ka_ks}
                        except ValueError:
                            pass
            if kaks_data:
                print(f"  (read with encoding: {enc})")
                break
        except (UnicodeDecodeError, UnicodeError):
            continue
    
    print(f"Loaded {len(kaks_data)} KaKs results")
    return kaks_data

def write_results(tandem_pairs, segmental_pairs, collinear_blocks, coords, kaks_data):
    """Write all duplication analysis results."""
    
    # 1. Tandem duplications
    tandem_file = os.path.join(OUTPUT_DIR, 'tandem_duplications.tsv')
    with open(tandem_file, 'w') as f:
        f.write("Gene1\tGene2\tChromosome\tDistance_bp\tIdentity_Pct\tEvalue")
        # Add KaKs columns if available
        if kaks_data:
            f.write("\tKa\tKs\tKa/Ks")
        f.write("\n")
        for tp in sorted(tandem_pairs, key=lambda x: (x['chrom'], x['distance'])):
            f.write(f"{tp['gene1']}\t{tp['gene2']}\t{tp['chrom']}\t{tp['distance']}\t{tp['identity']:.2f}\t{tp['evalue']:.2e}")
            if kaks_data:
                pair_key = (tp['gene1'], tp['gene2'])
                rev_key = (tp['gene2'], tp['gene1'])
                k = kaks_data.get(pair_key, kaks_data.get(rev_key, {}))
                f.write(f"\t{k.get('Ka', 'NA')}\t{k.get('Ks', 'NA')}\t{k.get('Ka_Ks', 'NA')}")
            f.write("\n")
    print(f"Written: {tandem_file}")
    
    # 2. Segmental duplications
    seg_file = os.path.join(OUTPUT_DIR, 'segmental_duplications.tsv')
    with open(seg_file, 'w') as f:
        f.write("Gene1\tGene2\tChrom1\tPos1\tChrom2\tPos2\tIdentity_Pct\tEvalue\tBitscore\tType")
        if kaks_data:
            f.write("\tKa\tKs\tKa/Ks")
        f.write("\n")
        for sp in sorted(segmental_pairs, key=lambda x: (x.get('chrom1', ''), x.get('pos1', 0))):
            f.write(f"{sp['gene1']}\t{sp['gene2']}\t{sp.get('chrom1', '')}\t{sp.get('pos1', '')}\t"
                   f"{sp.get('chrom2', '')}\t{sp.get('pos2', '')}\t{sp['identity']:.2f}\t{sp['evalue']:.2e}\t"
                   f"{sp['bitscore']:.1f}\t{sp['type']}")
            if kaks_data:
                pair_key = (sp['gene1'], sp['gene2'])
                rev_key = (sp['gene2'], sp['gene1'])
                k = kaks_data.get(pair_key, kaks_data.get(rev_key, {}))
                f.write(f"\t{k.get('Ka', 'NA')}\t{k.get('Ks', 'NA')}\t{k.get('Ka_Ks', 'NA')}")
            f.write("\n")
    print(f"Written: {seg_file}")
    
    # 3. Collinear blocks
    block_file = os.path.join(OUTPUT_DIR, 'collinear_blocks.tsv')
    with open(block_file, 'w') as f:
        f.write("Block_ID\tChrom1\tGene1\tPos1\tChrom2\tGene2\tPos2\tIdentity_Pct\n")
        for bidx, block in enumerate(collinear_blocks, 1):
            chrom1, chrom2 = block['chrom_pair']
            for pair in block['hits']:
                f.write(f"Block_{bidx}\t{chrom1}\t{pair['gene1']}\t{pair['pos1']}\t"
                       f"{chrom2}\t{pair['gene2']}\t{pair['pos2']}\t{pair['identity']:.2f}\n")
    print(f"Written: {block_file}")
    
    # 4. Summary statistics
    summary_file = os.path.join(OUTPUT_DIR, 'duplication_summary.tsv')
    
    # Count distinct gene loci
    gene_loci = {}
    for prot_id, loc in coords.items():
        gid = loc['gene_id']
        if gid not in gene_loci:
            gene_loci[gid] = prot_id
    
    # Count genes involved in each type (distinct loci)
    tandem_genes = set()
    for tp in tandem_pairs:
        tandem_genes.add(tp['gene1'])
        tandem_genes.add(tp['gene2'])
    
    seg_genes = set()
    for sp in segmental_pairs:
        seg_genes.add(sp['gene1'])
        seg_genes.add(sp['gene2'])
    
    # Chromosome name mapping
    chrom_names = {
        'NC_037285.2': 'Chr01', 'NC_037286.2': 'Chr02', 'NC_037287.2': 'Chr03',
        'NC_037288.2': 'Chr04', 'NC_037289.2': 'Chr05', 'NC_037290.2': 'Chr06',
        'NC_037291.2': 'Chr07', 'NC_037292.2': 'Chr08', 'NC_037293.2': 'Chr09',
        'NC_037294.2': 'Chr10', 'NC_037295.2': 'Chr11', 'NC_037296.2': 'Chr12',
        'NC_037297.2': 'Chr13', 'NC_037298.2': 'Chr14', 'NC_037299.2': 'Chr15',
        'NC_037300.2': 'Chr16', 'NC_037301.2': 'Chr17', 'NC_037302.2': 'Chr18',
        'NC_037303.2': 'Chr19'
    }
    
    with open(summary_file, 'w') as f:
        f.write("Metric\tValue\n")
        f.write(f"Total_WRKY_transcripts\t{len(coords)}\n")
        f.write(f"Distinct_WRKY_gene_loci\t{len(gene_loci)}\n")
        f.write(f"Tandem_duplication_pairs\t{len(tandem_pairs)}\n")
        f.write(f"Distinct_genes_in_tandem_duplications\t{len(tandem_genes)}\n")
        f.write(f"Segmental_duplication_pairs\t{len(segmental_pairs)}\n")
        f.write(f"Distinct_genes_in_segmental_duplications\t{len(seg_genes)}\n")
        f.write(f"Collinear_blocks\t{len(collinear_blocks)}\n")
        if collinear_blocks:
            f.write(f"Collinear_block_summary:\n")
            for block in sorted(collinear_blocks, key=lambda x: -x['size']):
                c1, c2 = block['chrom_pair']
                n1 = chrom_names.get(c1, c1)
                n2 = chrom_names.get(c2, c2)
                f.write(f"  {n1}-{n2}: {block['size']} pairs, "
                       f"range1={block['chrom1_range'][0]:,}-{block['chrom1_range'][1]:,}, "
                       f"range2={block['chrom2_range'][0]:,}-{block['chrom2_range'][1]:,}\n")
        
        # Chromosome distribution (distinct loci)
        locus_chrom_counts = defaultdict(int)
        for gid, prot_id in gene_loci.items():
            loc = coords[prot_id]
            locus_chrom_counts[loc['chrom']] += 1
        
        f.write(f"\nLocus_chromosome_distribution:\n")
        for chrom in sorted(locus_chrom_counts.keys()):
            n = chrom_names.get(chrom, chrom)
            f.write(f"{n}\t{locus_chrom_counts[chrom]}\n")
    
    print(f"Written: {summary_file}")

def main():
    print("=" * 60)
    print("Step 2: WRKY Duplication Classification")
    print("=" * 60)
    
    coords = load_coordinates()
    blast_pairs = load_blast_results()
    kaks_data = load_kaks()
    
    # Count distinct gene loci
    gene_loci = set(loc['gene_id'] for loc in coords.values())
    
    print(f"\nWRKY transcripts with coordinates: {len(coords)}")
    print(f"Distinct WRKY gene loci: {len(gene_loci)}")
    print(f"BLAST pairs loaded: {len(blast_pairs)}")
    print(f"KaKs pairs loaded: {len(kaks_data)}")
    
    # Step 2a: Tandem duplications
    print("\n--- Identifying Tandem Duplications ---")
    tandem_pairs = identify_tandem_duplications(coords, blast_pairs)
    
    # Step 2b: Segmental duplications
    print("\n--- Identifying Segmental Duplications ---")
    segmental_pairs = identify_segmental_duplications(coords, blast_pairs, tandem_pairs)
    
    # Step 2c: Collinear blocks
    print("\n--- Building Collinear Blocks ---")
    collinear_blocks = build_collinear_blocks(coords, blast_pairs, tandem_pairs)
    
    # Write all results
    print("\n--- Writing Results ---")
    write_results(tandem_pairs, segmental_pairs, collinear_blocks, coords, kaks_data)
    
    print("\nStep 2 complete!")

if __name__ == '__main__':
    main()
