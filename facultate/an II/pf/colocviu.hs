import Data.List
import System.IO

divizori n = filter (\x -> n `mod` x == 0) [1 .. n]
fib = 1 : 1 : [a + b | (a, b) <- zip fib (tail fib)]

-- sum n = foldr (\elem accum -> accum + elem) 0 [1..n]

myFun1 (x, y) z (x1, y2) = ((x + x1) * z, z * (y + y2))

whatAge 16 = "You can drive A1."
whatAge 18 = "You can drive A2 and B."
whatAge otherwise = "Nothing special."

double x = x * 2
doubleList [] = [] -- Same functionality as map
doubleList (x : xs) = double x : doubleList xs

areStringsEq [] [] = True
areStringsEq (x:xs) (y:ys) = x == y && areStringsEq xs ys
areStringsEq _ _ = False -- In case the strings are not equal

equalStr a b = and (zipWith (==) a b)

doMult func = func 3

dblist = map (\x -> x * 2)

removeFromACharsInB a b = [ x | x <- a, notElem x b]

removeFromACharsInBrecursive a b = filter (not . (`elem` b)) a

first_fold_argument a b = a + b

sumap2 n = foldr first_fold_argument 0 [1..n]

count e = foldr (\x acc -> if e == x then acc+1 else acc) 0

isAll e = foldr (\x acc -> e == x && acc) True

split = map (:[])

data Alegere = Piatra
             | Foarfeca
             | Hartie
             deriving (Eq, Show)

data Rezultat = Victorie | Infrangere | Egalitate deriving (Eq, Show)

partida :: Alegere -> Alegere -> Rezultat
partida x y
    | x == Piatra && y == Foarfeca = Victorie
    | x == Piatra && y == Hartie = Infrangere
    | x == Foarfeca && y == Piatra = Infrangere
    | x == Foarfeca && y == Hartie = Victorie
    | x == Hartie && y == Foarfeca = Infrangere
    | x == Hartie && y == Piatra = Victorie
    | otherwise = Egalitate


semipar2 [] = []
semipar2 (x:xs) = if even x then div x 2 : semipar2 xs else semipar2 xs
semipar3 l = [div x 2 | x <- l, even x]

interval a b l = [x | x <- l, a <= x && x<= b] 
interval2 a b [] = []
interval2 a b (x:xs) = if a <= x && x <= b then x : interval2 a b xs else interval a b xs

pozitive l = [x | x <- l, x > 0]

impare l = [fst x | x <- zip [0..] l, odd $ snd x]  

discount = map (\x -> if x < 200 then 0.75 * x else x)
discount1 [] = []
discount1 (x:xs) = if x < 200 then 0.75 * x : discount1 xs else x : discount1 xs

zip3 a b c = [(snd x, snd y , snd z) | x <- zip [1..] a, y <- zip [1..] b, z <- zip [1..] c, fst x == fst y && fst y == fst z] 

factori n = [x | x <- [1..n], mod n x == 0]
prim n = length (factori n) <= 2
primi n = zip [1 ..] [if length ([x | x <- [1 .. n], mod n x == 0]) <= 2 then "Yes" else "No" | x <- [1..n]]
primi2 n = [x | x <- [2..n], prim x]

firstEl l = [fst x | x <- l]
firstEl2 = map fst 

ex11 c l = [x | x <- l, elem c x]
ex12 c l = filter (elem c) l

ex21 l = [if odd x then x ^ 2 else x | x <- l]
ex22 l = map (\x -> if odd x then x ^ 2 else x) l
ex23 [] = []
ex23 (x:xs) = if odd x then x ^ 2 : ex23 xs else x : ex23 xs

ex31 l = [if odd (fst x) then snd x ^ 2 else snd x | x <- zip [0..] l]
ex32 [] = []
ex32 (x:xs) = if odd (fst x) then snd x ^ 2 : ex32 xs else snd x : ex32 xs
ex33 l = map (\(x, y) -> if odd x then y ^ 2 else y) (zip [0..] l)



e41helper a = [x | x <- a, notElem x "aeiouAEIOU"]
e41 = map e41helper

reverse' l = foldl (flip (:)) [] l

-- Def fold: Operator Initial LIST
-- Operator: flip (:)    
-- Initial: []          empty list
-- LIST: argumentul nostru 

-- [1,2,3,4,5,6,7]
-- Normal (:) se aplica intre element si o lista => e : [1,2,3] = [e, 1, 2, 3]
-- flip da reverese la argumente adica [1,2,3] : e = [1, 2, 3, e]

--                                 noted flip (:) cu X
-- so foldl (flip (:)) [] [1, 2, 3, 4, 5] = 1 X 2 X 3 X 4 X 5 X []
--                                   so  (((((2 : 1) X 3) X 4) X 5) X [])
--                                       (3 : (2 : 1)) X 4 X 5 X []
--                                       (4 : (3 : (2 : 1))) X 5 X []



-- Ex1
produsRec = error "🖕🖕🖕🖕🖕🖕🖕"
produsFold l = foldl (\x y -> x * y) 1 l

-- Ex2
-- se numeste and
functiaMeaBlanao l = and l

andFold lista = foldl (\x y -> x && y) True lista

-- Ex3
-- again, concat exista deja, astia-s retardati ma jur

concatFold l = foldl (++) [] l

-- Ex4
--      a)
rmChar _ [] = []
rmChar c (x:xs) = if x == c then rmChar c xs else x : rmChar c xs 

--      b)

rmcharsRec _ [] = []
rmcharsRec chars (x : xs) = if elem x chars then rmcharsRec chars xs else x : rmcharsRec chars xs


rmcharsRec2 _ [] = []
rmcharsRec2 chars l = [x | x <- l, notElem x chars]



printTrips a b c = do
                    putStrLn a
                    putStrLn b
                    putStrLn c




-- simulare
alfabet1 = ['A' .. 'L'] ++ ['a' .. 'l']
alfabet2 = ['M' .. 'Z'] ++ ['m' .. 'z']

f2a c
    | elem c alfabet1 = True
    | elem c alfabet2 = False
    | otherwise = error "eroare"

f2b l = (sum $ map (\x -> if elem x alfabet1 then 1 else 0) l) > (sum $ map (\x -> if elem x alfabet2 then 1 else 0) l)


f2cHelper1 [] = []
f2cHelper1 (x : xs) = if elem x alfabet1 then 1 : f2cHelper1 xs else 0 : f2cHelper1 xs
f2cHelper2 [] = []
f2cHelper2 (x : xs) = if elem x alfabet2 then 1 : f2cHelper2 xs else 0 : f2cHelper2 xs
f2c l = sum (f2cHelper1 l) > sum (f2cHelper2 l)

f3a l = [x | (x, y) <- zip l (tail l), x == y]

f3b [] = []
f3b [x] = []
f3b (x:y:xs) = if x == y then x : f3b (y : xs) else f3b (y : xs)

elementAt l i = l !! i

compress [] = []
compress [x] = [x]
compress (x : y : xs) = if x == y then compress (y : xs) else x : compress (y : xs)


function l n = if n < 0 then 0 else foldl max 0 [x | x <- l, 0 <= x && x <= n]

ordonatNatRed (x:y:rest) = if x < y then ordonatNat (y : rest) else False

ordonatNat [x] = True
ordonatNat (x:y:rest) = x < y && ordonatNat (y : rest)


calcFold l p = sum [uncurry (+) x ^ 2 | x <- zip l p]


f34a l = sum ((\l -> [if (\(a, b) -> mod a 3 == 0 && mod b 3 == 0) x then uncurry (-) x else uncurry (*) x | x <- l]) ((\l -> [(snd x, snd y) | x <- zip [0 ..] l, y <- zip [0 ..] l, fst x + 1 == fst y]) l))

exista str ls
  | null ls = False 
  | isPrefixOf str (head ls) = True
  | otherwise = exista str (tail ls)

-- extrage s ll = [or (map isPrefixOf s l) | l <- ll]


pozitie l1 l2 = [snd x | x <- zip [0..] l1, y <- zip [0..] l2, fst x == fst y, snd x == snd y]

vPozitive :: [(Int, Int)] -> [(Int, Int)]
vPozitive = filter (\(x, y) -> x > 0 && y > 0)


-- exmamen

-- Exercitiul 2 - functie ajutatoare
srDoiHelper :: Char -> (Char, Char)
srDoiHelper x
  | elem x ['a'..'z'] = (x, '#')
  | elem x ['A'..'Z'] = (x, '*')
  | elem x ['1'..'9'] = (x, '^')
  | otherwise = (x, '_')


-- Exercitiul 2 subpunctul 1 - Recursie

srDoiUnu :: [Char] -> [(Char, Char)]
srDoiUnu [] = []
srDoiUnu (x:rest) = srDoiHelper x : srDoiUnu rest

-- Teste :
-- srDoiUnu "ASDkllk;2L"

-- Exercitiu 2 subpunctul 2

srDoiDoi :: [Char] -> [(Char, Char)]
srDoiDoi [] = []
srDoiDoi l = [srDoiHelper x | x <- l]

-- Teste:
-- srDoiDoi "ASDkllk;2L" == srDoiUnu "ASDkllk;2L"

-- Exercitiu 2 subpunctul 3 - Functii de nivel inalt

srDoiTrei :: [Char] -> [(Char, Char)]
srDoiTrei = map srDoiHelper

-- Teste:
-- srDoiDoi "ASDkllk;2L" == srDoiTrei "ASDkllk;2L"

-- Exercitiu 2 subpunctul 3

srDoiQuickCheck :: [Char] -> Bool
srDoiQuickCheck l = srDoiUnu l == srDoiTrei l

-- Teste:
-- srDoiQuickCheck "ASDkllk;2L"

-- Exercitiul 3

-- Alo -> 4 ? sunt 3 nu, intradevar cu semnul sunt 4
-- dar Aaalo? -> sunt 6, raspunsul dumneavoastra    teste 7
-- Ahh, am inteles, se iau in considerare si spatiile.

delimiter = " ,.?!:"

-- O functie care transofrma un sir in lista de siruri
-- Mai am 50 de secunde si nu mai am timp pentru explicatii :/ Sper sa se inteleaga
splitStringHelper :: [Char] -> [Char] -> [[Char]]
splitStringHelper [] _ = []
splitStringHelper (x : rest) acc = if elem x delimiter then acc : (splitStringHelper rest "") else splitStringHelper rest (acc ++ [x])

splitString string = splitStringHelper string ""

-- rsTreiSolution :: [String] -> [Int]
rsTreiSolution :: [Char] -> [Int]
rsTreiSolution ll = [1 + length l | l <- splitStringHelper ll ""]


-- rsTreiSolution "Alo? Aaalo? Sunt eu: Picaso! Ti-am dat bip, si sunt voinic."

-- examen Alexandra

isPalindrom :: Eq a => [a] -> Bool
isPalindrom l = l == reverse l

-- Recursivitate

exerctiu1sub1 [] = False
exerctiu1sub1 (x:rest) = isPalindrom x || exerctiu1sub1 rest

-- Descriere de liste

exerctiu1sub2 l = or [isPalindrom x | x <- l]

-- Functii de  nivel intal

exerctiu1sub3 :: Eq a => [[a]] -> Bool
exerctiu1sub3 l = or (map isPalindrom l)

-- Quick check

exerctiu1sub4 :: Eq a => [[a]] -> Bool
exerctiu1sub4 l = exerctiu1sub1 l == exerctiu1sub3 l


-- 2

vocale :: [Char]
vocale = "AEIOUaeiou"

exerctiu2 :: [Char] -> [Char]
exerctiu2 [] = []
exerctiu2 [_] = []
exerctiu2 [x, y] = [x, y]
exerctiu2 [x, y, z] = if x == z && elem x vocale && y == 'p' then [x] else [x, y, z]
exerctiu2 (x : y : z : rest) = if x == z && elem x vocale && y == 'p' then x : exerctiu2 rest else x : exerctiu2 (y : z : rest)

-- teste:

-- exerctiu2 "mepergepe"
-- exerctiu2 "apapapa"
-- exerctiu2 "nupupu" => nupu
-- elimina primul grup de cuvinte de tipul vocala : p : vocala
-- rezulta n X pu | unde X = u transformat din upu

-- PRE EXAMEN

myLast :: [a] -> a
myLast (x:rest) = if null rest then x else myLast rest

data Shape = Circle Float Float Float | Rectangle Float Float Float Float deriving (Show)

surface (Circle _ _ r) = pi * r ^ 2
surface (Rectangle x1 x2 y1 y2) = (abs $ x2 - x1) * (abs $ y2 - y1)

myLenHelper [] acc = acc
myLenHelper (x:r) acc = myLenHelper r acc+1 

myLen l = myLenHelper l 0

