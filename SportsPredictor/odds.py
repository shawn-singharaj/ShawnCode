from selenium import webdriver
from bs4 import BeautifulSoup
import time

url = "https://www.bettingpros.com/nba/props/deni-avdija/points/"

driver = webdriver.Chrome()  # or whichever driver you use
driver.get(url)
time.sleep(5)  # wait for JS to load content

html = driver.page_source
soup = BeautifulSoup(html, 'html.parser')

# for example, find all rows in the props table
rows = soup.select("table.props-table tbody tr")
for row in rows:
    cells = [td.get_text(strip=True) for td in row.find_all("td")]
    print(cells)

driver.quit()