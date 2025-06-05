import java.io.*;

public class Valutatore {
    private Lexer lex;
    private BufferedReader pbr;
    private Token look;
    
    public Valutatore(Lexer l, BufferedReader br) { 
        lex = l; 
        pbr = br;
        move(); 
    }
   
    void move() { 
        look = lex.lexical_scan(pbr);
        System.out.println("token = " + look);
    }
    
    void error(String s) { 
        throw new Error("vicino alla linea " + lex.line + ": " + s);
    }
    
    void match(int t) {
        if (look.tag == t) {
            if (look.tag != Tag.EOF) move();
        } else error("errore di sintassi");
    }
    
    public void start() { 
        // <start> ::= <expr> EOF
        int expr_val;
        expr_val = expr();
        match(Tag.EOF);
        System.out.println(expr_val);
    }
    
    private int expr() { 
        // <expr> ::= <term> <exprp>
        int term_val, exprp_val;
        term_val = term();
        exprp_val = exprp(term_val);
        return exprp_val;
    }
    
    private int exprp(int exprp_i) {
        // <exprp> ::= + <term> <exprp> | - <term> <exprp> | ε
        int term_val, exprp_val;
        switch (look.tag) {
            case '+':
                match('+');
                term_val = term();
                exprp_val = exprp(exprp_i + term_val);
                break;
                
            case '-':
                match('-');
                term_val = term();
                exprp_val = exprp(exprp_i - term_val);
                break;
                
            case ')':
            case Tag.EOF:
                // <exprp> ::= ε - produzione vuota
                exprp_val = exprp_i;
                break;
                
            default: 
                exprp_val = exprp_i;
                error("Errore in exprp: token inatteso " + look);
        }
        return exprp_val;
    }
    
    private int term() { 
        // <term> ::= <fact> <termp>
        int fact_val, termp_val;
        fact_val = fact();
        termp_val = termp(fact_val);
        return termp_val;
    }
    
    private int termp(int termp_i) { 
        // <termp> ::= * <fact> <termp> | / <fact> <termp> | ε
        int fact_val, termp_val;
        switch (look.tag) {
            case '*':
                match('*');
                fact_val = fact();
                termp_val = termp(termp_i * fact_val);
                break;
                
            case '/':
                match('/');
                fact_val = fact();
                if (fact_val == 0) {
                    error("Divisione per zero");
                }
                termp_val = termp(termp_i / fact_val);
                break;
                
            case '+':
            case '-':
            case ')':
            case Tag.EOF:
                // <termp> ::= ε - produzione vuota
                termp_val = termp_i;
                break;
                
            default: 
                termp_val = termp_i;
                error("Errore in termp: token inatteso " + look);
        }
        return termp_val;
    }
    
    private int fact() { 
        // <fact> ::= NUM | ( <expr> )
        int fact_val;
        switch(look.tag) {
            case Tag.NUM:
                if (look instanceof NumberTok) {
                    fact_val = ((NumberTok) look).num;
                } else {
                    error("Token numerico non valido");
                    fact_val = 0;
                }
                match(Tag.NUM);
                break;
                
            case '(':
                match('(');
                fact_val = expr();
                match(')');
                break;
                
            default: 
                fact_val = 0;
                error("Errore in fact: atteso NUM o '(', trovato " + look);
        }
        return fact_val;
    }
    
    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "file.txt";
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Valutatore valutatore = new Valutatore(lex, br);
            valutatore.start();
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}