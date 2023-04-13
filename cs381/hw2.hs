-- cs381 spring term HW 2, group 4.
---
---
module HW2 where 

--Exercise 1. Mini Logo
--

-- Part (a)
--

type Name = String

type Num' = Int 

data Cmd = Pen Mode 
         | MoveTo (Pos,Pos)
         | Def Name Pars Cmd
         | Call Name Vals
         | Cmd `And` Cmd
            deriving Show

data Mode = Up | Down 
            deriving Show

data Pos =  PosNum Num' | PosName Name
            deriving Show

data Pars = ParsPair Name Pars | ParsName Name 
            deriving Show

data Vals = ValsPair Num' Vals | ValsNum Num' 
            deriving Show

-- Part (b)
--
--concrete syntax for Mini Logo macro vector 
--def vector (x1,y1,x2,y2) pen up; moveto (x1,y1); pen down; moveto (x2,y2); pen up 

vector = Def "vector" (ParsPair "x1" (ParsPair "y1" (ParsPair "x2" (ParsName "y2")))) (Pen Up `And` (MoveTo (PosName "x1",PosName "y1") `And` (Pen Down `And` (MoveTo (PosName "x2",PosName "y2") `And` Pen Down))))

--helper function for steps
step :: Int -> Int -> Cmd
step _ 0 = Pen Down
step n s = MoveTo(PosNum (n-s), PosNum (n-s+1)) `And` (MoveTo(PosNum (n-s+1), PosNum (n-s+1)) `And` (step n (s-1)))

steps :: Int -> Cmd
steps n = Pen Up `And` (MoveTo(PosNum 0, PosNum 0) `And` (step n n))

--------------------------------------------------------------------------------------------------------------------------------

--Exercise 2. Regular Expressions
   
-- Part (a)
--   

data RegEx = Empty
            | Period
            | Ch Char
            | Quest_Mark RegEx
            | Star RegEx
            | Plus RegEx
            | Seq RegEx RegEx
            | Alt RegEx RegEx
            | Group RegEx
              deriving Show 

-- Part (b)
--

accept :: RegEx -> String -> Bool
accept Empty s = s == ""

accept Period [c] = True

accept (Ch c) [s] = c == s

accept (Quest_Mark c) [] = True
accept (Quest_Mark c) s = accept c s

accept (Star a) s = accept Empty s || or [accept a v && accept (Star a) w | (v,w) <- splits s]

accept (Plus a) s = or [accept a v && accept (Plus a) w | (v,w) <- splits s]

accept (Seq a1 a2) s = or [accept a1 v && accept a2 w | (v,w) <- splits s]

-- provide by hw2 documentation

accept (Alt r1 r2) s = accept r1 s || accept r2 s

accept (Group a1) s = accept a1 s

accept _ _ = False

splits :: [a] -> [([a],[a])]
splits []     = []
splits [x]    = [([],[x]),([x],[])]
splits (x:xs) = [([],x:xs)] ++ [(x:s,t) | (s,t) <- splits xs]


--Ching the inner regular expression, accept both a1 and s



classify :: RegEx -> [String] -> IO ()
classify e ws = putStrLn ("ACCEPT:\n"++show acc++"\nREJECT:\n"++show rej )
   where acc = filter (accept e) ws
         rej = filter (not.(accept e)) ws



-- Part (c)
--
commaSep' = (Seq (Period) (Seq (Ch 'a') (Ch 't')))

commaSep :: RegEx
commaSep = Seq commaSep' (Alt Empty (Seq (Ch ',') commaSep))

commaSepTest = ["cat","cat,bat","cat,cat","bat","",",","dog",",cat","cat,","catcat","cat,,bat","cat,bat,"]
