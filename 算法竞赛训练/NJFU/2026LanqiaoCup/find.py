import requests
import pandas as pd
import time

def fetch_lanqiao_data(total_pages=1858):
    base_url = "https://dasai.lanqiao.cn/core/publicitySetting/getAwardList"
    all_records = []
    
    # 设置请求头，模拟浏览器访问，防止被拦截
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
        "Referer": "https://dasai.lanqiao.cn/"
    }

    print(f"开始抓取数据，共 {total_pages} 页...")

    for page in range(1, total_pages + 1):
        params = {
            "itemId": 1001,
            "current": page,
            "size": 20,
            "publicityCategoryId": 1,
            "publicityMatchName": "软件赛省赛"
        }
        
        try:
            response = requests.get(base_url, params=params, headers=headers, timeout=10)
            if response.status_code == 200:
                data = response.json()
                records = data.get("data", {}).get("records", [])
                all_records.extend(records)
                
                if page % 50 == 0:
                    print(f"已完成 {page}/{total_pages} 页抓取...")
            else:
                print(f"第 {page} 页请求失败，状态码: {response.status_code}")
        except Exception as e:
            print(f"第 {page} 页发生错误: {e}")
        
        # 适当休眠，避免给服务器造成过大压力
        # time.sleep(0.1)

    # 1. 转换为 DataFrame
    df = pd.DataFrame(all_records)

    # 2. 保存为 CSV
    csv_filename = "lanqiao_award_list.csv"
    df.to_csv(csv_filename, index=False, encoding="utf-8-sig")
    print(f"\n所有数据已保存至: {csv_filename}")

    # 3. 统计各组一二三等奖人数
    # 我们只统计“一等奖”、“二等奖”、“三等奖”，过滤掉其他可能的类型
    target_awards = ["一等奖", "二等奖", "三等奖"]
    stats = df[df['awardsGrade'].isin(target_awards)].groupby(['itemNameGroup', 'awardsGrade']).size().unstack(fill_value=0)
    
    # 调整列顺序
    stats = stats.reindex(columns=target_awards)
    
    # 添加总计列
    stats['总计'] = stats.sum(axis=1)
    
    print("\n--- 各组别获奖人数统计 ---")
    print(stats)
    
    # 将统计结果也保存为 CSV
    stats.to_csv("award_statistics.csv", encoding="utf-8-sig")
    print("\n统计结果已保存至: award_statistics.csv")

if __name__ == "__main__":
    fetch_lanqiao_data(total_pages=1858)