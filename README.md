# CNF-Problem-Solving-Using-Graphs---CPP


The problem commences with a formula F consisting of n number of variables which can be used in any
sequence. The formula consists of clauses having any number of OR operations on multiple variables and
the clauses are joined through AND operations. Suppose there is an initial random assignment T of Boolean
values to the variables of formula F, it is required to find another assignment T’ that disagrees with T on at
most k number of bits and strictly satisfies a greater number of clauses than the original T. For simplicity,
the disagreement is represented as d. Therefore, T and T’ are identical for (n – d) bits where 1 ≤ d ≤ k exhibits the disagreement constraint.


1. Clause Network can have minimum 1 and maximum 6 activated nodes.
2. Each node represents an arbitrary distinct variable.
3. Nodes N2 to N6 are activated only when a clause expression has more than one variable. A sample of Clause Network with edge weights representing a clause {-63, 205, 208, 215, 260} is given below in a table.
4. Weights of E1, E2, E3, E4, E5 and E6 edges represent respective Input Variables.
5. A negative weight edge represents NOT operation on the respective Input Variable.
6. The OR nodes perform OR-operation on two values and also have a read logic. For example, -63 and 205 received in OR1 means access variable63 with NOT and access variable 205 as it is and later perform OR on both accessed values.
7. Clauses are provided in a separate dataset.txt file in which each line represents a clause ending with
8. Remember, for testing a different dataset can be used.
9. The initial truth assignment T should be randomly generated for all 1040 variables, whereas T’ is the output of your algorithm that satisfies the given constraint.
