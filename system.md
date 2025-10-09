PEAR -> parse la commande -> [ARG | noms de fichiers]

-- lexem : un élément syntaxique 

data lexem = 
    PARENTHESE_OUVERTE 
    | PARENTHESE_FERME 
    | IDENFIFIANT String 
    | CONSTANTE Int 


lexer :: Nom de fichier -> [Lexem]
parser :: [lexem] -> AST

AST : Abstract Syntax Tree

4 + 3 * 2
    + 
   / \
  4   *
     / \
    3   2

Program 
|-main 
    |-definition 
        |- identifiant = var1
        |- val  = 3
    |- appel de fonction 
        |- identifiant = print
        |- 
