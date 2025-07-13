#!/usr/bin/env python3
import requests
import os
import chardet
from pathlib import Path
from urllib.parse import urlparse, urljoin

sources = []
oldSources = []
filePaths = []
printFileNames = True

def sanitize_filename(url):
    """更安全的文件名处理"""
    parsed = urlparse(url)
    domain = parsed.netloc.replace('www.', '')
    return domain.replace('.', '_')

def detect_encoding(content):
    """自动检测内容编码"""
    result = chardet.detect(content)
    return result['encoding'] or 'utf-8'

def getWebsite(url, path):
    """增强版的网页下载函数"""
    try:
        os.makedirs(os.path.dirname(path), exist_ok=True)
        headers = {
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36'
        }
        response = requests.get(url, headers=headers, timeout=15)
        response.raise_for_status()
        
        encoding = detect_encoding(response.content)
        try:
            decoded_content = response.content.decode(encoding)
        except UnicodeDecodeError:
            decoded_content = response.content.decode('utf-8', errors='replace')
        
        with open(path, 'w', encoding='utf-8', errors='replace') as f:
            f.write(decoded_content)
        print(f"✅ 成功保存: {path}")
        return True
    except Exception as e:
        print(f"⚠️ 错误: {str(e)}")
        return False

def getContent(pathToFile):
    """改进的文件读取"""
    try:
        with open(pathToFile, 'rb') as f:
            raw_content = f.read()
            encoding = detect_encoding(raw_content)
        
        with open(pathToFile, 'r', encoding=encoding, errors='replace') as f:
            return [line.strip() for line in f if line.strip()]
    except Exception as e:
        print(f"⚠️ 文件读取错误: {str(e)}")
        return []

def add(found, lang):
    """资源链接提取"""
    found = found[:found.find(lang) + len(lang)]
    for sep in [' ', '"', "'", '>', ')', ']']:
        if sep in found:
            found = found[found.rfind(sep) + 1:]
    if found and found not in sources and found not in oldSources:
        if printFileNames:
            print(f"🔗 发现资源: {found}")
        sources.append(found)

def findSources(content):
    """查找页面中的资源链接"""
    if not content:
        return
        
    for line in content:
        line = line.replace("'", '"')
        if ('href' in line or 'src' in line) and not line.startswith(('http:', 'https:')):
            for ext in ['.js', '.php', '.css', '.jpg', '.jpeg', '.gif', '.png', '.webp', '.htm', '.html', '.svg']:
                if ext in line.lower():
                    add(line, ext)

def download_binary(url, path):
    """下载二进制文件"""
    try:
        os.makedirs(os.path.dirname(path), exist_ok=True)
        r = requests.get(url, stream=True, timeout=15)
        r.raise_for_status()
        with open(path, 'wb') as f:
            for chunk in r.iter_content(1024):
                f.write(chunk)
        print(f"✅ 下载成功: {url}")
    except Exception as e:
        print(f"⚠️ 下载失败 {url}: {str(e)}")

def getSources():
    """下载所有找到的资源"""
    for source in sources[:]:
        # 处理绝对URL和相对URL
        if source.startswith(('http://', 'https://')):
            absolute_url = source
        else:
            if not source.startswith('/'):
                source = '/' + source
            absolute_url = urljoin(website, source)
        
        # 生成本地保存路径
        if source.startswith(('http://', 'https://')):
            # 对于绝对URL，使用域名后的路径部分
            parsed = urlparse(source)
            local_path = os.path.join(filename, parsed.path.lstrip('/'))
        else:
            local_path = os.path.join(filename, source.lstrip('/'))
        
        # 确保路径不以/结尾
        local_path = local_path.rstrip('/')
        
        # 跳过已存在的文件
        if os.path.exists(local_path):
            continue
            
        try:
            if any(local_path.lower().endswith(ext) for ext in ['.jpg', '.jpeg', '.gif', '.png', '.webp', '.svg']):
                download_binary(absolute_url, local_path)
            else:
                if getWebsite(absolute_url, local_path):
                    if local_path.endswith(('.htm', '.html')):
                        filePaths.append(local_path)
        except Exception as e:
            print(f"⚠️ 资源处理失败 {absolute_url}: {str(e)}")

if __name__ == "__main__":
    website = input('🌐 请输入网站URL: ').strip()
    
    if not website.startswith(('http://', 'https://')):
        website = 'https://' + website
    if website.endswith('/'):
        website = website[:-1]
    
    filename = sanitize_filename(website)
    
    if os.path.exists(filename):
        import shutil
        shutil.rmtree(filename)
    os.makedirs(filename, exist_ok=True)
    
    print(f"📁 创建下载目录: {filename}")
    
    index_path = os.path.join(filename, 'index.html')
    if getWebsite(website, index_path):
        content = getContent(index_path)
        if content:
            findSources(content)
            getSources()
            
            oldSources = sources.copy()
            sources = []
            
            for path in filePaths[:]:
                if os.path.exists(path):
                    content = getContent(path)
                    if content:
                        findSources(content)
                else:
                    filePaths.remove(path)
                    
            getSources()
    
    print("🎉 操作完成！")