import subprocess
import argparse

def is_list_sorted(sorted_list):
    for lower, higher in zip(sorted_list[:-1], sorted_list[1:]):
        if lower > higher:
            return False
    return True

def check_output(runs, verbose=False):
    traceback = ''
    correct = 0
    for i in range(runs):
        out = subprocess.check_output('./main').decode()
        if verbose:
            print(out)
        out_list = list(map(int, out.split()))
        if is_list_sorted(out_list):
            correct += 1
        else:
            traceback += out + '\n'
    if traceback:
        print('Output from failed runs:')
        print(traceback, end='')
    print('{}/{} correct'.format(correct, runs))

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('runs', type=int, default=10, nargs='?')
    parser.add_argument('-v', '--verbose', action='store_true')
    args = parser.parse_args()
    subprocess.run('make')
    print('')
    check_output(args.runs, args.verbose)

if __name__ == '__main__':
    main()
