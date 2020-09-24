#!/bin/bash
cd uartDriver
make
cd ../UserInterface
make
cd ../
gdbserver localhost:1234 UserInterface/UserInterface 123
