data Prog = On Instr
data Instr = Off | Expr :> Instr
data Expr = Mem | V Int | Expr :+ Expr
type Env = Int
type DomProg = [Int]
type DomInstr = Env -> [Int]
type DomExpr = Env -> Int

prog :: Prog -> [Int]
prog = undefined

stmt :: Instr -> Env -> [Int]
stmt = undefined

expr :: Expr -> Env -> Int
expr = undefined

p1 = On (((Mem :+ V 2) :+ V 3) :> V 5 :+ V 3 :> ((Mem :+ V 5) :> Off))

type Name = String
data Hask
  = HTrue
  | HFalse
  | HLit Int
  | HIf Hask Hask Hask
  | Hask :==: Hask
  | Hask :+: Hask
  | HVar Name
  | HLam Name Hask
  | Hask :$: Hask
  deriving (Read, Show)

infix 4 :==:
infixl 6 :+:
infixl 9 :$:

data Value
  = VBool Bool
  | VInt Int
  | VFun (Value -> Value)
  | VError -- pentru reprezentarea erorilor

type HEnv = [(Name, Value)]

type DomHask = HEnv -> Value

hEval :: Hask -> DomHask
hEval = undefined


safediv :: Integral a => a -> a -> Maybe a
safediv m 0 = Nothing
safediv m n = Just (div m n)

isJust Nothing = False
isJust (Just _)  = True

fromJust Nothing = error "shoudn't happen"
fromJust (Just x) = x


divFrom10 n = [fromJust (safediv 10043 x) | x <- [n..50], isJust(safediv 10 x)]