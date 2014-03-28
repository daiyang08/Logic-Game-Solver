Logic-Game-Solver
=================
This is the course project for Formal Verification Course. It is mainly to solve an interesting logic game: fill-a-pix, which can be found online (http://www.websudoku.com/?fill-a-pix).
For the basic version of the game, we need to fill some grids according to the clue number initiated at first.
We modeled the game as a SAT(satisfiability) problem and tried to solve it using SAT solver.

![image](https://raw.githubusercontent.com/daiyang08/Logic-Game-Solver/master/sample_result.png)

1.Generate SAT formula
----------------------
Actually, our formulas are the reflection of the init clues. This part of codes read the clues and generated a file with lines corresponding to each clue. Specifically, we need to watch some corner cases(e.g. corners and edges of the matrix).

2.Solve SAT problem using SAT solver
------------------------------------
This part would solve the formula we proposed in previous part. We should use two tools: limboole (http://fmv.jku.at/limboole/) and lingeling (http://fmv.jku.at/lingeling/). limboole is used to convert the original formula into the CNF(conjugate normal form), since CNF is the generic input of most SAT solver. lingeling is a high-performance SAT solver.

3.Generate result
-----------------
This part of codes need to parse the result coming from SAT solver and generate the final result. In addition, we visualized the result using SVG animation.

4.Test
------
i. run genFormula first with the input file (in.txt), the program will generate formula.txt
ii. run limboole to generate the CNF file (type ./limboole -d formula.txt -o cnf.txt)
iii. run lingeling to solve the SAT problem (type ./lingeling cnf.txt > solution.txt)
iv. run genSolution to get the final result with the Solution.svg file
