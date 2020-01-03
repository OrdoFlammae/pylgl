from pylgl_c import *


def read_cnf(cnf):
    result = []
    lines = cnf.split('\n')

    for line in lines[1:]:
        items = line.split()

        if len(items) > 1:
            result.append(items[:-1])

    return result
