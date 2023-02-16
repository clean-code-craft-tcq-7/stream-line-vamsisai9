import csv
import sys

def send_data_from_csv(filename: str) -> None:
    with open(filename, newline='') as f:
        reader = csv.reader(f)
        headers = next(reader)
        sys.stdout.write(','.join(headers) + '\n')
        sys.stdout.flush()
        for row in reader:
            sys.stdout.write(','.join(row) + '\n')
            sys.stdout.flush()
