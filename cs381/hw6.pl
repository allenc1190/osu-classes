
/* Exercise 1 */

/*redefine_system_predicate(when).*/

when(275,10).
when(261,12).
when(381,11).
when(398,12).
when(399,12).

where(275,owen102).
where(261,dear118).
where(381,cov216).
where(398,dear118).
where(399,cov216).

enroll(mary,275).
enroll(john,275).
enroll(mary,261).
enroll(john,381).
enroll(jim,399).


/* Exercise 1 */


/*Q1.a*/
schedule(Name,Classroom,Time):- enroll(Name,ID), where(ID,Classroom),when(ID,Time).


/*Q1.b*/

usage(Classroom,Time):- where(ID,Classroom), when(ID,Time).

/*Q1.c*/
conflict(ID_1,ID_2):- where(ID_1,Room), where(ID_2,Room), when(ID_1,Time), when(ID_2,Time), ID_1 \= ID_2.

/*Q1.d*/
meet(Student_1,Student_2):-schedule(Student_1,Classroom,Time_1),schedule(Student_2,Classroom,Time_2),Student_1\=Student_2,Time_2 =:= Time_1+1;
                           schedule(Student_1,Classroom,Time_1),schedule(Student_2,Classroom,Time_2),Student_1\=Student_2,Time_1 = Time_2.

/* Exercise 2 */


/*Q2.a*/
rdup([],[]).
rdup([L],[L]):-!.
rdup([X,X|L],M):-rdup([X|L],M),!.
rdup([X|L],[X|M]):-rdup(L,M).

/*Q2.b*/
flat([],[]).
flat([[Y|X]|L],F):-flat([Y|[X|L]],F),!.
flat([[]|L],F):-flat(L,F).
flat([X|L],[X|F]):-flat(L,F).



/*
flat([X|Y], L) :- flat(X,LX),
                  flat(Y,LY),
                  sppend(LX,LY,L).

*/

/*Q3.c*/
project(E,L1,L2):-project(0,E,L1,L2).
project(_,[],_,[]).
project(_,_,[],[]).
project(I,[X|E],[Y|L1],[Y|L2]):- X is I+1,project(X,E,L1,L2).
project(I,[X|E],[_|L1],L2):-project(I+1,[X|E],L1,L2),!.








