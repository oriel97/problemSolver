Problem-Solver is a Server, handles various clients parallel.

The problem given from the client, is finding shortest path in a graph (more precisley a matrix Graph, given a start and a goal,

the matrix filled with costs of every "step" which is sent line by line (creating the matrix of costs) by the client.

We implemented few algorithm for finding shorthest path A*, BEST FIRST SEARCH, DFS and BFS.
 
by doing An empirical experiment we learned that A* 
 
is the best algorithm to solve our client problems and the program use this algorithm.

When running our server using the main i made(namespace)

it expects a command line argument indicating the port number the server will be opened on.

Now the clients can send matrix and get the the soulution for the specific problem.

the solution the client is getting back, is a string that tell us the path from the start point we get

to the end point we also get from the client. 
