#!/bin/sh
set -e

./ex17 db.dat c

./ex17 db.dat s 1 whg whg@163.com
./ex17 db.dat s 2 zxc zxc@163.com
./ex17 db.dat s 3 amy amy@163.com

./ex17 db.dat l