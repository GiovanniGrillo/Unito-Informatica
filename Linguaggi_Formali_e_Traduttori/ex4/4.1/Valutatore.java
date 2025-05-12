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
        throw new Error("near line " + lex.line + ": " + s);
    }

    void match(int t) {
        if (look.tag == t) {
            if (look.tag != Tag.EOF) move();
        } else {
            error("syntax error");
        }
    }

    public void start() {
        // <start> ::= <expr> EOF {print(expr.val)}
        int expr_val;
        expr_val = expr();
        match(Tag.EOF);
        System.out.println("Risultato: " + expr_val);
    }

    private int expr() {
        // <expr> ::= <term> {exprp.i = term.val} <exprp> {expr.val = exprp.val}
        int term_val, exprp_val;
        term_val = term();
        exprp_val = exprp(term_val);
        return exprp_val;
    }

    private int exprp(int exprp_i) {
        // <exprp> ::= + <term> {exprp1.i = exprp.i + term.val} <exprp1> {exprp.val = exprp1.val}
        //          | - <term> {exprp1.i = exprp.i - term.val} <exprp1> {exprp.val = exprp1.val}
        //          | ε {exprp.val = exprp.i}
        int term_val, exprp_val = 0;
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
                exprp_val = exprp_i;
                break;

            default:
                error("syntax error in exprp");
        }
        return exprp_val;
    }

    private int term() {
        // <term> ::= <fact> {termp.i = fact.val} <termp> {term.val = termp.val}
        int fact_val, termp_val;
        fact_val = fact();
        termp_val = termp(fact_val);
        return termp_val;
    }

    private int termp(int termp_i) {
        // <termp> ::= * <fact> {termp1.i = termp.i * fact.val} <termp1> {termp.val = termp1.val}
        //          | / <fact> {termp1.i = termp.i / fact.val} <termp1> {termp.val = termp1.val}
        //          | ε {termp.val = termp.i}
        int fact_val, termp_val = 0;
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
                    error("division by zero");
                }
                termp_val = termp(termp_i / fact_val);
                break;

            case '+':
            case '-':
            case ')':
            case Tag.EOF:
                termp_val = termp_i;
                break;

            default:
                error("syntax error in termp");
        }
        return termp_val;
    }

    private int fact() {
        // <fact> ::= (<expr>) {fact.val = expr.val} | NUM {fact.val = NUM.value}
        int fact_val = 0;
        switch (look.tag) {
            case '(':
                match('(');
                fact_val = expr();
                match(')');
                break;

            case Tag.NUM:
                // Ottieni il valore dal token numerico
                if (look instanceof NumberTok) {
                    fact_val = ((NumberTok)look).num;
                }
                match(Tag.NUM);
                break;

            default:
                error("syntax error in fact");
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