data Prog = On Instr
data Instr = Off | Expr :> Instr
data Expr = Mem | V Int | Expr :+ Expr

type Env = Int
type DomProg = [Int]
type DomInstr = Env -> [Int]
type DomExpr = Env -> Int


prog :: Prog -> DomProg
prog (On s) = undefined 