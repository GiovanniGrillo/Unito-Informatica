import java.io.*;
import java.util.*;

public class Lexer2 {

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
            //ESERCIZIO 2.3 RICONOSCO COMMENTI
              readch(br);
              if (peek == '*'){
                readch(br);
                int commentoTerminato = 0;//il commento è terminato quando trovo */, se lo trovo metto commentoTerminato = 1
              while(commentoTerminato==0 && (peek!=(char)-1) ){ //vado avanti finchè non trovo */ 
              if (peek == '*'){
                readch(br); //ho trovato un asterisco, leggo il prossimo carattere e controllo se e' /
              if(peek=='/'){ //ho letto */, il commento e' terminato
                   commentoTerminato = 1; //io metto commentoTerminato = 1 solo quando trovo */ ovvero quando chiudono un commento
              }
                }else{
                  readch(br);
                }
              }
                if (commentoTerminato ==0 ){ //se commentoTerminato è uguale a 0 non è stato chiuso il comment
                  System.err.println("Errore: non e' stato chiuso il commento");
                  return null;
                }
                peek=' ';
                return lexical_scan(br);
              }else if (peek == '/'){
              while (peek != '\n'){ // sono in questo tipo di commento, ignoro quello che viene scritto finchè non vado a capo
                readch(br); //leggo e scorro la stringa
              }
              peek = ' ';
              return lexical_scan(br);
              }else{
                return Token.div;
              }

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
               parola = parola + peek;
               readch(br);

               while(Character.isLetter(peek) || Character.isDigit(peek) || peek == '_'){
                  parola = parola + peek;
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
            }else{

              //ESERCIZIO 2.2
              int stringaOk = 0; //se ho solo underscore metto a 1
              int i=0; //lo uso per scorrere la lunghezza parola , length restituisce la lunghezza della parola
              while(i<parola.length()){ //ciclo da 0 a lunghezza della parola
                if (parola.charAt(i) != '_'){
                  stringaOk=1;
                }
                i++;
              }
              if (stringaOk == 0){
                System.err.println("Error : la sringa è composta da soli underscore " + peek );
                return null;
              }else{
                Word ret = new Word (Tag.ID, parola);
                return ret;
              }
            }

              } else if (Character.isDigit(peek)) {
	               // ... gestire il caso dei numeri ... //
                  String numero = "";
                  numero = numero + peek;
                  readch(br);
                  while(Character.isDigit(peek)){
                     numero = numero + peek;
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
        Lexer lex = new Lexer();
        String path = "file2.txt";
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Token tok;
            do {
                tok = lex.lexical_scan(br);
                System.out.println("Scan: " + tok);
            } while (tok.tag != Tag.EOF);
            br.close();
        } catch (IOException e) {e.printStackTrace();}
    }

}