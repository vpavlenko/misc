#!/usr/bin/env python3

import csv


def write_to_csv(filename, table):
    with open(filename, 'w', newline='') as output_file:
        output_writer = csv.writer(output_file)
        for row in table:
            output_writer.writerow(row)


def main():
    table = []
    for phi in range(0, 375, 15):
        table.append([phi, phi ** 2])
    write_to_csv('mytable.csv', table)


if __name__ == '__main__':
    main()
