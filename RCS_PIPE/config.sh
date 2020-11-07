#!/bin/bash
FW4GPID="UART/debug/bin/4GPID"
UART="uartDriver/debug/bin/usart"


make -C UART/

if [ -e "$FW4GPID" ] 
then
    if [ ! -x "$FW4GPID" ]
    then
        chmod u+x $FW4GPID
    fi
    mv UART/debug/bin/4GPID ./bin
else
    exit 1
fi

make -C uartDriver/


if [ -e "$UART" ]
then
    if [ ! -x "$UART"  ]
    then
        chmod u+x $UART
    fi

    mv uartDriver/debug/bin/usart ./bin
else
    exit 1
fi

cp bin ~/nfs -r
#./bin/4GPID
