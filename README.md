# Leaderboards
Simple leaderboard API for games.

## Usage
See client.py for examples.

## API
We use coded messages. Code is an 16-bit integer.

### 0: send_record
#### Args
1. author: str - allowed regex `[A-z0-9\-_]{2,25}`
2. val: float64

### 1: get_top_records
#### Args
1. amount: int32 - how many records from the top to fetch

#### Returns
Comma-separated list of 10 record objects,  e.g.:
* `Request: 1 3` - get top 3 records
* `Response: author=alex val=10, author=ray val=7.5, author=sonny val=3`


## References
* [Creating Winsock Application](https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/WinSock/creating-a-basic-winsock-application.md)
