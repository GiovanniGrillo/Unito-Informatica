import java.io.*;
import java.util.*;

public class Lexer1 {

    public static int line = 1;
    private char peek = ' ';

    private void readch(BufferedReader br) {
        try {
            peek = (char) br.read();
        } catch (IOException exc) {
            peek = (char) -1; // ERROR
        }
    }

    public Token lexical_scan(BufferedReader br) {
        while (peek == ' ' || peek == '\t' || peek == '\n'  || peek == '\r') {
            if (peek == '\n') line++;
            readch(br);
        }

        switch (peek) {
            case '!':
                peek = ' ';
                return Token.not;

	// ... gestire i casi di ( ) { } + - * / ; , ... //
            case '(':
                peek = ' ';
                return Token.lpt;

            case ')':
                peek = ' ';
                return Token.rpt;

            case '{':
                peek = ' ';
                return Token.lpg;

            case '}':
                peek = ' ';
                return Token.rpg;

            case '+':
                peek = ' ';
                return Token.plus;

            case '-':
                peek = ' ';
                return Token.minus;

            case '*':
                peek = ' ';
                return Token.mult;

            case '/':
                peek = ' ';
                return Token.div;

            case ';':
                peek = ' ';
                return Token.semicolon;

              case ',':
                  peek = ' ';
                  return Token.comma;

              case '&':
                  readch(br);
                  if (peek == '&') {
                      peek = ' '; //metto ' ' per poter proseguire il ciclo
                      return Word.and;
                  } else {
                      System.err.println("Erroneous character" + " after & : "  + peek );
                      return null;
                  }

  	// ... gestire i casi di || < > <= >= == <> ... //

              case '|':
                     readch(br);
                     if (peek == '|') {
                         peek = ' ';
                         return Word.or;
                     } else {
                         System.err.println("Erroneous character" + " after & : "  + peek );
                         return null;
                     }

               case '<':
                   readch(br);
                     if (peek == '=') {
                         peek = ' ';
                         return Word.le;
                     } else {
                       if (peek == '>'){
                         peek = ' ';
                         return Word.ne;
                       }else {
                         return Word.lt;
                       }
                   }

               case '>':
                   readch(br);
                     if (peek == '=') {
                         peek = ' ';
                         return Word.ge;
                     } else {
                         return Word.gt;
                       }

               case '=':
                   readch(br);
                   if (peek == '=') {
                       peek = ' ';
                       return Word.eq;
                   } else {
                       return null;
                   }

            case (char)-1:
                return new Token(Tag.EOF);

            default:
                if (Character.isLetter(peek)) {
	// ... gestire il caso degli identificatori e delle parole chiave //
               String parola = "";
               parola = parola + peek; //metto nella stringa parola il carattere
               readch(br);//leggi il simbolo dopo

               while(Character.isLetter(peek) || Character.isDigit(peek) || peek == '_'){ //finche il simbolo che leggo è una lettera o un numero
                  parola = parola + peek; //continuo ad aggiungere
                  readch(br);
               }

               if (parola.equals("assign")){
                 return Word.assign;
               }
               else if(parola.equals("to")){
                  return Word.to;
               }
               else if (parola.equals("if")){
                 return Word.iftok;
               }
               else if (parola.equals("else")){
                return Word.elsetok;
               }
               else if (parola.equals("while")){
                return Word.whiletok;
               }
               else if (parola.equals("begin")){
                return Word.begin;
               }
               else if (parola.equals("end")){
                return Word.end;
               }
               else if (parola.equals("print")){
                return Word.print;
               }
               else if (parola.equals("read")){
                return Word.read;
               }
               else {
                Word ret = new Word (Tag.ID, parola);
                return ret;
              }

               } else if (Character.isDigit(peek)) {
	               // ... gestire il caso dei numeri ... //
                  String numero = "";
                  numero = numero + peek; //metto nella stringa parola il carattere
                  readch(br);//leggo il simbolo successivo
                  while(Character.isDigit(peek)){ //finche il simbolo che leggo è una lettera o un numero
                     numero = numero + peek; //continuo ad aggiungere al numero il peek
                     readch(br);
                  }
                  //tradurre "numero" in un intero
                  int num = Integer.parseInt(numero);
                  NumberTok ret = new NumberTok (Tag.NUM, num);
                  return ret;
                  } else {
                          System.err.println("Erroneous character: " + peek );
                          return null;
                  }
         }

    }

    public static void main(String[] args) {
        Lexer1 lex = new Lexer1();
        String path = "file1.txt";
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Token tok;
            do {
                tok = lex.lexical_scan(br);
                System.out.println("Scan: " + tok);
            } while (tok.tag != Tag.EOF);
            br.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

}
