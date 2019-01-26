#!/bin/bash
freeloop=$(losetup -f)
echo "The first free loop device is $freeloop"
echo $freeloop > active_loopdevice.txt
losetup -f ./loopdevfile.img
mkdir mountpoint
mount $freeloop ./mountpoint

