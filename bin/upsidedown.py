#!/usr/bin/env python3
"""Send serial messages to AVR from the Upside Down."""

import argparse
import json
import random
import re
import serial
import serial.tools.list_ports as list_ports
import sys
import time

BAUD = 9600  # serial port baud rate

# random messages selected from:
MESSAGES = ["barb", "boo", "halloween", "help", "redrum", "run", "trick or treat"]

NTRUNC = 32

def clean(tweet):
    """Clean tweet of special characters, hash tags, user names, etc."""

    words = []
    for w in re.split(r"\s+", tweet):
        if w[:4] == "http" or w[0] in ["@", "#"]:
            continue

        words.append(w.strip().lower())

    message = re.sub(r"[^a-z ]", "", " ".join(words))
    message = re.sub(r"\s+", " ", message)

    return message.strip()

def comport():
    """Default serial device."""

    try:
        port = list_ports.comports()[0].device
    except IndexError:
        port = None

    return port

def parse(results, userfile):
    """Parse Twitter search results from twurl."""

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

def ports():
    """Display a list of available serial ports."""

    labels = ("Device", "Description")
    header = "{0:40}{1:30}".format(*labels)

    print(header)
    print("-"*len(header))
    for port in list_ports.comports():
        print("{0.device:40}{0.description:30}".format(port))

def send(port, message):
    """Send message to serial port."""

    message = message[:NTRUNC]
    delay = 2*len(message)  # delay (in sec) to wait for message to display

    print("send: '{}' ({} s)".format(message, delay))
    port.write("{}\r\n".format(message).encode("utf-8"))
    time.sleep(delay)

if __name__ == "__main__":
    p = argparse.ArgumentParser(prog="upsidedown.py", description=__doc__)
    p.add_argument("-b", "--baud", dest="baud", type=int, default=9600,
                   help="Baud rate")
    p.add_argument("-d", "--device", dest="device", type=str,
                   default=comport(), help="Serial port device")
    p.add_argument("-i", "--id", dest="idfile", type=str,
                   help="Filename to store latest tweet ID")
    p.add_argument("-l", "--list", dest="list", action="store_true",
                   help="List available serial port devices and exit")
    p.add_argument("-t", "--twitter", dest="twitter", action="store_true",
                   help="Parse tweets from Twitter API")
    p.add_argument("-u", dest="userfile", type=str,
                   help="Filename to store Twitter user names")
    p.add_argument(dest="message", nargs="*", type=str,
                   help="Message to display")

    args = p.parse_args()

    if args.list:
        ports()
        sys.exit(0)
    elif args.twitter:
        results = json.load(sys.stdin)
        userfile = open(args.userfile, "a") if args.userfile else None
        messages, since_id = parse(results, userfile)

        if args.idfile and since_id > 0:
            with open(args.idfile, "w") as fp:
                fp.write("{}".format(since_id))
    elif args.message:
        messages = [re.sub(r"[^~a-z ]", "", " ".join(args.message))]
    else:
        messages = [random.choice(MESSAGES)]

    with serial.Serial(args.device, args.baud, timeout=5) as port:
        if not messages:
            r = random.random()
            if r < 0.6:
                print("flash")
                port.write("~\r\n".encode("utf-8"))
            else:
                send(port, random.choice(MESSAGES))
        else:
            for msg in messages:
                send(port, msg)
