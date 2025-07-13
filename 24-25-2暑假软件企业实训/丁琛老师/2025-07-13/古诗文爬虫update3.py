import requests
from bs4 import BeautifulSoup
import time
import json

HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36'
}

def page_request(url):
    try:
        response = requests.get(url, headers=HEADERS, timeout=10)
        response.raise_for_status()
        response.encoding = 'utf-8'
        return response.text
    except Exception as e:
        print(f"请求出错: {e}")
        return None

def page_parse(html):
    soup = BeautifulSoup(html, 'lxml')
    poems = []
    items = soup.find_all('div', class_='cont')
    print(f"找到 {len(items)} 个条目")  # 调试：检查找到的条目数量
    
    for item in items:
        a_tags = item.find_all('a')
        if a_tags:
            sentence = a_tags[0].text.strip()
            print(f"提取到句子: {sentence}")  # 调试：检查提取的内容
            poems.append(sentence)
    
    return poems

def save_to_file(poems, filename='poems.txt'):
    with open(filename, 'a', encoding='utf-8') as f:
        for poem in poems:
            f.write(f"{poem}\n\n")

if __name__ == '__main__':
    base_url = 'https://www.gushiwen.cn/mingjus/default.aspx?page={}'
    
    for page in range(1, 3):  # 爬取前2页
        url = base_url.format(page)
        print(f"正在爬取第 {page} 页: {url}")
        
        html = page_request(url)
        if html:
            poems = page_parse(html)
            save_to_file(poems)
            print(f"第 {page} 页爬取完成，共 {len(poems)} 条名句")
        
        time.sleep(2)  # 适当延迟防止被封
    
    print("爬取完成！结果已保存到 poems.txt")