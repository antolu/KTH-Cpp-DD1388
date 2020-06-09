#!/usr/bin/env python3
from argparse import ArgumentParser
from pprint import pformat
from os import path

def main(args):
    if not path.exists(args.in_file):
        raise ValueError(f'In file at {args.in_file} does not exist')

    with open(args.in_file, 'r') as f:
        data = f.readlines()

    data = [l.strip() for l in data]  # remove lingering whitespace

    out = list()

    names = dict()
    it = iter(data)
    while True:
        try:
            line = next(it)
            if line.startswith('#'):
                continue

            if line.startswith('test'):
                d = {
                    'board': list(),
                    'tests': {
                    'white_capturing_moves': 0,
                    'black_capturing_moves': 0,
                    'white_noncapturing_moves': 0,
                    'black_noncapturing_moves': 0,
                    }
                }

                _, name = line.split(':')
                if ',' in name:
                    name, sub_name = line.split(',')
                else:
                    sub_name = ""

                name = name.lower()
                sub_name = sub_name.lower()
                if name not in names:
                    names[name] = 1
                else:
                    names[name] += 1

                d['name'] = name
                if sub_name != "":
                    d['sub_name'] = sub_name
                else:
                    d['sub_name'] = names[name]

                for i in range(8):
                    board_line = next(it)
                    if len(board_line) != 8:
                        raise ValueError('Not enough lines to parse a check board')

                    d['board'].append(board_line)

                out.append(d)

            elif line.startswith('w_capt'):
                _, out[-1]['tests']['white_capturing_moves'] = line.split(' ')
            elif line.startswith('b_capt'):
                _, out[-1]['tests']['black_capturing_moves'] = line.split(' ')
            elif line.startswith('w_ncapt'):
                _, out[-1]['tests']['white_noncapturing_moves'] = line.split(' ')
            elif line.startswith('b_ncapt'):
                _, out[-1]['tests']['black_noncapturing_moves'] = line.split(' ')
        except StopIteration:
            break

    print('Parsed file:')
    print(pformat(out))


    if path.exists(args.out_file):
        prompt = input(f'The file at {args.out_file} will be overwritten. Confirm (y/n): ')
        if prompt.lower() != 'y':
            print('Leaving destination file as-is. Exiting.')
            exit(0)

    with open(args.out_file, 'w') as f:
        write = lambda line="": f.write(line + '\n')
        write('#include <gtest/gtest.h>\n')
        write('#include <iostream>')
        write('#include "string"')
        write()
        write('#include "chesspiece.hpp"')
        write('#include "chessboard.hpp"')
        write('#include "chessmove.hpp"')
        write()

        for test in out:
            write(f'TEST({test["name"]}, {test["sub_name"]}) {{')
            write('\tChessBoard chess;')
            write('\tstd::stringstream s;')
            for b in test['board']:
                write(f'\ts << "{b}" << std::endl;')
            write('\ts >> chess;')

            written_tests = list()
            for test_type, n in test['tests'].items():
                if int(n) != 0:
                    if test_type == 'white_capturing_moves':
                        write(f'\tstd::vector<ChessMove> {test_type} = chess.capturingMoves(true);')
                    elif test_type == 'black_capturing_moves':
                        write(f'\tstd::vector<ChessMove> {test_type} = chess.capturingMoves(false);')
                    elif test_type == 'white_noncapturing_moves':
                        write(f'\tstd::vector<ChessMove> {test_type} = chess.nonCapturingMoves(true);')
                    elif test_type == 'black_noncapturing_moves':
                        write(f'\tstd::vector<ChessMove> {test_type} = chess.nonCapturingMoves(false);')
                    written_tests.append((test_type, n))

            write()
            if args.print_board:
                write('\tstd::cout << chess << std::endl;\n')
            for test_type in written_tests:
                write(f'\tEXPECT_EQ( {test_type[0]}.size(), {test_type[1]} );')
            write('}\n')

    print('Written all tests (yay!)')


if __name__ == '__main__':
    parser = ArgumentParser()

    parser.add_argument('-i', '--in-file', dest='in_file', type=str, required=True, help='The text file containing all the board tests.')
    parser.add_argument('-o', '--out-file', dest='out_file', type=str, required=True, help='The c++ source file to write the tests to. This file will be overwritten.')
    parser.add_argument('-p', '--print-board', dest='print_board', action='store_true', help='Print the board at each test')

    args = parser.parse_args()
    print('Parsed arguments:\n')
    print(pformat(args.__dict__))

    main(args)