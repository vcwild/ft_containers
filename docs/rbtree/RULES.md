# Red-Black Trees

## Rules

A red-black tree is a binary search tree that satisﬁes the following red-
black properties:

1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant
leaves contain the same number of black nodes.

* As a matter of convenience in dealing with boundary conditions in
red-black tree code, we use a single sentinel to represent NIL
