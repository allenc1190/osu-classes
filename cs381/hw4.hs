module Homework_4 where
-----------------------
--Group 4 members:    |
-----------------------
-- 1) Danmar Green    |
-- 2) Xufeng Liu      |
-- 3) Allen Chan      |
-- 4) Abdullah Oumar  |
----------------------

-------------------------------------------------------------------------------------------------
---
--Exercise 1. A Rank-Based Type Systems for the Stack Language
---
----

type Prog = [Cmd]

data Cmd = LD Int
         | ADD
         | MULT
         | DUP
         | DEC
         | SWAP
         | POP Int
         deriving Show

type Rank    = Int
type CmdRank = (Int,Int)

type Stack = [Int]


sem :: Prog -> Stack -> Stack
sem [] s = s
sem (x:xs) s = sem xs (semCmd x s)

semCmd :: Cmd -> Stack -> Stack
semCmd (LD x) s = x:s
semCmd ADD (x:y:xs) = (x+y):xs
semCmd MULT (x:y:xs) = (x*y):xs
semCmd DUP (x:xs) = x:x:xs
semCmd DEC (x:xs) = (x-1):xs
semCmd SWAP (x:y:xs) = y:x:xs
semCmd (POP k) xs = drop k xs

--(a)  Use the following types to represent stack and operation ranks.

rankC :: Cmd -> CmdRank
rankC (LD c) = (0,1)
rankC ADD    = (2,1)
rankC MULT   = (2,1)
rankC DUP    = (1,2)
rankC DEC    = (1,1)
rankC SWAP   = (2,2)
rankC (POP k)  = (k,0)

rank :: Prog -> Rank -> Maybe Rank
rank [] r = Just r
rank (c:cms) r
    | (r > n) = rank cms rc
    | otherwise = Nothing
    where (n,m) = rankC c
          rc = (m + r - n)


rankP :: Prog -> Maybe Rank
rankP (cms) =  rank cms 0

--(b)

semStatTC :: Prog -> Maybe Stack
semStatTC p | (rankP p /= Nothing) = Just (sem p [])
            | otherwise = Nothing

-------------------------------------------------------------------------------------------------------------------------------------------------------------
---
--Exercise 2. Shape Language
---
----

data Shape = X
            | TD Shape Shape
            | LR Shape Shape
            deriving Show

type BBox = (Int,Int)


--(a)  Define a type checker for the shape language as a Haskell function

bbox :: Shape -> BBox
bbox X      = (1,1)
bbox (TD s1 s2) = (max bw1 bw2,bh1+bh2)
                where (bw1,bh1) = bbox s1
                      (bw2,bh2) = bbox s2

bbox (LR s1 s2) = (bw1+bw2,max bh1 bh2)
                where (bw1,bh1) = bbox s1
                      (bw2,bh2) = bbox s2


--(b)  Rectangles are a subset of shapes and thus describe a more restricted set of types.
--By restrictingthe application of the TD and LR operations to rectangles only one could ensure that only convexshapes without holes can be constructed.
--Define a type checker for the shape language that assignstypes only to rectangular shapes by defining a Haskell function

rect :: Shape -> Maybe BBox
rect X      = Just (1,1)
rect (TD s1 s2) = case (rect s1,rect s2) of
                  (Just(x1,y1),Just(x2,y2)) -> if (x1 == x2) then Just(x1,y1+y2) else Nothing
                  _                         -> Nothing

rect (LR s1 s2) = case (rect s1,rect s2) of
                  (Just(x1,y1),Just(x2,y2)) -> if (y1 == y2) then Just(x1+x2,y2) else Nothing
                  _                         -> Nothing


