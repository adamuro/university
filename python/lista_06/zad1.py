import re
from threading import Thread
from urllib.request import urlopen

class Crawler(Thread):
  def __init__(self, page, distance, action):
    self.page = page
    self.distance = distance
    self.action = action
    Thread.__init__(self)

  def run(self):
    response = urlopen(self.page)
    html = response.read()
    # print(html)
    # text = html.decode('utf8')
    links = re.findall("href=[\"\'](.*?)[\"\']", html)
    # print(links[:5])

crawler = Crawler("http://kite.com", None, None)
crawler.start()
