import java.io.*;

public class Valutatore { // Modificato da Parser a Valutatore per coerenza con il nome file originale
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
    	} else
          error("syntax error, expected " + t + " found " + look.tag);
    }

    public void prog() {
      //prog -> statlist EOF
      // Guida: {ASSIGN, PRINT, READ, FOR, IF, BEGIN}
      switch (look.tag){
        case Tag.ASSIGN:
        case Tag.PRINT:
        case Tag.READ:
        case Tag.FOR:
        case Tag.IF:
        case Tag.BEGIN: // '{' in Esercizio 3.2, BEGIN in Esercizio 4 Tag.java
  	       statlist();
  	       match(Tag.EOF);
           break;
        default:
          error("Error in prog, expected a statement, found " + look.tag);
      }
    }

    private void statlist() {
      //statlist -> stat statlistp
      // Guida: {ASSIGN, PRINT, READ, FOR, IF, BEGIN}
      switch (look.tag) {
        case Tag.ASSIGN:
        case Tag.PRINT:
        case Tag.READ:
        case Tag.FOR:
        case Tag.IF:
        case Tag.BEGIN:
          stat();
          statlistp();
          break;
        default:
          error("Error in statlist");
	     }
    }

    private void statlistp() {
      //statlistp -> ; stat statlistp   guida {;}
      //statlistp -> epsilon            guida {EOF, END} // END in Esercizio 4, '}' in Esercizio 3.2
      switch (look.tag){
        case ';':
          match(Token.semicolon.tag);
          stat();
          statlistp();
          break;
        case Tag.EOF:
        case Tag.END: // BEGIN...END block
          break;
        default:
          error("Error in statlistp, expected ';' or end of block/file, found " + look.tag);
       }
    }

    private void stat() {
      //stat -> assign ID := expr                 (Nota: Esercizio 4 originale non ha :=, usa 'assign expr to idlist')
      //stat -> print (exprlist)
      //stat -> read (idlist)
      //stat -> for ( ID init expr ; bexpr ) do stat
      //stat -> if (bexpr) then stat [else stat] end
      //stat -> begin statlist end
      switch (look.tag) {
        case Tag.ASSIGN: // assign expr to idlist (come da Esercizio 4 originale)
          match(Tag.ASSIGN);
          expr(); // L'espressione da assegnare
          match(Tag.TO);
          idlist();
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
          match(Tag.ID); // Variabile del ciclo
          match(Tag.INIT); // ':='
          expr(); // Valore iniziale
          match(';');
          bexpr(); // Condizione
          match(')');
          match(Tag.DO);
          stat();
          // Non c'è END esplicito per FOR nella grammatica di riferimento (Esercizio 3.2, Esercizio 5)
          break;

        case Tag.IF:
          match(Tag.IF);
          match('(');
          bexpr();
          match(')');
          // THEN non presente in Tag.java di Esercizio 4, quindi lo ometto
          stat();
          if_statp(); // Gestisce ELSE e END
          break;

        case Tag.BEGIN: // '{' in Esercizio 3.2, BEGIN in Esercizio 4
          match(Tag.BEGIN);
          statlist();
          match(Tag.END);
          break;

        default:
          error("Error in stat, unrecognized statement starting with " + look.tag);
	     }
    }

    private void if_statp() { // Gestisce la parte opzionale 'else stat end' o solo 'end' per l'IF
      //if_statp -> else stat end     guida {ELSE}
      //if_statp -> end               guida {END}
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
          error("Error in if_statp, expected ELSE or END, found " + look.tag);
	     }
    }

    private void idlist() {
      //idlist -> ID idlistp
      if (look.tag == Tag.ID){
        match(Tag.ID);
        idlistp();
      }else{
        error("Error in idlist, expected ID, found " + look.tag);
      }
    }

    private void idlistp() {
      //idlistp -> , ID idlistp   guida {,}
      //idlistp -> epsilon      guida {), ; , EOF, END}
      switch (look.tag){
        case ',':
          match(Token.comma.tag);
          match(Tag.ID);
          idlistp();
          break;
        case ')': // Fine di una lista di ID in read() o print()
        case ';': // Fine di un'istruzione
        case Tag.EOF:
        case Tag.END: // Fine di un blocco
          break;
        default:
          error("Error in idlistp, expected ',' or end of list/statement, found " + look.tag);
	     }
    }

    private void bexpr() {
      //bexpr -> expr RELOP expr  (Semplificato rispetto a Esercizio 3.2 che ha RELOP expr expr)
      // Guida: {NUM, ID, (}
      expr();
      if (look.tag == Tag.RELOP){
        match(Tag.RELOP);
        expr();
      }else{
        error("Error in bexpr, expected RELOP, found " + look.tag);
      }
    }

    private void expr() {
      // Utilizziamo la struttura di expr, term, fact dell'originale Valutatore.java (aritmetica infissa)
      // Questo è diverso da Esercizio 3.2 Parser.java, ma mantiene la capacità di Valutatore
      // Per semplicità, le funzioni non restituiscono valori (parsing puro)
      // Guida: {(, NUM, ID}
      if (look.tag == '(' || look.tag == Tag.NUM || look.tag == Tag.ID) {
          term();
          exprp();
      } else {
          error("Error in expr, expected '(', NUM or ID, found " + look.tag);
      }
    }

    private void exprp() {
      //exprp -> + term exprp | - term exprp | epsilon
      // Guida: {+, -, ), ;, RELOP, EOF, END}
      switch (look.tag) {
        case '+':
          match(Token.plus.tag);
          term();
          exprp();
          break;
        case '-':
          match(Token.minus.tag);
          term();
          exprp();
          break;
        case ')':
        case ';':
        case Tag.RELOP:
        case Tag.EOF:
        case Tag.END: // Aggiunto per coerenza con statlistp e idlistp
        case Tag.TO: // Per 'assign expr TO idlist'
        case Tag.DO: // Per 'for (...) DO stat'
          break; // Epsilon
        default:
          error("Error in exprp, unexpected token " + look.tag);
	     }
    }

    private void term() {
      //term -> fact termp
      // Guida: {(, NUM, ID}
      if (look.tag == '(' || look.tag == Tag.NUM || look.tag == Tag.ID) {
          fact();
          termp();
      } else {
          error("Error in term, expected '(', NUM or ID, found " + look.tag);
      }
    }

    private void termp() {
      //termp -> * fact termp | / fact termp | epsilon
      // Guida: {*, /, +, -, ), ;, RELOP, EOF, END}
      switch (look.tag){
        case '*':
          match(Token.mult.tag);
          fact();
          termp();
          break;
        case '/':
          match(Token.div.tag);
          fact();
          termp();
          break;
        case '+':
        case '-':
        case ')':
        case ';':
        case Tag.RELOP:
        case Tag.EOF:
        case Tag.END:
        case Tag.TO:
        case Tag.DO:
          break; // Epsilon
        default:
          error("Error in termp, unexpected token " + look.tag);
      }
    }

    private void fact() {
      //fact -> (expr) | NUM | ID
      // Guida: {(, NUM, ID}
      switch (look.tag) {
        case '(':
          match('(');
          expr();
          match(')');
          break;
        case Tag.NUM:
            match(Tag.NUM);
            break;
        case Tag.ID:
            match(Tag.ID);
            break;
        default:
            error ("Error in fact, expected '(', NUM or ID, found " + look.tag);
      }
    }
    
    private void exprlist() {
      //exprlist -> expr exprlistp
      // Guida: {(, NUM, ID}
      if (look.tag == '(' || look.tag == Tag.NUM || look.tag == Tag.ID) {
          expr();
          exprlistp();
      } else {
          error("Error in exprlist, expected expression, found " + look.tag);
      }
    }

    private void exprlistp() {
      //exprlistp -> , expr exprlistp | epsilon
      // Guida: {,, )}
      switch (look.tag) {
        case ',':
          match(Token.comma.tag);
          expr();
          exprlistp();
          break;
        case ')':
          break;
        default:
            error ("Error in exprlistp, expected ',' or ')', found " + look.tag);
      }
    }

    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "file.txt"; // Il percorso del file da leggere
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Valutatore parser = new Valutatore(lex, br); // Modificato da Parser a Valutatore
            parser.prog(); // Chiamata a prog() invece di start()
            System.out.println("Input OK");
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Error e) {
            System.err.println(e.getMessage());
        }
    }
}
