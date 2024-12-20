#!/bin/bash

#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 

if [ "$1" = "-d" ]; then 
    qemu-system-x86_64 -s -S -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=audio0 -machine pcspk-audiodev=audio0
else 
    qemu-system-x86_64 -audiodev pa,id=foo -hda Image/x64BareBonesImage.qcow2 -m 512 -machine pcspk-audiodev=foo 
fi 
