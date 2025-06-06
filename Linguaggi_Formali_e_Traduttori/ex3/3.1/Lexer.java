import java.io.*;
import java.util.*;

public class Lexer {
    public static int line = 1;
    private char peek = ' ';

    private void readch(BufferedReader br) {
        try {
            peek = (char) br.read();
        } catch (IOException exc) {
            peek = (char) -1;
        }
    }

    public Token lexical_scan(BufferedReader br) {
        while (peek == ' ' || peek == '\t' || peek == '\n' || peek == '\r') {
            if (peek == '\n') line++;
            readch(br);
        }

        switch (peek) {
            case '!':
                peek = ' ';
                return Token.not;

            case '(':
                peek = ' ';
                return Token.lpt;

            case ')':
                peek = ' ';
                return Token.rpt;

            case '[':
                peek = ' ';
                return Token.lpq;

            case ']':
                peek = ' ';
                return Token.rpq;

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
                // Gestione dei commenti
                readch(br);
                if (peek == '*') {
                    // Commento multi-riga /* ... */
                    readch(br);
                    boolean commento_terminato = false;

                    while (!commento_terminato && peek != (char)-1) {
                        if (peek == '*') {
                            readch(br);
                            if (peek == '/') {
                                commento_terminato = true;
                                readch(br);
                            }
                        } else {
                            if (peek == '\n') line++;  // Conta le linee nei commenti
                            readch(br);
                        }
                    }

                    if (!commento_terminato) {
                        System.err.println("Errore: commento non chiuso");
                        return null;
                    }

                    // Ritorna il prossimo token dopo aver saltato il commento
                    return lexical_scan(br);
                } else if (peek == '/') {
                    // Commento di linea // ...
                    do {
                        readch(br);
                    } while (peek != '\n' && peek != (char)-1);

                    // Ritorna il prossimo token dopo aver saltato il commento
                    return lexical_scan(br);
                } else {
                    // È un normale operatore di divisione
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
                    peek = ' ';
                    return Word.and;
                } else {
                    System.err.println("Carattere errato dopo & : " + peek);
                    return null;
                }

            case '|':
                readch(br);
                if (peek == '|') {
                    peek = ' ';
                    return Word.or;
                } else {
                    System.err.println("Carattere errato dopo | : " + peek);
                    return null;
                }

            case '<':
                readch(br);
                if (peek == '=') {
                    peek = ' ';
                    return Word.le;
                } else if (peek == '>') {
                    peek = ' ';
                    return Word.ne;
                } else {
                    return Word.lt;
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
                    System.err.println("Carattere errato dopo = : " + peek);
                    return null;
                }

            case ':':
                readch(br);
                if (peek == '=') {
                    peek = ' ';
                    return Word.init;
                } else {
                    System.err.println("Carattere errato dopo : : " + peek);
                    return null;
                }

            case (char)-1:
                return new Token(Tag.EOF);

            default:
                if (Character.isLetter(peek)) {
                    // Identificatore che inizia con lettera
                    String lexeme = "";
                    lexeme += peek;
                    readch(br);

                    // Accetta anche underscore all'interno degli identificatori
                    while (Character.isLetterOrDigit(peek) || peek == '_') {
                        lexeme += peek;
                        readch(br);
                    }

                    switch (lexeme) {
                        case "assign":
                            return Word.assign;
                        case "to":
                            return Word.to;
                        case "if":
                            return Word.iftok;
                        case "else":
                            return Word.elsetok;
                        case "do":
                            return Word.dotok;
                        case "for":
                            return Word.fortok;
                        case "begin":
                            return Word.begin;
                        case "end":
                            return Word.end;
                        case "print":
                            return Word.print;
                        case "read":
                            return Word.read;
                        default:
                            // Verifica se la parola è composta solo da underscore
                            boolean solo_underscore = true;
                            for (int i = 0; i < lexeme.length(); i++) {
                                if (lexeme.charAt(i) != '_') {
                                    solo_underscore = false;
                                    break;
                                }
                            }

                            if (solo_underscore) {
                                System.err.println("Errore: identificatore composto solo da underscore");
                                return null;
                            } else {
                                return new Word(Tag.ID, lexeme);
                            }
                    }
                } else if (peek == '_') {
                    // ex2.2: Identificatore che inizia con underscore
                    String lexeme = "";

                    // Leggi tutti gli underscore iniziali
                    do {
                        lexeme += peek;
                        readch(br);
                    } while (peek == '_');

                    // Verifica che ci sia almeno una lettera o cifra dopo gli underscore
                    if (Character.isLetterOrDigit(peek)) {
                        // Continua a leggere il resto dell'identificatore
                        do {
                            lexeme += peek;
                            readch(br);
                        } while (Character.isLetterOrDigit(peek) || peek == '_');

                        return new Word(Tag.ID, lexeme);
                    } else {
                        // Identificatore composto solo da underscore - non valido
                        System.err.println("Errore: identificatore composto solo da underscore");
                        return null;
                    }
                } else if (Character.isDigit(peek)) {
                    // ex2.1: Gestione numeri
                    if (peek == '0') {
                        readch(br);
                        return new NumberTok(Tag.NUM, 0);
                    } else {
                        int num = 0;
                        do {
                            num = num * 10 + Character.digit(peek, 10);
                            readch(br);
                        } while (Character.isDigit(peek));

                        return new NumberTok(Tag.NUM, num);
                    }
                } else {
                    System.err.println("Carattere errato: " + peek);
                    return null;
                }
        }
    }

    public static void main(String[] args) {
        Lexer lex = new Lexer();
        String path = "file.txt";

        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            Token tok;
            do {
                tok = lex.lexical_scan(br);
                if (tok == null)
                    break;
                System.out.println("Scan: " + tok);
            } while (tok.tag != Tag.EOF);
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}