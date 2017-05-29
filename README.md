# lab8
Laboratory work 8 KPI programming course
# Laboratory work 8
## HTTP server
### Task
Create a TCP-server that listens TCP clients' connection requests and interact with them using HTTP protocol.
The server handle only with HTTP GET requests.
#### Avaliable HTTP paths:
* `/` - sends json object with information about server
* `/favourites` - sends json list with favourite actors
* `/favorites?{key}={value}` - sends json sublist with actors from `/favourites` list which have field `{key}` set as `{value}`
* `/favorites/{id}` - sends json object from `/favourites` list with id set as `{id}`
* `/file` - reads `data.txt` file from `data/` dircetory; sends json object with name of file, its size and data
* `/file/data` - sends json object with numbers on even positions in `data.txt`
### Modules
* Actor - describes actor
* List - functions for searching in `/favourites` list of actors
* Request - processes HTTP request and responces
* File - functions for working with files
