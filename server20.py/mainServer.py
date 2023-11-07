#!/usr/bin/env python
# -*- coding: utf-8 -*-
from rpc_en_cli import ConsolaCLI

if __name__ == '__main__':
    uncli = ConsolaCLI()
    uncli.prompt = '>>'
    #ejcuto do_help para mostrar la lista de comandos disponibles
    uncli.do_listCom(None)
    uncli.cmdloop('Iniciando entrada de comandos...')
