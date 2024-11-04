# Leaderboards
Simple leaderboard API for games.

## Usage
See client.py for examples.

## API
We use codes and *lithium message format*. Code is a 16-bit integer. As soon as you connected, you can send any messages, and listen for responses. Responses are not connected to requests directly, the only identifier is a code.

Lithium message format: `<code>,<body_0>,<body_1>,<body...>,<body_n>`

### 0:send_record
#### Body
1. author: str - allowed regex `[A-z0-9\-_]{2,25}`
2. val: float64

### 1:get_top_records
#### Body
1. amount: int32 - how many records from the top to fetch

#### Response
1. 3:records, size <= amount

### 2:record
#### Body (array)
1. author: str
2. val: float64

## References
* [Creating Winsock Application](https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/WinSock/creating-a-basic-winsock-application.md)
* [Python Sockets](https://docs.python.org/3/howto/sockets.html)
