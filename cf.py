#!/usr/local/bin/python3

import CloudFlare
import sys

if (len(sys.argv) < 2):
  print("ERROR: CF API token required as first argument")
  a = 5
  print("Usage:" + )
  exit(1)

token = sys.argv[1]
cf = CloudFlare.CloudFlare(token=str(token))
zones = cf.zones.get(params = {'per_page':500})
for x in zones:
  print(x['name'])
