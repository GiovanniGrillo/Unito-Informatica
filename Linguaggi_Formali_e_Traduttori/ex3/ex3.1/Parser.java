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

    public void start() {
      //start -> expr EOF     guida {(, num}
      if(look==Token.lpt||look.tag==Tag.NUM){
  	     expr();
  	     match(Tag.EOF);
      }else{
        error("Error in start");
      }
    }

    private void expr() {
      //expr -> term exprp   guida {(,num}
      if (look == Token.lpt || look.tag == Tag.NUM){
        term();
        exprp();
      }else{
        error("Error in Expr");
      }
    }

    private void exprp() {
      //exprp -> + term exprp     guida {+}
      //exprp -> - term exprp     guida {-}
      //exprp -> epsilon          guida {EOF,)}
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

        case Tag.EOF:
          break;

        case ')':
          break;

        default:
          error("Error in Exprp");
	     }
    }

    private void term() {
      //term -> fact termp    guida {(, num}
      if (look == Token.lpt || look.tag == Tag.NUM){
        fact();
        termp();
      }else{
        error("Error in Term");
      }
    }

    private void termp() {
      //termp -> * fact termp      guida {*}
      //termp -> - fact termp      guida {/}
      //termp -> epsilon           guida {+,-,EOF,)}
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

        case Tag.EOF:

        break;

        default:
          error("Error in Termp");
      }
    }

    private void fact() {
      //fact -> ( <expr> ) guida {(}
      //fact -> num    giuda {num}
      switch (look.tag) {
        case '(':
          match(Token.lpt.tag);
          expr();
          match(Token.rpt.tag);
          break;

        case Tag.NUM:
            match(Tag.NUM);
            break;

        default:
            error ("error in Fact");
      }
    }

    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "file.txt" ; // il percorso del file da leggere
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
