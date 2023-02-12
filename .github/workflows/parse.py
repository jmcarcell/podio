import re
import sys
import json
import requests

URL_PATTERN = r'https?:\/\/(?:www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&//=]*)'

# text = sys.argv[1]
text = """blablablablaaoeu aoeuh assoehu saoetu hasoeuh 
important pRPRP this is atoeut haetu.
asaeu depends on https://github.com/jmcarcell/k4FWCore/pull/1"""

# print('Parsing text in the PR to find other branches that will be compiled together...')
res = re.search(f'[dD]epends +(?:on)? *{URL_PATTERN}', text)
if not res:
    print('No linked PRs could be found, the current branch will be compiled with the master branches of other packages')
    exit()
# print(res.groups())
for group in res.groups():
    ls = group.split('/')
    owner = ls[1]
    repo = ls[2]
    number = ls[4]
    response = requests.get(f'https://api.github.com/repos/{owner}/{repo}/pulls/{number}')
    js = response.json()
    _, branch = js['head']['label'].split(':')
    print(owner, repo, branch)
    print(owner, repo, branch)
