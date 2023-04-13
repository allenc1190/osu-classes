module HOMEWORK3 where
-----------------------
--Group members:      |
-----------------------
-- 1) Danmar Green    |
-- 2) Xufeng Liu      |
-- 3) Allen Chan      |
-- 4) Abdullah Oumar  |
----------------------

-------------------------------------------------------------------------------------------------

---Exercise 1. A Stack Language
----
-----

type Prog = [Cmd]

data Cmd = LD Int
         | ADD
         | MULT
         | DUP
         deriving Show

type Stack = [Int]

type D = Maybe Stack -> Maybe Stack

sem :: Prog -> D
sem [] s = s
sem (x:xs) s = sem xs (semCmd x s)

semCmd :: Cmd -> D
semCmd (LD x) (Just s) = Just $ x :s
semCmd ADD (Just (x:y:xs)) = Just $ (x+y) : xs
semCmd MULT (Just (x:y:xs)) = Just $ (x*y) : xs
semCmd DUP (Just (x:xs)) = Just $ x : x : xs

semCmd _  _   =  Nothing

----------------------------------------------------------------------------------------------

---Exercise 2. Mini Logo
---
----

data Cmd' = Pen Mode
          | MoveTo Int Int
          | Seq Cmd' Cmd'
            deriving Show
          
data Mode = Up | Down
            deriving Show

type State = (Mode,Int,Int)

type Line  = (Int,Int,Int,Int)

type Lines = [Line]


semS :: Cmd' -> State -> (State,Lines)
semS (Pen c) (m,x1,y1) = ((c,x1,y1),[])
semS (MoveTo x2 y2) (m,x1,y1) = case m of
                                Up   ->  ((Up,x2,y2),[])
                                Down ->  ((Down,x2,y2),[(x1,y1,x2,y2)]) 

semS (Seq c c') (m,x1,y1) = y
      where xs = fst (semS c (m,x1,y1))
            ys = snd (semS c (m,x1,y1))
            x = fst (semS c' xs)
            y = (x,ys ++ snd (semS c' xs))


sem' :: Cmd' -> Lines
sem' c = snd (semS c (Up,0,0))

      
