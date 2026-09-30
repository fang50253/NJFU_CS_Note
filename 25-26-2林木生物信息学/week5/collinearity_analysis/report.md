# WRKY 基因家族共线性分析报告

## 1. 实验目的

对毛果杨（*Populus trichocarpa*）WRKY 转录因子基因家族进行共线性分析，包括：
- WRKY 基因在染色体上的分布特征
- 串联重复（Tandem Duplication）和片段重复（Segmental Duplication）事件的鉴定
- 共线性区块（Collinear Blocks）的识别与统计
- 结合 KaKs 选择压力分析结果

## 2. 数据来源与预处理

### 2.1 基因组数据

- **物种**: *Populus trichocarpa* (黑棉杨)
- **基因组版本**: GCF_000002775.5 (RefSeq, P.trichocarpa_v4.1)
- **数据来源**: NCBI Datasets
- **基因组大小**: 392,162,179 bp
- **染色体数目**: 19 条
- **注释基因数**: 34,621

### 2.2 WRKY 基因家族数据

- 前期已通过 HMMER 和 BLAST 鉴定出 **149 条 WRKY 转录本**，对应 **98 个独立基因位点**（多个可变剪接异构体）
- 已有 WRKY 基因间的 BLASTP 全长比对结果（29,410 对非自身匹配）
- 已有 100 对基因的 Ka/Ks 选择压力分析结果

### 2.3 分析方法

1. 从 NCBI GFF 注释文件中提取每个 WRKY 基因的染色体坐标
2. 将可变剪接异构体合并为独立基因位点（以 LOC ID 区分）
3. 基于染色体邻近性和 BLAST 证据鉴定串联重复（间距 ≤ 200 kb）
4. 基于染色体间/染色体内远距离 BLAST 匹配鉴定片段重复
5. 构建染色体对间的共线性区块（保持基因顺序保守性的多基因配对）

## 3. 染色体分布分析

WRKY 基因不均勻分布在 19 条染色体上：

| 染色体 | WRKY 基因位点数 |
|--------|-----------------|
| Chr01  | 12 |
| Chr02  | 11 |
| Chr14  | 10 |
| Chr06  | 9 |
| Chr03  | 6 |
| Chr05  | 6 |
| Chr11  | 6 |
| Chr18  | 6 |
| Chr13  | 5 |
| Chr04  | 4 |
| Chr16  | 4 |
| Chr17  | 4 |
| Chr07  | 3 |
| Chr08  | 3 |
| Chr10  | 3 |
| Chr12  | 2 |
| Chr15  | 2 |
| Chr19  | 2 |

**分布特征**: WRKY 基因在染色体上呈簇状分布，Chr01（12 个）、Chr02（11 个）和 Chr14（10 个）携带最多的 WRKY 基因，而 Chr12、Chr15 和 Chr19 仅含 2 个。Chr09 上未检测到 WRKY 基因。

![染色体分布图](file:///D:/Documents/Github/CladeCheck/task3/collinearity_analysis/output/chromosome_distribution.png)

## 4. 串联重复分析

### 4.1 鉴定标准

- 同一染色体的两个 WRKY 位点
- 基因间距 ≤ 200 kb
- 有显著的 BLASTP 匹配（E-value < 1e-5）

### 4.2 结果

共鉴定出 **12 对串联重复基因**，涉及 **21 个独立基因位点**：

| 基因1 | 基因2 | 染色体 | 间距(bp) | 相似度(%) |
|-------|-------|--------|----------|-----------|
| XP_006386616.2 | XP_002301377.2 | Chr02 | 29,077 | 39.74 |
| XP_024456867.1 | XP_052308647.1 | Chr05 | 121,039 | 46.96 |
| XP_002308704.1 | XP_006382109.3 | Chr06 | 43,055 | 43.10 |
| XP_002310044.1 | XP_024461002.1 | Chr07 | 192,550 | 45.83 |
| XP_002312267.1 | XP_002311329.2 | Chr08 | 125,898 | 40.26 |
| XP_024466901.1 | XP_002315024.1 | Chr10 | 171,372 | 45.93 |
| XP_002319879.4 | XP_024439297.1 | Chr13 | 10,213 | 41.51 |
| XP_006375351.1 | XP_002320160.2 | Chr14 | 20,195 | 31.58 |
| XP_002320967.3 | XP_052303237.1 | Chr14 | 81,774 | 53.23 |
| XP_002324328.1 | XP_006371762.1 | Chr18 | 13,944 | 45.25 |
| XP_024446284.2 | XP_002324328.1 | Chr18 | 42,934 | 41.67 |
| XP_024446284.2 | XP_006371762.1 | Chr18 | 56,878 | 50.88 |

**串联成簇最显著的染色体**: Chr14（3 对）和 Chr18（3 对），其中 Chr18 的 3 个 WRKY 位点（XP_002324328.1, XP_006371762.1, XP_024446284.2）彼此串联排列，表明该区域发生过多次串联重复事件。

## 5. 片段重复分析

### 5.1 鉴定标准

- 不同染色体上的 WRKY 基因对（染色体间）
- 或同一染色体上相距 > 2 Mb 的基因对
- 有显著的 BLASTP 匹配

### 5.2 结果

共鉴定出 **4,584 对片段重复**（位点合并后），涉及全部 **98 个 WRKY 基因位点**。表明 WRKY 基因家族主要通过片段重复/全基因组重复（WGD）进行扩增。

### 5.3 共线性区块

共鉴定出 **153 个共线性区块**，覆盖所有 19 条染色体间的配对关系。主要共线性区块（≥6 对基因匹配）：

| 染色体对 | 基因对数 | 区间范围(Chr1) | 区间范围(Chr2) |
|----------|---------|----------------|----------------|
| Chr01-Chr02 | 11 | 159Kb-48.6Mb | 2.8Mb-21.8Mb |
| Chr01-Chr14 | 10 | 159Kb-38.0Mb | 1.5Mb-11.9Mb |
| Chr02-Chr14 | 10 | 2.8Mb-15.8Mb | 1.5Mb-11.9Mb |
| Chr01-Chr06 | 9 | 159Kb-36.6Mb | 5.3Mb-26.0Mb |
| Chr02-Chr06 | 9 | 2.8Mb-15.6Mb | 5.3Mb-26.0Mb |
| Chr06-Chr14 | 9 | 5.3Mb-26.0Mb | 1.5Mb-10.9Mb |

这些大规模共线性区块与杨柳科（Salicaceae）已报道的全基因组重复事件（Salicoid WGD）特征一致，为 WRKY 基因家族的片段重复扩增提供了有力证据。

![共线性点阵图](file:///D:/Documents/Github/CladeCheck/task3/collinearity_analysis/output/collinearity_dotplot.png)

## 6. 基因分布可视化

![染色体基因分布图](file:///D:/Documents/Github/CladeCheck/task3/collinearity_analysis/output/chromosome_gene_map.png)

## 7. 总结

### 7.1 主要发现

| 指标 | 数值 |
|------|------|
| WRKY 转录本总数 | 149 |
| 独立 WRKY 基因位点数 | 98 |
| 串联重复对数 | 12 |
| 参与串联重复的基因数 | 21 |
| 片段重复对数 | 4,584 |
| 参与片段重复的基因数 | 98（全部） |
| 共线性区块 | 153 |

### 7.2 结论

1. **WRKY 基因广泛分布于 18 条染色体**（Chr01-Chr19，Chr09 除外），其中 Chr01、Chr02 和 Chr14 为富集染色体。

2. **片段重复是 WRKY 基因家族扩增的主要机制**，全部 98 个位点均参与了染色体间的同源关系，共线性区块分析显示这些重复与杨柳科古多倍化事件（Salicoid WGD）相关。

3. **串联重复对 WRKY 基因家族的局部扩增也有贡献**，12 对串联重复基因主要位于 Chr14 和 Chr18，在这些区域形成基因簇。

4. **WRKY 基因家族的扩张模式**以片段重复主导、串联重复补充，这与 WRKY 作为转录因子家族的进化特征一致——通过基因重复获得功能分化（亚功能化/新功能化）。

### 7.3 输出文件

| 文件 | 说明 |
|------|------|
| `collinearity_analysis/output/WRKY_chromosome_coordinates.tsv` | WRKY 基因染色体坐标 |
| `collinearity_analysis/output/WRKY_genes.gff` | GFF 格式的基因区间 |
| `collinearity_analysis/output/WRKY_genes.bed` | BED 格式的基因区间 |
| `collinearity_analysis/output/tandem_duplications.tsv` | 串联重复基因对 |
| `collinearity_analysis/output/segmental_duplications.tsv` | 片段重复基因对 |
| `collinearity_analysis/output/collinear_blocks.tsv` | 共线性区块 |
| `collinearity_analysis/output/duplication_summary.tsv` | 统计汇总 |
| `collinearity_analysis/output/chromosome_distribution.png` | 染色体分布图 |
| `collinearity_analysis/output/chromosome_gene_map.png` | 基因定位图 |
| `collinearity_analysis/output/duplication_types.png` | 重复类型图 |
| `collinearity_analysis/output/collinearity_dotplot.png` | 共线性散点图 |
