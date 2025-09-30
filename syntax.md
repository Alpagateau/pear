<Program>  -> [<Instruction>]

<Instruction> -> 
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
        <Instructiona>
    
    
Fonction ->
fonction Nom([Nom:Type]) [Type]
debut
    [Instruction]
fin
