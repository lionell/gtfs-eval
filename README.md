# GTFS evaluation

Runs a simulation of people traveling in a transport network specified as GTFS feed.
Computes "total time spent in transit" for a provided travel profile.
This effectively evaluates "performance" of the transportation network and allows
to compare 2 networks in a **fair** way.

### Travel profile

File that contains a sample(or aggregate) of trips that people are making
throughout the day.

Format is very simple and follows this schema:

| Column      |    Type          | Description |
| ----------- |------------------| ----------- |
| From        | String           | Start stop  |
| To          | String           | Final stop  |
| When        | Timestamp (UNIX) | Start time  |

> TODO: Consider adding a field for number of people that travelled.
> Allows for more compact representation of aggregate information.

#### Example

Unfortunately, there's no publicly available people travel profile.
There are potential privacy issues associated with releasing even de-anonymized
aggregate information. [Differential-privacy][diff-privacy] is very hard to
achive for this use-case.

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

[diff-privacy]: https://en.wikipedia.org/wiki/Differential_privacy
[linz]: https://en.wikipedia.org/wiki/Linz
