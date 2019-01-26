#!/bin/bash
umount ./mountpoint
rm -rf ./mountpoint
active_loopdevice=$(head -n 1 active_loopdevice.txt)
losetup -d $active_loopdevice
rm active_loopdevice.txt

