# Timestamp Generator

Utility to generate a timestamp from current time

```
NAME
timestamp_generator - generates timestamp from current time

SYNOPSIS
./timestamp_generator [-p | --precision <PRECISION>] [-d | --padding]

DESCRIPTION
timestamp_generator is an utility to generate a timestamp from current time in various precision and format. The generation is performed in a threa-safe manner.

OPTIONS
       -p, --precision
           Sets the precision of the timestamp. Can be one of: year, month, day, hour, minute, second, millisecond, microsecond, nanosecond.

       -d, --padding
           When present, this option pads the suffix after seconds with zeros '0' from left, to maintain a fixed-length format.
```

Note: Options are not implemented yet.
