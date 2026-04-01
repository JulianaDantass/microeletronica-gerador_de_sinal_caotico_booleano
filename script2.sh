#!/bin/bash

export MBK_IN_LO=vst
export MBK_OUT_LO=vst

genlib -v caos

alliance-ocp gerador_caos caos_posicionado

nero -p caos_posicionado gerador_caos caos_roteado

export MBK_OUT_LO=spi

cougar -t -ac caos_roteado
