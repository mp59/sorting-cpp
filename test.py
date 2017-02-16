import subprocess
import argparse
from collections import namedtuple
from concurrent.futures import ThreadPoolExecutor as Pool
import queue
from threading import Thread

TestResult = namedtuple('TestResults', ['output', 'passed'])

def limited_print_manager(print_queue, runs):
    for i in range(runs):
        message = print_queue.get()
        print(message)
        print_queue.task_done()

class BaseTest(object):

    def __init__(self, runs, concurrent=True, verbose=False):
        self.runs = runs
        self.passed_runs = 0
        self.concurrent = concurrent
        self.verbose = verbose
        self._print_queue = queue.Queue()
        if verbose:
            printer_thread = Thread(target=limited_print_manager,
                args=(self._print_queue, self.runs))
            printer_thread.start()
        if concurrent:
            with Pool() as pool:
                self.results = list(pool.map(
                    lambda _: self.process_run(),
                    range(self.runs)
                    ))
        else:
            self.results = [self.process_run() for i in range(self.runs)]
        if verbose:
            printer_thread.join()
        self.passed = self.passed_runs >= self.runs

    def process_run(self):
        result = self.run()
        if self.verbose:
            self._print_queue.put(result.output)
        if result.passed:
            self.passed_runs += 1
        return result

    def run(self):
        """Returns TestResult object"""
        pass

    def print_outcome(self):
        print('{}/{} runs passed'.format(self.passed_runs, self.runs))

    def print_failed_output(self):
        for result in (r for r in self.results if not r.passed):
            print(result.output)

class SortingTest(BaseTest):

    def __init__(self, runs, concurrent=True, verbose=False):
        subprocess.run('make')
        print('\n', end='')
        super().__init__(runs, concurrent, verbose)

    def run(self):
        output = subprocess.check_output('./main').decode()
        output_list = list(map(int, output.split()))
        passed = self.is_list_sorted(output_list)
        result = TestResult(output=output, passed=passed)
        return result

    @staticmethod
    def is_list_sorted(sorted_list):
        for lower, higher in zip(sorted_list[:-1], sorted_list[1:]):
            if lower > higher:
                return False
        return True

def create_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('runs', type=int, default=100, nargs='?')
    parser.add_argument('-v', '--verbose', action='store_true')
    parser.add_argument('-n', '--non-concurrent', dest='concurrent', action='store_false')
    return parser

def main():
    args = create_parser().parse_args()
    test = SortingTest(runs=args.runs, concurrent=args.concurrent, verbose=args.verbose)
    if not test.passed:
        test.print_failed_output()
    test.print_outcome()

if __name__ == '__main__':
    main()
