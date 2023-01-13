from bs4 import BeautifulSoup as bs
import re
import urllib.request
from collections import deque
from django.core.validators import URLValidator
from django.core.exceptions import ValidationError
import concurrent
import multiprocessing as mp


def make_soup(url):
    validator = URLValidator()
    try:
        validator(url)
    except ValidationError:
        return -1

    try:
        page = urllib.request.urlopen(url)
    except urllib.request.HTTPError:
        return -1
    except UnicodeEncodeError:
        return -1

    request = urllib.request.Request(
        url, headers={'User-Agent': 'Chrome/83.0.4103.97'})
    try:
        page = urllib.request.urlopen(request).read()
    except UnicodeEncodeError:
        return -1

    return bs(page, 'html.parser')


def get_links(url):
    soup = make_soup(url)
    if soup == -1:
        return []

    return list(filter(lambda l: l is not None and len(l) > 0 and l.startswith('http'), [l.get('href') for l in soup.findAll('a')]))


def get_text(url):
    soup = make_soup(url)
    if soup == -1:
        return ""

    for noise in soup(["script", "style", "head", "meta"]):
        noise.decompose()
    return " ".join(list(soup.stripped_strings))


def crawl(start_page, distance, action):
    pages = set([start_page])
    all_pages = set([start_page])

    print('Getting links: ', flush=True)
    for _ in range(distance):
        current_pages = set()
        with concurrent.futures.ThreadPoolExecutor() as executor:
            current_pages = set(list(executor.map(get_links, pages))[0])
        pages = current_pages
        all_pages = all_pages.union(current_pages)

    pages = all_pages
    results = []

    print('Actioning: ', flush=True)
    with mp.Pool() as pool:
        parsed_pages = pool.map(get_text, pages)
        sentences = list(map(action, parsed_pages))
        results = list(zip(pages, sentences))

    return iter(results)


def sentence_with_python(text):
    sentences = re.split(r'(^[A-Za-z,;\'\"\s]+[.?!]\s*$")', text)
    sentences = [s.strip()
                 for s in filter(lambda x: x.find('Python') != -1, sentences)]
    return sentences


results = crawl(
    "https://en.wikipedia.org/wiki/Computer_programming", 1, sentence_with_python)

for url, sentences in results:
    if sentences:
        print(url, sentences)
