# 看完整索引（含每份文件的来源 URL、上游 commit）
less references/INDEX.md

# 校验本地文件与抓取时是否一致（SHA256 + 字节数）
python3 fetch_references.py --verify

# 上游文档更新后重新抓取
python3 fetch_references.py
