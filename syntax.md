<Program>  -> [<Instruction>]

# <Instruction> -> 
    <Vide>
OU
    [<Insruction>]
OU
    <Affectation>
OU 
    retourner [<Expression>]
OU 
    debut
        [<Instruction>]
    fin
OU
    si <Expr_bool> alors 
        <Instruction> 
    sinon 
        <Instruction>
OU
    tantque <Expr_bool> faire 
        <Instruction>
OU
    pour <Nom> de <Expr_int> à <Expr_int> faire
        <Instruction>
OU
    répéter <Expr_int> fois
        <Instruction>
    

# <Fonction> ->
    fonction <Nom>([<Nom>:<Type>]) [<Type>]
    debut
        [<Instruction>]
    fin

# <Expression> ->
    <Nom>
OU
    <Nom>\[<Expression>\]
OU
    <Nom>\[<Expression>\]\[<Expression>\]
OU
    <Nom>([<Expression>])
OU
    <Nom> 
    

# <Operateur> ->
    +
OU
    -
OU
    *
OU 
    /
OU
    %
OU
    =