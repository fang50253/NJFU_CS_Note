#crawl_poem.py
import requests
from bs4 import BeautifulSoup
import time
# 更新为更完整的headers
HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Language': 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
    'Accept-Encoding': 'gzip, deflate, br',
    'Connection': 'keep-alive',
    'Upgrade-Insecure-Requests': '1',
    'Sec-Fetch-Dest': 'document',
    'Sec-Fetch-Mode': 'navigate',
    'Sec-Fetch-Site': 'none',
    'Sec-Fetch-User': '?1',
    'Cache-Control': 'max-age=0'
}
# 函数1：请求网页
def page_request(url, headers=HEADERS):
    try:
        response = requests.get(url, headers=headers, timeout=10)
        print(f"状态码: {response.status_code}")
        print(f"内容长度: {len(response.text)}")
        print(f"实际URL: {response.url}")  # 检查是否被重定向
        print("响应头:", response.headers)
        
        # 保存响应内容供检查
        with open("response.html", "w", encoding="utf-8") as f:
            f.write(response.text)
            
        return response.text
    except Exception as e:
        print(f"请求出错: {e}")
        return None
# 函数2：解析网页
def page_parse(html):
    soup = BeautifulSoup(html, 'lxml')
    title = soup('title')
    # 诗句内容：诗句+出处+链接
    info = soup.select('body > div.main3 > div.left > div.sons > div.cont')
    # 诗句链接
    sentence = soup.select('div.left > div.sons > div.cont > a:nth-of-type(1)')
    sentence_list = []
    href_list = []
    for i in range(len(info)):
        curInfo = info[i]
        poemInfo = ''
        poemInfo = poemInfo.join(curInfo.get_text().split('\n'))
        sentence_list.append(poemInfo)
        href = sentence[i].get('href')
        href_list.append("https://so.gushiwen.org" + href)
    return [href_list, sentence_list]
def save_txt(info_list):
    import json
    with open(r'sentence.txt', 'a', encoding='utf-8') as txt_file:
        for element in info_list[1]:
            txt_file.write(json.dumps(element, ensure_ascii=False) + '\n\n')
# 子网页处理函数：进入并解析子网页/请求子网页
def sub_page_request(info_list):
    subpage_urls = info_list[0]
    ua = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.86 Safari/537.36'}
    sub_html = []
    for url in subpage_urls:
        html = page_request(url, ua)
        sub_html.append(html)
    return sub_html
# 子网页处理函数：解析子网页，爬取诗句内容
def sub_page_parse(sub_html):
    poem_list = []
    for html in sub_html:
        soup = BeautifulSoup(html, 'lxml')
        poem = soup.select('div.left > div.sons > div.cont > div.contson')
        if len(poem) == 0:
            continue
        poem = poem[0].get_text()
        poem_list.append(poem.strip())
    return poem_list
# 子网页处理函数：保存诗句到txt
def sub_page_save(poem_list):
    import json
    with open(r'poems.txt', 'a', encoding='utf-8') as txt_file:
        for element in poem_list:
            txt_file.write(json.dumps(element, ensure_ascii=False) + '\n\n')
if __name__ == '__main__':
    print("**************开始爬取古诗文网站********************")
    ua = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.86 Safari/537.36'}
    poemCount = 0
    for i in range(1, 3):  # 一共爬取2页
        url = 'https://so.gushiwen.cn/mingjus/default.aspx?page=%d' % i
        print(url)
        html = page_request(url, ua)
        info_list = page_parse(html)
        save_txt(info_list)
        # 开始处理子网页
        print("开始解析第%d" % i + "页")
        # 开始解析名句子网页
        sub_html = sub_page_request(info_list)
        poem_list = sub_page_parse(sub_html)
        sub_page_save(poem_list)
        poemCount += len(info_list[0])
    print("****************爬取完成***********************")
    print("共爬取%d" % poemCount + "个古诗词名句")
    print("共爬取%d" % poemCount + "个古诗词")
