//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA3
// README.md
// README file for Graph ADT
//-----------------------------------------------------------------------------

List.c  - Implementation file for List ADT
List.h - Header file for List ADT
Graph.c - Implementation file for Graph ADT
Graph.h - Header file for Graph ADT
GraphTest.c - Self-created tests for Graph ADT functions
FindComponents.c - Top-level file for Graph ADT: iterate thru each vertex to create a map of each SCC(forwards). Re-run DFS on the transpose of G in order to verify backwards reachability(roots are vertices with no parents). DFS order from 1st call determines the order for 2nd call. This ensures that deepest roots are explored first, so SCCs are built correctly. DFS runs a private helper function that accepts a time int, manipulating a copy locally to pass as outout for accumulated time.
Makefile - Makefile for Graph ADT

AI Chat Log URLS
Graph.c - https://chatgpt.com/c/69756f0b-81d4-8331-b508-ead76edb2cfa
FindComponents.c - https://chatgpt.com/c/6976cd0e-81dc-832b-b1d1-922dd8eae982
