python -c "
from Bio import SeqIO
records = list(SeqIO.parse('WRKY_CDS_final.fasta', 'fasta'))
print('前5个ID:')
for i, r in enumerate(records[:5], 1):
    print(f'{i}. {r.id}')
"