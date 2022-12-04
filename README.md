# GTFS evaluation

Runs a simulation of people traveling in a transport network specified as GTFS feed.
Computes "total time spent in transit" for a provided travel profile.
This effectively evaluates "performance" of the transportation network and allows
to compare 2 networks in a **fair** way.

## Travel profile

File that contains a sample(or aggregate) of trips that people are making
throughout the day.

Format is a simple CSV that follows this schema:

| Column      | Type             | Description |
| ----------- |------------------| ----------- |
| From        | String           | Start stop  |
| To          | String           | Final stop  |
| When        | Timestamp (UNIX) | Start time  |

> TODO: Consider adding a field for number of people that travelled.
> Allows for more compact representation of aggregate information.

### Example

Unfortunately, there's no publicly available people travel profile.
There are potential privacy issues associated with releasing even de-anonymized
aggregate information. [Differential-privacy][diff-privacy] is very hard to
achive for this use-case.

Having said that, many public transportation providers require people to use
company-issued cards (eg. [ORCA][orca], [Clipper][clipper] cards).
It's fairly easy to design a way to collect an aggregate data internaly based
on the information tracked by these cards.

As an example we've generated 10K random trips uniformly sampled from the GTFS
feed for [Linz, Austria][linz].

See `profile.csv` in the current repo:

```
$ head profile.csv

at:44:41339:0,at:44:41307:0,1669863600
at:44:41357:0,at:44:41150:0,1669935600
at:44:41474:0,at:44:41143:0,1669878000
at:44:40144:0,at:44:41156:0,1669863600
at:44:41470:0,at:44:41003:0,1669903200
at:44:41073:0,at:44:42598:0,1669863600
at:44:41162:0,at:44:41185:0,1669888800
at:44:41852:0,at:44:40252:0,1669870800
at:44:41234:0,at:44:41110:0,1669852800
at:44:41164:0,at:44:41056:0,1669878000
```

## How to run?

Tool is composed of 2 parts:
* `transform.py` - Python script that transforms GTFS feed data into low-level
  schedule data.
* `sim` - Routing simulator written in C++ that uses schedule data and travel
  profile to calculate resulting performance metric.
  
### GTFS Feed to schedule

Transformation tool consumes a valid GTFS feed and produced a _schedule_.
Which is a low-level joined representation of all the edges in the dynamic
routing graph.

Here are all the flags supported by the transformation tool:

```
usage: transform.py [-h] [--gtfs GTFS] [-o OUTPUT]

options:
  -h, --help            show this help message and exit
  --gtfs GTFS           path to the folder containing GTFS feed data
  -o OUTPUT, --output OUTPUT
                        where to put output schedule
```

Output is a CSV file that follows a simple schema:

| Column      | Type             | Description    |
| ----------- |------------------| ---------------|
| From        | String           | Start stop     |
| To          | String           | Final stop     |
| Departure   | Timestamp (UNIX) | Departure time |
| Arrival     | Timestamp (UNIX) | Arrival time   |

#### Example

As an example we'll use a GTFS feed for public transportation in
[Linz, Austria][linz]. It is checked in as part of this repo (see `linz`).

```
$ ./transform.py --gtfs=linz -o sched.csv
$ head sched.csv

at:44:40002:0,at:44:41126:0,1669868160,1669868220
at:44:40002:0,at:44:41126:0,1669869900,1669869960
at:44:40002:0,at:44:41126:0,1669870020,1669870080
at:44:40002:0,at:44:41126:0,1669870260,1669870320
at:44:40002:0,at:44:41126:0,1669870860,1669870920
at:44:40002:0,at:44:41126:0,1669872180,1669872240
at:44:40002:0,at:44:41126:0,1669873020,1669873080
at:44:40002:0,at:44:41126:0,1669873620,1669873680
at:44:40002:0,at:44:41126:0,1669873680,1669873740
at:44:40002:0,at:44:41126:0,1669874400,1669874520
```

[diff-privacy]: https://en.wikipedia.org/wiki/Differential_privacy
[linz]: https://en.wikipedia.org/wiki/Linz
[orca]: https://www.myorca.com
[clipper]: https://www.clippercard.com
