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
        throw new Error("vicino alla linea " + lex.line + ": " + s);
    }

    void match(int t) {
        if (look.tag == t) {
            if (look.tag != Tag.EOF) move();
        } else {
            error("errore di sintassi");
        }
    }

    public void prog() {
        // <prog> ::= <statlist> EOF
        statlist();
        match(Tag.EOF);
    }

    private void statlist() {
        // <statlist> ::= <stat> <statlistp>
        stat();
        statlistp();
    }

    private void statlistp() {
        // <statlistp> ::= ; <stat> <statlistp> | ε
        switch (look.tag) {
            case ';':
                match(';');
                stat();
                statlistp();
                break;

            case Tag.EOF:
            case '}':
                // ε - produzione vuota
                break;

            default:
                error("Errore in statlistp");
        }
    }

    private void stat() {
        // <stat> ::= assign <assignlist>
        //         | print (<exprlist>)
        //         | read (<idlist>)
        //         | for ( <forstat>
        //         | if ( <bexpr> ) <stat> <ifp>
        //         | { <statlist> }
        switch (look.tag) {
            case Tag.ASSIGN:
                match(Tag.ASSIGN);
                assignlist();
                break;

            case Tag.PRINT:
                match(Tag.PRINT);
                match('(');
                exprlist();
                match(')');
                break;

            case Tag.READ:
                match(Tag.READ);
                match('(');
                idlist();
                match(')');
                break;

            case Tag.FOR:
                match(Tag.FOR);
                match('(');
                forstat();
                break;

            case Tag.IF:
                match(Tag.IF);
                match('(');
                bexpr();
                match(')');
                stat();
                ifp();
                break;

            case '{':
                match('{');
                statlist();
                match('}');
                break;

            default:
                error("Errore in stat");
        }
    }

    private void forstat() {
        // <forstat> ::= ID := <expr> ; <bexpr> ) do <stat>
        //             | <bexpr> ) do <stat>
        if (look.tag == Tag.ID) {
            match(Tag.ID);
            match(Tag.INIT); // :=
            expr();
            match(';');
            bexpr();
            match(')');
            match(Tag.DO);
            stat();
        } else {
            bexpr();
            match(')');
            match(Tag.DO);
            stat();
        }
    }

    private void ifp() {
        // <ifp> ::= else <stat> end | end
        switch (look.tag) {
            case Tag.ELSE:
                match(Tag.ELSE);
                stat();
                match(Tag.END);
                break;

            case Tag.END:
                match(Tag.END);
                break;

            default:
                error("Errore in ifp");
        }
    }

    private void assignlist() {
        // <assignlist> ::= [ <expr> to <idlist> ] <assignlistp>
        match('[');
        expr();
        match(Tag.TO);
        idlist();
        match(']');
        assignlistp();
    }

    private void assignlistp() {
        // <assignlistp> ::= [ <expr> to <idlist> ] <assignlistp> | ε
        if (look.tag == '[') {
            match('[');
            expr();
            match(Tag.TO);
            idlist();
            match(']');
            assignlistp();
        }
        // else ε - produzione vuota
    }

    private void idlist() {
        // <idlist> ::= ID <idlistp>
        if (look.tag == Tag.ID) {
            match(Tag.ID);
            idlistp();
        } else {
            error("Errore in idlist");
        }
    }

    private void idlistp() {
        // <idlistp> ::= , ID <idlistp> | ε
        switch (look.tag) {
            case ',':
                match(',');
                match(Tag.ID);
                idlistp();
                break;

            case ')':
            case ';':
            case Tag.EOF:
            case ']':
            case '}':
                // ε - produzione vuota
                break;

            default:
                error("Errore in idlistp");
        }
    }

    private void bexpr() {
        // <bexpr> ::= RELOP <expr> <expr>
        if (look.tag == Tag.RELOP) {
            match(Tag.RELOP);
            expr();
            expr();
        } else {
            error("Errore in bexpr");
        }
    }

    private void expr() {
        // <expr> ::= + ( <exprlist> )
        //          | - <expr> <expr>
        //          | * ( <exprlist> )
        //          | / <expr> <expr>
        //          | NUM
        //          | ID
        switch (look.tag) {
            case '+':
                match('+');
                match('(');
                exprlist();
                match(')');
                break;

            case '-':
                match('-');
                expr();
                expr();
                break;

            case '*':
                match('*');
                match('(');
                exprlist();
                match(')');
                break;

            case '/':
                match('/');
                expr();
                expr();
                break;

            case Tag.NUM:
                match(Tag.NUM);
                break;

            case Tag.ID:
                match(Tag.ID);
                break;

            default:
                error("Errore in expr");
        }
    }

    private void exprlist() {
        // <exprlist> ::= <expr> <exprlistp>
        expr();
        exprlistp();
    }

    private void exprlistp() {
        // <exprlistp> ::= , <expr> <exprlistp> | ε
        switch (look.tag) {
            case ',':
                match(',');
                expr();
                exprlistp();
                break;

            case ')':
                // ε - produzione vuota
                break;

            default:
                error("Errore in exprlistp");
        }
    }

    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "file.txt";
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Parser parser = new Parser(lex, br);
            parser.prog();
            System.out.println("Input OK");
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}