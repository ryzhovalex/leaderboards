# Leaderboards
Simple leaderboard API for games.

## Usage
See client.py for examples.

## API
We use codes and [lithium message structure](httsp://github.com/slimebones/lithium). Code is a 16-bit integer. As soon as you connected, you can send any available starts, and receive back reacts.

Start message format: `<code>;<body_0>;<body_1>;<body...>;<body_n>`
React message format: `<start_code>;<body_0>;<body_1>;<body...>;<body_n>`

By knowing start codes, you know start and react body structures, since there are single defined react body structure per start code.

Both client and server can send start and react messages, but in case of this app, start sending is mostly done by the client.

### 0: send_record
#### Body
1. author: str - allowed regex `[A-z0-9\-_]{2,25}`
2. val: float64

### 1: get_top_records
#### Body
1. amount: int32 - how many records from the top to fetch

#### React
Comma-separated list of `amount` record objects: `{author: str, val: float}`.


## References
* [Creating Winsock Application](https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/WinSock/creating-a-basic-winsock-application.md)
