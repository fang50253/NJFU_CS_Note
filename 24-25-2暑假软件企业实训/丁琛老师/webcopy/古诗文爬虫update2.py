import requests
from bs4 import BeautifulSoup
import time

HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36',
    'Accept-Language': 'zh-CN,zh;q=0.9',
    'Referer': 'https://www.gushiwen.cn/'
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
    
    # 查找所有名句条目
    items = soup.find_all('div', class_='cont')
    
    for item in items:
        # 提取名句文本
        sentence = item.find('a').text.strip()
        # 提取出处链接
        href = item.find('a')['href']
        if not href.startswith('http'):
            href = 'https://www.gushiwen.cn' + href
        # 提取作者和出处
        source = item.find_all('a')[-1].text.strip()
        
        poems.append({
            'sentence': sentence,
            'source': source,
            'url': href
        })
    
    return poems

def save_to_file(poems, filename='poems.txt'):
    with open(filename, 'a', encoding='utf-8') as f:
        for poem in poems:
            f.write(f"名句: {poem['sentence']}\n")
            f.write(f"出处: {poem['source']}\n")
            f.write(f"链接: {poem['url']}\n\n")

if __name__ == '__main__':
    base_url = 'https://www.gushiwen.cn/mingjus/default.aspx?page={}'
    
    for page in range(1, 10000):  # 爬取前2页
        url = base_url.format(page)
        print(f"正在爬取第 {page} 页: {url}")
        
        html = page_request(url)
        if html:
            poems = page_parse(html)
            save_to_file(poems)
            print(f"第 {page} 页爬取完成，共 {len(poems)} 条名句")
        
        time.sleep(2)  # 适当延迟防止被封
    
    print("爬取完成！结果已保存到 poems.txt")