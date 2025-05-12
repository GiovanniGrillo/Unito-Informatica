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
    	} else
          error("syntax error");
    }

    public void prog() {
      //prog -> statlist EOF     guida {assign,print,read,while,if,{ }
      switch (look.tag){
        case Tag.ASSIGN:
  	       statlist();
  	       match(Tag.EOF);
           break;

        case Tag.PRINT:
          statlist();
          match(Tag.EOF);
          break;

        case Tag.READ:
          statlist();
          match(Tag.EOF);
          break;

        case Tag.FOR:
          statlist();
          match(Tag.EOF);
          break;

        case Tag.IF:
          statlist();
          match(Tag.EOF);
          break;

        case '{':
          statlist();
          match(Tag.EOF);
          break;

      default:
        error("Error in prog");
      }
    }

    private void statlist() {
      //statlist -> stat statlistp   guida {assign,print,read,while,if,{ }
      switch (look.tag) {
        case Tag.ASSIGN :
          stat();
          statlistp();
          break;

        case Tag.PRINT :
          stat();
          statlistp();
          break;

        case Tag.READ :
          stat();
          statlistp();
          break;

        case Tag.FOR:
          stat();
          statlistp();
          break;

        case Tag.IF :
          stat();
          statlistp();
          break;

        case '{' :
          stat();
          statlistp();
          break;

        default:
          error("Error in statlist");
	     }
    }

    private void statlistp() {
      //statlistp -> ; stat statlistp   guida {;}
      //statlistp -> epsilon            guida {eof, } }
      switch (look.tag){
        case ';':
          match(Token.semicolon.tag);
          stat();
          statlistp();
          break;

        case Tag.EOF:
          break;

        case '}':
          break;

        default:
          error("Error in statlistp");
       }
    }

    private void stat() {
      //stat -> assign expr to idlist     guida {assign}
      //stat -> print (exprlist)     guida {print}
      //stat -> read (idlist)       guida {read}
      //stat -> assign ID := expr to expr do stat end guida {assign} - Updated for FOR
      //stat -> print (exprlist)     guida {print}
      //stat -> read (idlist)       guida {read}
      //stat -> for ID assign expr to expr do stat end guida {for}
      //stat -> if (bexpr) stat [else stat] end  guida{if}
      //stat -> {statlist} guida {}}
      switch (look.tag) {
        case Tag.ASSIGN:
          match(Tag.ASSIGN);
          expr();
          match(Tag.TO);
          idlist();
          break;

        case Tag.PRINT:
          match(Tag.PRINT);
          match ('(');
          exprlist();
          match (')');
          break;

        case Tag.READ:
          match(Tag.READ);
          match ('(');
          idlist();
          match (')');
          break;

        case Tag.FOR:
          match(Tag.FOR);
          match('(');
          match(Tag.ID);
          match(Tag.INIT); // := 
          expr(); // Valore iniziale
          match(';');
          bexpr(); // Condizione
          match(')');
          match(Tag.DO);
          stat();
          // NESSUN match(Tag.END) qui, gestito da statp o non necessario per FOR
          break;

        case Tag.IF:
          match(Tag.IF);
          match ('(');
          bexpr();
          match (')');
          stat();
          statp();
          break;

        case '{':
          match ('{');
          statlist();
          match ('}');
          break;

        default:
          error("Error in stat");
	     }
    }

    private void statp() { // Gestisce la parte opzionale 'else stat end' o solo 'end' per l'IF
      //statp -> else stat end     guida {else}
      //statp -> end               guida {end}
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
          error("Error in statp");
	     }
    }

    private void idlist() {
      //idlist -> ID idlistp   guida {ID}
      if (look.tag == Tag.ID){
        match(Tag.ID);
        idlistp();
      }else{
        error("Error in idlist");
      }
    }

    private void idlistp() {
      //idlist -> , ID idlistp   guida {,}
      //idlistp -> epsilon      guida {) ; eof, end, else, } }
      switch (look.tag){
        case ',':
          match(Token.comma.tag);
          match(Tag.ID);
          idlistp();
          break;

        case ')' :
          break;

        case ';':
          break;

        case Tag.EOF:
          break;



        case '}':
          break;

        default:
          error("Error in idlistp");
	     }
    }

    private void bexpr() {
      //idlist -> relop expr expr  guida {RELOP}
      if (look.tag == Tag.RELOP){
        match(Tag.RELOP);
        expr();
        expr();
      }else{
        error("Error in bexpr");
      }
    }

    private void expr() {
      //expr -> + (exprlist)      guida {+}
      //expr -> - expr expr       guida {-}
      //expr -> * (exprlist)      guida {*}
      //expr -> / expr expr       guida {/}
      //expr -> NUM               guida {NUM}
      //expr -> ID                guida {ID}
      switch (look.tag){
        case '+':
          match(Token.plus.tag);
          match ('(');
          exprlist();
          match (')');
          break;

        case '-':
          match(Token.minus.tag);
          expr();
          expr();
          break;

        case '*':
          match(Token.mult.tag);
          match ('(');
          exprlist();
          match (')');
          break;

        case '/':
          match(Token.div.tag);
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
          error("Error in expr");
      }
    }

    private void exprlist() {
      //exprlist -> expr exprlistp  guida {+,-,*,/,num,id}
      switch (look.tag){
        case '+' :
          expr();
          exprlistp();
          break;

        case '-' :
          expr();
          exprlistp();
          break;

        case '*' :
          expr();
          exprlistp();
          break;

        case '/' :
          expr();
          exprlistp();
          break;

        case Tag.NUM:
          expr();
          exprlistp();
          break;

        case Tag.ID :
          expr();
          exprlistp();
          break;

        default:
          error("Error in expr");
      }
    }

    private void exprlistp() {
      //exprlistp -> , expr esprlistp   guida {,}
      //exprlistp -> epsilon            guida {)}
      switch (look.tag) {
        case ',':
          match(Token.comma.tag);
          expr();
          exprlistp();
          break;

        case ')':
          break;

        default:
            error ("error in exprlisp");
      }
    }

    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "factorial.lft"; // il percorso del file da leggere
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
