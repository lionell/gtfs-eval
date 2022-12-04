#!/usr/bin/env python3

import pandas as pd

from os import path
from argparse import ArgumentParser

def canonicalize_stop_id(stop_id):
    return stop_id[:stop_id.rfind(':')]

def parse_time(time):
    if time.startswith('24'):
        return int(pd.to_datetime('2022-12-02 00' + time[2:], utc=True).timestamp())
    return int(pd.to_datetime('2022-12-01 ' + time, utc=True).timestamp())

if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('--gtfs', help='path to the folder containing GTFS feed data', default='linz')
    parser.add_argument('-o', '--output', help='where to put output schedule', default='sched.csv')
    args = parser.parse_args()

    calendar = pd.read_csv(path.join(args.gtfs, 'calendar.txt'))
    calendar = calendar.drop(columns=['start_date',  'end_date'])

    trips = pd.read_csv(path.join(args.gtfs, 'trips.txt'))
    trips = trips[['service_id', 'trip_id']]

    stop_times = pd.read_csv(path.join(args.gtfs, 'stop_times.txt'))
    stop_times = stop_times[['trip_id', 'arrival_time', 'departure_time', 'stop_id', 'stop_sequence']]

    # NOTE! This is a heuristic that works for GTFS feed of Linz, Austria.
    # Stops have IDs like 'at:44:42589:0:1:0' and 2 stops are close nearby
    # if their IDs differ only in the last part(eg. ':0', ':1', etc).
    #
    # Doign this leads to a 60% decrease in the number of stops and describes a
    # real-world phenomenon of people walking in between stops to make a layover.
    stop_times = stop_times.assign(stop_id=stop_times['stop_id'].apply(canonicalize_stop_id))

    data = pd.merge(stop_times, trips, on='trip_id')
    data = pd.merge(data, calendar, on='service_id')

    day = data[data['wednesday'] == 1]
    day = day[['trip_id', 'arrival_time', 'departure_time', 'stop_id', 'stop_sequence']]

    grp = day.groupby('trip_id')
    day = day.assign(
        next_arrival_time=grp['arrival_time'].shift(-1),
        next_stop_id=grp['stop_id'].shift(-1)
    )
    day = day.dropna()

    sched = pd.DataFrame({
        'from': day['stop_id'],
        'to': day['next_stop_id'],
        'departure': day['departure_time'],
        'arrival': day['next_arrival_time'],
    })
    sched = sched.drop_duplicates()
    sched = sched.sort_values(by=list(sched.columns))

    sched = sched.assign(departure=sched['departure'].apply(parse_time),
                        arrival=sched['arrival'].apply(parse_time))
    sched.to_csv(args.output, header=False, index=False)
