#!/usr/bin/env python3
"""
Step 3: Generate visualizations for WRKY collinearity analysis.
- Chromosome distribution bar chart
- Chromosome ideogram-style map
- Tandem vs segmental duplication comparison
- Collinearity dot plot
"""

import os
import sys
from collections import defaultdict, OrderedDict

# Try to import matplotlib
try:
    import matplotlib
    matplotlib.use('Agg')
    import matplotlib.pyplot as plt
    import matplotlib.patches as mpatches
    HAS_MPL = True
except ImportError:
    HAS_MPL = False
    print("WARNING: matplotlib not available. Install with: pip install matplotlib")

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUTPUT_DIR = os.path.join(BASE, 'output')
PROJECT_DIR = r'D:\Documents\Github\CladeCheck\task3'

COORDS_FILE = os.path.join(OUTPUT_DIR, 'WRKY_chromosome_coordinates.tsv')
TANDEM_FILE = os.path.join(OUTPUT_DIR, 'tandem_duplications.tsv')
SEG_FILE = os.path.join(OUTPUT_DIR, 'segmental_duplications.tsv')
BLOCK_FILE = os.path.join(OUTPUT_DIR, 'collinear_blocks.tsv')

def load_coords():
    coords = {}
    with open(COORDS_FILE) as f:
        header = f.readline()
        for line in f:
            parts = line.strip().split('\t')
            if len(parts) >= 7:
                coords[parts[0]] = {
                    'chrom': parts[1],
                    'start': int(parts[2]),
                    'end': int(parts[3]),
                    'strand': parts[4],
                    'gene_id': parts[5],
                    'midpoint': int(parts[6])
                }
    return coords

def load_duplications(filepath):
    pairs = []
    if not os.path.exists(filepath):
        return pairs
    with open(filepath) as f:
        header = f.readline()
        for line in f:
            parts = line.strip().split('\t')
            if len(parts) >= 2:
                pairs.append((parts[0], parts[1]))
    return pairs

def load_segmental():
    pairs = []
    if not os.path.exists(SEG_FILE):
        return pairs
    with open(SEG_FILE) as f:
        header = f.readline()
        for line in f:
            parts = line.strip().split('\t')
            if len(parts) >= 2:
                pairs.append((parts[0], parts[1], parts[3], parts[5]))
    return pairs

def plot_chromosome_distribution(coords):
    """Bar chart of WRKY genes per chromosome."""
    if not HAS_MPL:
        return
    
    chrom_counts = defaultdict(int)
    for prot_id, loc in coords.items():
        chrom_counts[loc['chrom']] += 1
    
    # Sort by chromosome name (NC_037285.2 = Chr01, etc.)
    chroms = sorted(chrom_counts.keys())
    counts = [chrom_counts[c] for c in chroms]
    
    # Short labels
    chrom_names = {
        'NC_037285.2': 'Chr01', 'NC_037286.2': 'Chr02', 'NC_037287.2': 'Chr03',
        'NC_037288.2': 'Chr04', 'NC_037289.2': 'Chr05', 'NC_037290.2': 'Chr06',
        'NC_037291.2': 'Chr07', 'NC_037292.2': 'Chr08', 'NC_037293.2': 'Chr09',
        'NC_037294.2': 'Chr10', 'NC_037295.2': 'Chr11', 'NC_037296.2': 'Chr12',
        'NC_037297.2': 'Chr13', 'NC_037298.2': 'Chr14', 'NC_037299.2': 'Chr15',
        'NC_037300.2': 'Chr16', 'NC_037301.2': 'Chr17', 'NC_037302.2': 'Chr18',
        'NC_037303.2': 'Chr19'
    }
    short_labels = [chrom_names.get(c, c.replace('NW_', 'Scaffold_')) for c in chroms]
    
    fig, ax = plt.subplots(figsize=(14, 6))
    bars = ax.bar(range(len(chroms)), counts, color='steelblue', edgecolor='navy')
    
    ax.set_xlabel('Chromosome')
    ax.set_ylabel('Number of WRKY Genes')
    ax.set_title('Distribution of WRKY Genes on Populus trichocarpa Chromosomes')
    ax.set_xticks(range(len(chroms)))
    ax.set_xticklabels(short_labels, rotation=45, ha='right', fontsize=8)
    
    # Add value labels on bars
    for bar, count in zip(bars, counts):
        ax.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 0.3,
                str(count), ha='center', va='bottom', fontsize=8)
    
    plt.tight_layout()
    outpath = os.path.join(OUTPUT_DIR, 'chromosome_distribution.png')
    plt.savefig(outpath, dpi=200)
    plt.close()
    print(f"Saved: {outpath}")

def plot_gene_order_map(coords):
    """Plot gene order on each chromosome (ideogram-style)."""
    if not HAS_MPL:
        return
    
    # Group by chromosome
    by_chrom = defaultdict(list)
    for prot_id, loc in coords.items():
        by_chrom[loc['chrom']].append((prot_id, loc['start'], loc['end'], loc['strand'], loc['midpoint']))
    
    for chrom in by_chrom:
        by_chrom[chrom].sort(key=lambda x: x[4])  # Sort by midpoint
    
    # Chromosome lengths (from GFF sequence-regions)
    chrom_lengths = {
        'NC_037285.2': 49788581, 'NC_037286.2': 25242375, 'NC_037287.2': 21678634,
        'NC_037288.2': 24140038, 'NC_037289.2': 24981103, 'NC_037290.2': 27516652,
        'NC_037291.2': 15561420, 'NC_037292.2': 19195260, 'NC_037293.2': 12987399,
        'NC_037294.2': 22799081, 'NC_037295.2': 19288771, 'NC_037296.2': 15589050,
        'NC_037297.2': 15705617, 'NC_037298.2': 17801709, 'NC_037299.2': 15231745,
        'NC_037300.2': 14619816, 'NC_037301.2': 15189755, 'NC_037302.2': 16264003,
        'NC_037303.2': 15623655
    }
    
    # Only plot chromosomes that have WRKY genes
    main_chroms = sorted([c for c in by_chrom.keys() if c in chrom_lengths])
    if not main_chroms:
        print("No main chromosomes found, skipping gene order map")
        return
    
    fig, axes = plt.subplots(len(main_chroms), 1, figsize=(12, 2 * len(main_chroms)))
    if len(main_chroms) == 1:
        axes = [axes]
    
    for ax, chrom in zip(axes, main_chroms):
        length = chrom_lengths.get(chrom, max(l[4] for l in by_chrom[chrom]) + 100000)
        
        # Draw chromosome backbone
        ax.plot([0, length], [0, 0], color='gray', linewidth=6, zorder=1)
        
        # Plot each gene
        genes = by_chrom[chrom]
        for prot_id, start, end, strand, midpoint in genes:
            color = 'red' if strand == '+' else 'blue'
            y = 0
            ax.plot(midpoint, y, marker='v' if strand == '+' else '^', 
                   color=color, markersize=8, zorder=2)
        
        # Short label
        chrom_names = {
            'NC_037285.2': 'Chr01', 'NC_037286.2': 'Chr02', 'NC_037287.2': 'Chr03',
            'NC_037288.2': 'Chr04', 'NC_037289.2': 'Chr05', 'NC_037290.2': 'Chr06',
            'NC_037291.2': 'Chr07', 'NC_037292.2': 'Chr08', 'NC_037293.2': 'Chr09',
            'NC_037294.2': 'Chr10', 'NC_037295.2': 'Chr11', 'NC_037296.2': 'Chr12',
            'NC_037297.2': 'Chr13', 'NC_037298.2': 'Chr14', 'NC_037299.2': 'Chr15',
            'NC_037300.2': 'Chr16', 'NC_037301.2': 'Chr17', 'NC_037302.2': 'Chr18',
            'NC_037303.2': 'Chr19'
        }
        label = f"{chrom_names.get(chrom, chrom)} ({len(genes)} WRKY)"
        
        ax.set_ylabel(label, fontsize=8, rotation=0, ha='right', va='center', labelpad=10)
        ax.set_xlim(0, length)
        ax.set_ylim(-1, 1)
        ax.set_yticks([])
        ax.spines['top'].set_visible(False)
        ax.spines['right'].set_visible(False)
        ax.spines['left'].set_visible(False)
        ax.tick_params(axis='x', labelsize=6)
    
    axes[-1].set_xlabel('Chromosome Position (bp)', fontsize=9)
    plt.tight_layout()
    outpath = os.path.join(OUTPUT_DIR, 'chromosome_gene_map.png')
    plt.savefig(outpath, dpi=200)
    plt.close()
    print(f"Saved: {outpath}")

def plot_duplication_types(coords):
    """Pie/bar chart comparing tandem vs segmental duplications."""
    if not HAS_MPL:
        return
    
    tandem = load_duplications(TANDEM_FILE)
    seg = load_segmental()
    
    labels = ['Tandem\nDuplication', 'Segmental\nDuplication', 'No\nDuplication\nDetected']
    
    tandem_genes = set()
    for g1, g2 in tandem:
        tandem_genes.add(g1)
        tandem_genes.add(g2)
    
    seg_genes = set()
    for g1, g2, c1, c2 in seg:
        seg_genes.add(g1)
        seg_genes.add(g2)
    
    # Count mutually exclusive
    only_tandem = len(tandem_genes - seg_genes)
    only_seg = len(seg_genes - tandem_genes)
    both = len(tandem_genes & seg_genes)
    none_ = len(coords) - len(tandem_genes | seg_genes)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
    
    # Pie chart
    sizes = [len(tandem_genes), len(seg_genes), none_]
    colors = ['#ff9999', '#66b3ff', '#99ff99']
    ax1.pie(sizes, labels=['Tandem', 'Segmental', 'None'], colors=colors, autopct='%1.1f%%', startangle=90)
    ax1.set_title('WRKY Gene Duplication Types')
    
    # Bar chart
    categories = ['Tandem Only', 'Segmental Only', 'Both', 'None']
    values = [only_tandem, only_seg, both, none_]
    bars = ax2.bar(categories, values, color=['#ff9999', '#66b3ff', '#cc66ff', '#99ff99'])
    ax2.set_ylabel('Number of Genes')
    ax2.set_title('Duplication Category Distribution')
    for bar, val in zip(bars, values):
        ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 0.3,
                str(val), ha='center', fontsize=10)
    
    plt.tight_layout()
    outpath = os.path.join(OUTPUT_DIR, 'duplication_types.png')
    plt.savefig(outpath, dpi=200)
    plt.close()
    print(f"Saved: {outpath}")

def plot_collinearity_dotplot(coords):
    """Dot plot showing collinearity relationships between WRKY gene pairs."""
    if not HAS_MPL:
        return
    
    if not os.path.exists(BLOCK_FILE):
        return
    
    # Load blocks: each block has a Block_ID, then lines for pairs
    block_data = defaultdict(list)
    with open(BLOCK_FILE) as f:
        header = f.readline()
        for line in f:
            parts = line.strip().split('\t')
            if len(parts) >= 8:
                bid = parts[0]
                block_data[bid].append({
                    'chrom1': parts[1], 'gene1': parts[2], 'pos1': int(parts[3]),
                    'chrom2': parts[4], 'gene2': parts[5], 'pos2': int(parts[6])
                })
    
    if not block_data:
        return
    
    # Get top chromosome pairs by block size
    cp_sizes = defaultdict(int)
    cp_gene_pairs = defaultdict(set)
    for bid, pairs in block_data.items():
        if pairs:
            cp = (pairs[0]['chrom1'], pairs[0]['chrom2'])
            if cp[0] != cp[1]:
                cp_sizes[cp] += len(pairs)
                for p in pairs:
                    cp_gene_pairs[cp].add((p['gene1'], p['gene2']))
    
    significant_pairs = sorted(cp_sizes.keys(), key=lambda x: -cp_sizes[x])[:6]
    
    if not significant_pairs:
        return
    
    # Plot each significant pair
    n_plots = min(len(significant_pairs), 6)  # Limit to 6 plots
    fig, axes = plt.subplots(2, 3, figsize=(15, 10))
    axes = axes.flatten()
    
    for i in range(min(n_plots, 6)):
        cp = significant_pairs[i]
        ax = axes[i]
        
        # Get genes from both chromosomes
        chrom_a_genes = []
        chrom_b_genes = []
        
        for prot_id, loc in coords.items():
            if loc['chrom'] == cp[0]:
                chrom_a_genes.append((prot_id, loc['midpoint']))
            elif loc['chrom'] == cp[1]:
                chrom_b_genes.append((prot_id, loc['midpoint']))
        
        chrom_a_genes.sort(key=lambda x: x[1])
        chrom_b_genes.sort(key=lambda x: x[1])
        
        if not chrom_a_genes or not chrom_b_genes:
            continue
        
        # Build position mapping
        a_pos = {g[0]: i+1 for i, g in enumerate(chrom_a_genes)}
        b_pos = {g[0]: i+1 for i, g in enumerate(chrom_b_genes)}
        
        # Plot connections
        for bid, pairs in block_data.items():
            for p in pairs:
                if p['chrom1'] == cp[0] and p['chrom2'] == cp[1]:
                    if p['gene1'] in a_pos and p['gene2'] in b_pos:
                        ax.plot(a_pos[p['gene1']], b_pos[p['gene2']], 'o', 
                               color='crimson', markersize=4, alpha=0.7)
        
        chrom_names = {
            'NC_037285.2': 'Chr01', 'NC_037286.2': 'Chr02', 'NC_037287.2': 'Chr03',
            'NC_037288.2': 'Chr04', 'NC_037289.2': 'Chr05', 'NC_037290.2': 'Chr06',
            'NC_037291.2': 'Chr07', 'NC_037292.2': 'Chr08', 'NC_037293.2': 'Chr09',
            'NC_037294.2': 'Chr10', 'NC_037295.2': 'Chr11', 'NC_037296.2': 'Chr12',
            'NC_037297.2': 'Chr13', 'NC_037298.2': 'Chr14', 'NC_037299.2': 'Chr15',
            'NC_037300.2': 'Chr16', 'NC_037301.2': 'Chr17', 'NC_037302.2': 'Chr18',
            'NC_037303.2': 'Chr19'
        }
        chrom_a_label = chrom_names.get(cp[0], cp[0])
        chrom_b_label = chrom_names.get(cp[1], cp[1])
        
        ax.set_xlabel(f'{chrom_a_label} (gene index)')
        ax.set_ylabel(f'{chrom_b_label} (gene index)')
        ax.set_title(f'{chrom_a_label} vs {chrom_b_label}')
        ax.grid(True, alpha=0.3)
    
    # Hide unused subplots
    for i in range(n_plots, 6):
        axes[i].set_visible(False)
    
    plt.tight_layout()
    outpath = os.path.join(OUTPUT_DIR, 'collinearity_dotplot.png')
    plt.savefig(outpath, dpi=200)
    plt.close()
    print(f"Saved: {outpath}")

def main():
    print("=" * 60)
    print("Step 3: Collinearity Visualization")
    print("=" * 60)
    
    coords = load_coords()
    print(f"Loaded coordinates for {len(coords)} WRKY genes")
    
    if not HAS_MPL:
        print("Skipping visualizations (matplotlib not available)")
        return
    
    print("\nGenerating visualizations...")
    plot_chromosome_distribution(coords)
    plot_gene_order_map(coords)
    plot_duplication_types(coords)
    plot_collinearity_dotplot(coords)
    
    print("\nStep 3 complete!")

if __name__ == '__main__':
    main()
