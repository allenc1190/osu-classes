-- cs381 spring term HW 1, group 4.

module HW1types where

import Data.List (nub,sort)



-- Types for Exercise 1
--
--(a)
type Bag a = [(a,Int)]
ins :: Eq a => a -> Bag a -> Bag a
ins x [] = [(x,1)]
ins x ((y,z):zs)
    | y == x = (y,z+1):zs
    | otherwise = (y,z): ins x zs



--(b)
del :: Eq a => a -> Bag a -> Bag a
del x ((y,z):zs)
    | y == x = if (z-1 == 0) then zs else (y,z-1):zs
    | otherwise = (y,z): del x zs

--(c)

bag :: Eq a => [a] -> Bag a
bag []  = []
bag (x:xs) =  ins x (bag xs)
    

--(d)
subbag :: Eq a => Bag a -> Bag a -> Bool
subbag [] _ = True
subbag ((x,n):xns) yns = case (lookup x yns) of 
                         Just m  -> m >= n && subbag xns yns    
                         Nothing -> False



--(e)

isSet :: Eq a => Bag a -> Bool
isSet [] = True
isSet ((x,_):xns) = case (lookup x xns) of 
                    Just m  -> False 
                    Nothing -> isSet xns

--(f)

size :: Bag a -> Int
size [] = 0
size ((_,n):ns) = n + size ns


-- Types and functions for Exercise 2
--



type Node  = Int
type Edge  = (Node,Node)
type Graph = [Edge]
type Path  = [Node]

norm :: Ord a => [a] -> [a]
norm = sort . nub


--(a)
nodes :: Graph -> [Node]
nodes [] = []
nodes x = norm $ map fst x ++ map snd x


--(b)
suc :: Node -> Graph -> [Node]
suc x [] = []
suc x ((a,b):ys)
    | x == a = b : suc x ys
    | otherwise = suc x ys 


--(c)
detach :: Node -> Graph -> Graph
detach x [] = []
detach x ((a,b):ys)
    | x /= a && x /= b = (a,b) : detach x ys
    | otherwise = detach x ys

--(d)
cyc :: Int -> Graph
cyc 0 = []
cyc x = zip y z
    where y = take x (cycle [1..x]) 
          z = tail $ take (x+1) (cycle [1..x])


-- Types for Exercise 3
--
type Number = Int

type Point = (Number,Number)
type Length = Number

data Shape = Pt Point
           | Circle Point Length
           | Rect Point Length Length
           deriving Show

type Figure = [Shape]

type BBox = (Point,Point)

--(a)
width :: Shape -> Length  
width (Pt (ptP1,ptP2)) = 0
width (Circle (ptC1,ptC2) c) = 2*c
width (Rect (ptR1,ptR2) ln1 ln2) = ln1

--(b)
bbox :: Shape -> BBox
bbox (Pt (ptP1,ptP2)) = ((ptP1,ptP2),(ptP1,ptP2))
bbox (Circle (ptC1,ptC2) c) = ((ptC1-c,ptC2-c),(ptC1+c,ptC2+c))
bbox (Rect (ptR1,ptR2) ln1 ln2) = ((ptR1,ptR2),(ptR1+ln1,ptR2+ln2))

--(c)
minX  :: Shape -> Number
minX (Pt (ptP1,ptP2)) = ptP1
minX (Circle (ptC1,ptC2) c) = ptC1-c
minX (Rect (ptR1,ptR2) ln1 ln2) = ptR1

--(d)
addPt :: Point -> Point -> Point
addPt (x1,y1) (x2,y2) = (x1+x2,y1+y2)

move :: Shape -> Point -> Shape
move (Pt (ptP1,ptP2)) (x1,y1) = (Pt (addPt (ptP1,ptP2) (x1,y1)))
move (Circle (ptC1,ptC2) c) (x2,y2) = ( Circle (addPt (ptC1,ptC2) (x2,y2)) c)
move (Rect (ptR1,ptR2) ln1 ln2) (x3,y3) = (Rect (addPt (ptR1,ptR2) (x3,y3)) ln1 ln2)




