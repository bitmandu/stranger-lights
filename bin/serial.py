#!/usr/bin/env python3
"""Send serial messages to AVR."""

import argparse
import json
import random
import re
import sys

MESSAGES = ["run", "help", "pumpkin", "halloween", "trick or treat", "boo"]

def clean(tweet):
    """Clean tweet of special characters and links."""

    words = []
    for w in re.split(r"\s+", tweet):
        if w[:4] == "http":
            continue

        words.append(w.strip().lower())

    message = re.sub(r"[^a-z ]", "", " ".join(words))
    return message

def parse(results, userfile):
    """Parse Twitter search results."""

    since_id = 0
    messages = []

    for tweet in results["statuses"]:
        if tweet["id"] > since_id:
            since_id = tweet["id"]

        messages.append(clean(tweet["text"]))

        if userfile:
            screen_name = tweet["user"]["screen_name"]
            userfile.write("https://twitter.com/{}\n".format(screen_name))

    return messages, since_id

if __name__ == "__main__":
    p = argparse.ArgumentParser(prog="serial.py", description=__doc__)
    p.add_argument("-l", dest="logfile", type=str,
                   help="Log filename (stores latest tweet ID)")
    p.add_argument("-t", "--twitter", dest="twitter", action="store_true",
                   help="Parse tweets from twurl")
    p.add_argument("-u", dest="userfile", type=str,
                   help="Filename to store Twitter user names")
    p.add_argument(dest="message", nargs="*", type=str,
                   help="Message to display")

    args = p.parse_args()

    if args.twitter:
        results = json.load(sys.stdin)
        userfile = open(args.userfile, "a") if args.userfile else None
        messages, since_id = parse(results, userfile)

        if args.logfile and since_id > 0:
            with open(args.logfile, "w") as fp:
                fp.write("{}".format(since_id))
    elif args.message:
        messages = [re.sub(r"[^a-z ]", "", " ".join(args.message))]
    else:
        messages = [random.choice(MESSAGES)]

    for m in messages:
        print("send: '{}'".format(m))
        #send(m)
