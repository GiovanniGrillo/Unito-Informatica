import java.io.*;
import java.util.LinkedList;
import java.util.List;

public class Translator {
    private Lexer lex;
    private BufferedReader pbr;
    private Token look;

    SymbolTable st = new SymbolTable();
    CodeGenerator code = new CodeGenerator();
    int count = 0;

    public Translator(Lexer l, BufferedReader br) {
        lex = l;
        pbr = br;
        move();
    }

    void move() {
        look = lex.lexical_scan(pbr);
        if (look == null) {
            error("Lexical error: invalid token");
        }
        System.out.println("token = " + look);
    }

    void error(String s) {
        throw new Error("Near line " + lex.line + ": " + s);
    }

    void match(int t) {
        if (look.tag == t) {
            if (look.tag != Tag.EOF) move();
        } else {
            error("syntax error");
        }
    }

    public void prog() {
        statlist();
        match(Tag.EOF);
        try {
            code.toJasmin();
        } catch (java.io.IOException e) {
            System.out.println("IO error\n");
        }
    }

    private void statlist() {
        stat();
        statlistp();
    }

    private void statlistp() {
        switch (look.tag) {
            case ';':
                match(';');
                stat();
                statlistp();
                break;
            case Tag.EOF:
            case '}':
                break;
            default:
                error("Error in statlistp");
        }
    }

    public void stat() {
        switch (look.tag) {
            case Tag.ASSIGN:
                match(Tag.ASSIGN);
                assignlist();
                break;

            case Tag.PRINT:
                match(Tag.PRINT);
                match('(');
                int printCount = exprlist_print();
                for (int i = 0; i < printCount; i++) {
                    code.emit(OpCode.invokestatic, 1);
                }
                match(')');
                break;

            case Tag.READ:
                match(Tag.READ);
                match('(');
                List<String> ids = idlist();
                match(')');
                for (String id : ids) {
                    code.emit(OpCode.invokestatic, 0); // read()
                    int id_addr = st.lookupAddress(id);
                    if (id_addr == -1) {
                        id_addr = count;
                        st.insert(id, count++);
                    }
                    code.emit(OpCode.istore, id_addr);
                }
                break;

            case Tag.FOR:
                match(Tag.FOR);
                match('(');
                
                int condition_label = code.newLabel();
                int body_label = code.newLabel();
                int end_label = code.newLabel();
                
                // Controlla se c'è inizializzazione
                if (look.tag == Tag.ID) {
                    // Caso: for (ID := expr; bexpr) do stat
                    Token id_token = look;
                    match(Tag.ID);
                    String varName = ((Word)id_token).lexeme;
                    match(Tag.INIT);
                    expr();
                    
                    int id_addr = st.lookupAddress(varName);
                    if (id_addr == -1) {
                        id_addr = count;
                        st.insert(varName, count++);
                    }
                    code.emit(OpCode.istore, id_addr);
                    
                    match(';');
                }
                // else: caso for (bexpr) do stat
                
                code.emitLabel(condition_label);
                bexpr(body_label, true);  // Salta al body se condizione vera
                code.emit(OpCode.GOto, end_label);
                
                match(')');
                match(Tag.DO);
                
                code.emitLabel(body_label);
                stat();
                code.emit(OpCode.GOto, condition_label);
                
                code.emitLabel(end_label);
                break;

            case Tag.IF:
                int lnext_true = code.newLabel();
                int lnext_false = code.newLabel();
                int lnext_end = code.newLabel();
                
                match(Tag.IF);
                match('(');
                bexpr(lnext_true, true);  // Salta se vero
                code.emit(OpCode.GOto, lnext_false);
                match(')');
                
                code.emitLabel(lnext_true);
                stat();
                code.emit(OpCode.GOto, lnext_end);
                
                switch (look.tag) {
                    case Tag.ELSE:
                        code.emitLabel(lnext_false);
                        match(Tag.ELSE);
                        stat();
                        match(Tag.END);
                        break;
                    case Tag.END:
                        code.emitLabel(lnext_false);
                        match(Tag.END);
                        break;
                    default:
                        error("Error in if statement");
                }
                code.emitLabel(lnext_end);
                break;

            case '{':
                match('{');
                statlist();
                match('}');
                break;

            default:
                error("Error in stat");
        }
    }

    private void assignlist() {
        match('[');
        expr();
        match(Tag.TO);
        List<String> ids = idlist();
        
        // Genera il codice per assegnare il valore a tutti gli ID
        for (int i = 0; i < ids.size(); i++) {
            if (i < ids.size() - 1) {
                code.emit(OpCode.dup);
            }
            int id_addr = st.lookupAddress(ids.get(i));
            if (id_addr == -1) {
                id_addr = count;
                st.insert(ids.get(i), count++);
            }
            code.emit(OpCode.istore, id_addr);
        }
        
        match(']');
        assignlistp();
    }

    private void assignlistp() {
        if (look.tag == '[') {
            match('[');
            expr();
            match(Tag.TO);
            List<String> ids = idlist();
            
            for (int i = 0; i < ids.size(); i++) {
                if (i < ids.size() - 1) {
                    code.emit(OpCode.dup);
                }
                int id_addr = st.lookupAddress(ids.get(i));
                if (id_addr == -1) {
                    id_addr = count;
                    st.insert(ids.get(i), count++);
                }
                code.emit(OpCode.istore, id_addr);
            }
            
            match(']');
            assignlistp();
        }
        // else ε - produzione vuota
    }

    private List<String> idlist() {
        List<String> ids = new LinkedList<>();
        if (look.tag == Tag.ID) {
            ids.add(((Word) look).lexeme);
            match(Tag.ID);
            idlistp(ids);
        } else {
            error("Expected identifier in idlist");
        }
        return ids;
    }

    private void idlistp(List<String> ids) {
        if (look.tag == ',') {
            match(',');
            if (look.tag == Tag.ID) {
                ids.add(((Word) look).lexeme);
                match(Tag.ID);
                idlistp(ids);
            } else {
                error("Expected identifier after comma");
            }
        }
        // else ε - produzione vuota
    }

    private void bexpr(int lnext, boolean jump_if_true) {
        if (look.tag != Tag.RELOP) {
            error("Expected relational operator");
        }
        
        Token relop = look;
        match(Tag.RELOP);
        expr();  // primo operando
        expr();  // secondo operando
        
        String op = ((Word)relop).lexeme;
        if (jump_if_true) {
            // Salta a lnext se la condizione è vera
            switch(op) {
                case "==": code.emit(OpCode.if_icmpeq, lnext); break;
                case "<>": code.emit(OpCode.if_icmpne, lnext); break;
                case "<":  code.emit(OpCode.if_icmplt, lnext); break;
                case "<=": code.emit(OpCode.if_icmple, lnext); break;
                case ">":  code.emit(OpCode.if_icmpgt, lnext); break;
                case ">=": code.emit(OpCode.if_icmpge, lnext); break;
                default: error("Unknown relational operator: " + op);
            }
        } else {
            // Salta a lnext se la condizione è falsa (negata)
            switch(op) {
                case "==": code.emit(OpCode.if_icmpne, lnext); break;
                case "<>": code.emit(OpCode.if_icmpeq, lnext); break;
                case "<":  code.emit(OpCode.if_icmpge, lnext); break;
                case "<=": code.emit(OpCode.if_icmpgt, lnext); break;
                case ">":  code.emit(OpCode.if_icmple, lnext); break;
                case ">=": code.emit(OpCode.if_icmplt, lnext); break;
                default: error("Unknown relational operator: " + op);
            }
        }
    }

    private void expr() {
        switch(look.tag) {
            case '+':
                match('+');
                match('(');
                int addCount = exprlist_op();
                // Emetti iadd per ogni coppia (n-1 volte per n operandi)
                for (int i = 1; i < addCount; i++) {
                    code.emit(OpCode.iadd);
                }
                match(')');
                break;
                
            case '-':
                match('-');
                expr();
                expr();
                code.emit(OpCode.isub);
                break;
                
            case '*':
                match('*');
                match('(');
                int mulCount = exprlist_op();
                // Emetti imul per ogni coppia (n-1 volte per n operandi)
                for (int i = 1; i < mulCount; i++) {
                    code.emit(OpCode.imul);
                }
                match(')');
                break;
                
            case '/':
                match('/');
                expr();
                expr();
                code.emit(OpCode.idiv);
                break;
                
            case Tag.NUM:
                code.emit(OpCode.ldc, ((NumberTok) look).lexeme);
                match(Tag.NUM);
                break;
                
            case Tag.ID:
                int read_id_addr = st.lookupAddress(((Word)look).lexeme);
                if (read_id_addr == -1) {
                    error("Variable '" + ((Word)look).lexeme + "' not declared");
                }
                code.emit(OpCode.iload, read_id_addr);
                match(Tag.ID);
                break;
                
            default:
                error("Error in expr");
        }
    }

    // Metodo exprlist per PRINT
    private int exprlist_print() {
        expr();
        return 1 + exprlistp_print();
    }

    private int exprlistp_print() {
        if (look.tag == ',') {
            match(',');
            expr();
            return 1 + exprlistp_print();
        }
        return 0;
    }

    // Metodo exprlist per operazioni n-arie
    private int exprlist_op() {
        expr();
        return 1 + exprlistp_op();
    }

    private int exprlistp_op() {
        if (look.tag == ',') {
            match(',');
            expr();
            return 1 + exprlistp_op();
        }
        return 0;
    }

    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "test.lft"; // Nome del file da tradurre
        
        if (args.length > 0) {
            path = args[0];
        }
        
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Translator translator = new Translator(lex, br);
            translator.prog();
            br.close();
            System.out.println("Translation completed successfully.");
            System.out.println("Output written to Output.j");
        } catch (IOException e) {
            System.err.println("IO error: " + e.getMessage());
        } catch (Error e) {
            System.err.println("Translation error: " + e.getMessage());
        }
    }
}