import java.io.*;

public class Parser {
    private Lexer lex;
    private BufferedReader pbr;
    private Token look;

    public Parser(Lexer l, BufferedReader br) {
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
        // <start> ::= <expr> EOF
        expr();
        match(Tag.EOF);
    }

    private void expr() {
        // <expr> ::= <term> <exprp>
        term();
        exprp();
    }

    private void exprp() {
        switch (look.tag) {
            case '+':
                // <exprp> ::= + <term> <exprp>
                match('+');
                term();
                exprp();
                break;

            case '-':
                // <exprp> ::= - <term> <exprp>
                match('-');
                term();
                exprp();
                break;

            case ')':  // Follow set di exprp include ')'
            case Tag.EOF:  // Follow set di exprp include EOF
                // <exprp> ::= ε
                break;

            default:
                error("Error in exprp");
        }
    }

    private void term() {
        // <term> ::= <fact> <termp>
        fact();
        termp();
    }

    private void termp() {
        switch (look.tag) {
            case '*':
                // <termp> ::= * <fact> <termp>
                match('*');
                fact();
                termp();
                break;

            case '/':
                // <termp> ::= / <fact> <termp>
                match('/');
                fact();
                termp();
                break;

            case '+':  // Follow set di termp include '+' e '-'
            case '-':
            case ')':  // Follow set di termp include ')'
            case Tag.EOF:  // Follow set di termp include EOF
                // <termp> ::= ε
                break;

            default:
                error("Error in termp");
        }
    }

    private void fact() {
        switch (look.tag) {
            case '(':
                // <fact> ::= ( <expr> )
                match('(');
                expr();
                match(')');
                break;

            case Tag.NUM:
                // <fact> ::= NUM
                match(Tag.NUM);
                break;

            default:
                error("Error in fact");
        }
    }

    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "file.txt"; // il percorso del file da leggere
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Parser parser = new Parser(lex, br);
            parser.start();
            System.out.println("Input OK");
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}