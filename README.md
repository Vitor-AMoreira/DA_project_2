# DA Routing Algorithm

This project corresponds to part 2 of the project done in the course Desenho de Algoritmos, a 2nd year course in the BSc/First Degree in Informatics and Computing Engineering @ FEUP

## Project Motivation

In this programming project, we were asked to design efficient algorithms to find optimal routes for vehicles
in generic shipping and delivery scenarios, from urban deliveries to ocean shipping. This problem
corresponds to the TSP. As the TSP is intractable, there are no known efficient algorithms to solve it.
Backtracking techniques can find the optimal solution to this problem. If the size of the graph is relatively
low, the application of these approaches might be reasonable. However, as we concluded in this project,
their application to large graphs is infeasible, due to their high computational complexity. Therefore,
approximation algorithms based on heuristics were devised to efficiently address TSP-based problems. This class
of approaches provide in many cases near-optimal solutions and may also prove bounds on the ratio between the
approximate and the optimal solutions.

In this project we were asked to design efficient heuristics for the TSP applied to diverse scenarios. We were
given multiple graphs and a selected departure and arrival point (or node). While we were given plenty of freedom
to explore effective heuristics, we were strongly suggested to at least implement the heuristic that takes advantage
of a triangular approximation as this one has a guaranteed approximation bound for an important class of graphs.
In particular, we designed appropriate heuristics according to the input data, such as the size and type of
the graph, as well as additional information contained in the dataset. In this regard, we analysed which heuristics
were more adequate to a given graph and analyse the trade-offs between optimality and efficiency.

Additionally, we implemented a backtracking algorithm to the TSP. Although this algorithm is not
efficient, it enabled us to determine the optimal solution to this problem for small graphs. These results helped
us analyse the optimality of our heuristics on small graphs.

## Authors

- **Victor Matos** - [vmup2021](https://github.com/vmup2021)
- **João Francisco Santos** - [ExSchYte](https://github.com/ExSchYte)
- **Vitor Moreira** - [Vitor-AMoreira](https://github.com/Vitor-AMoreira)
