from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from bs4 import BeautifulSoup
import time
import json
import random
from tqdm import tqdm

# 配置参数
BASE_URL = "https://so.gushiwen.cn"
DELAY = (0, 0)  # 随机延迟范围
PAGES = 10  # 爬取页数

def init_driver():
    """初始化浏览器"""
    options = Options()
    options.add_argument("user-agent=Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36")
    options.add_argument("--disable-blink-features=AutomationControlled")
    options.add_experimental_option("excludeSwitches", ["enable-automation"])
    options.add_experimental_option("useAutomationExtension", False)
    
    driver = webdriver.Chrome(options=options)
    driver.execute_cdp_cmd("Page.addScriptToEvaluateOnNewDocument", {
        "source": """
        Object.defineProperty(navigator, 'webdriver', {
            get: () => undefined
        })
        """
    })
    return driver

def parse_main_page(driver):
    """解析主页面获取名句和链接"""
    WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.CSS_SELECTOR, "div.sons div.cont"))
    )
    soup = BeautifulSoup(driver.page_source, 'lxml')
    
    href_list = []
    sentence_list = []
    
    for item in soup.select('div.sons div.cont'):
        try:
            # 提取名句文本
            text = ' '.join(item.get_text().strip().split())
            
            # 提取详情页链接
            link = item.find('a', href=True)
            if link and link['href'].startswith('/shiwenv'):
                href_list.append(BASE_URL + link['href'])
                sentence_list.append(text)
        except Exception as e:
            print(f"解析条目出错: {str(e)}")
    
    return href_list, sentence_list

def parse_poem_page(driver, url):
    """解析诗词详情页"""
    driver.get(url)
    time.sleep(random.uniform(*DELAY))
    
    try:
        WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.CSS_SELECTOR, "div.contson"))
        )
        soup = BeautifulSoup(driver.page_source, 'lxml')
        poem = soup.select_one('div.contson')
        return poem.get_text().strip() if poem else ""
    except:
        return ""

def save_data(filename, data):
    """保存数据到文件"""
    with open(filename, 'a', encoding='utf-8') as f:
        for item in data:
            f.write(json.dumps(item, ensure_ascii=False) + '\n\n')

def main():
    print("**************开始爬取古诗文网站********************")
    driver = init_driver()
    
    all_sentences = []
    all_poems = []
    
    try:
        for page in tqdm(range(1, PAGES+1), desc="爬取进度"):
            url = f'{BASE_URL}/mingjus/default.aspx?page={page}'
            print(f"\n正在处理: {url}")
            
            # 获取列表页
            driver.get(url)
            time.sleep(random.uniform(*DELAY))
            
            # 解析名句和链接
            href_list, sentence_list = parse_main_page(driver)
            all_sentences.extend(sentence_list)
            
            # 获取每个名句的详情页
            for href in tqdm(href_list, desc=f"第{page}页名句", leave=False):
                poem = parse_poem_page(driver, href)
                if poem:
                    all_poems.append(poem)
            
            # 每页保存一次
            save_data('sentence.txt', sentence_list)
            save_data('poems.txt', all_poems[-len(href_list):])
        
        print("\n****************爬取完成***********************")
        print(f"共爬取{len(all_sentences)}个古诗词名句")
        print(f"共爬取{len(all_poems)}个古诗词")
    
    finally:
        driver.quit()

if __name__ == '__main__':
    main()