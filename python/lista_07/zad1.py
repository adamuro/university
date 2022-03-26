import re
from threading import Lock, Thread
from typing import Set
from urllib.request import urlopen
from html2text import html2text

lock = Lock()
python_sentences = []

class Crawler(Thread):
  def __init__(self, page, distance, action):
    self.page = page
    self.distance = distance
    self.action = action
    Thread.__init__(self)

  visited = set()

  def run(self):
    if (self.distance <= 0):
      return

    try:
      response = urlopen(self.page)
      html = response.read()
      html_decoded = html.decode('utf8')
      text = html2text(html_decoded)
      text.replace('!', '.')
      text.replace('?', '.')
      text.replace('\n', '.')
      
      global lock
      lock.acquire()
      self.action(text)
      lock.release()
    except:
      return


    Crawler.visited.add(self.page)
    pages = re.findall("href=[\"\'](.*?)[\"\']", html_decoded)
    crawlers = []

    for page in pages:
      if page not in Crawler.visited:
        crawlers.append(Crawler(page, self.distance - 1, self.action))
    for crawler in crawlers:
      crawler.start()
    for crawler in crawlers:
      crawler.join()

def findSentencesWithPython(text):
  sentences = text.split('.')

  for sentence in sentences:
    if 'python' in sentence.lower():
      python_sentences.append(sentence)

crawler = Crawler('https://www.w3schools.com/python/default.asp', 2, findSentencesWithPython)
crawler.start()
crawler.join()

print("python sentences: " + str(python_sentences[:10]))
print("\nvisited pages: " + str(Crawler.visited))
