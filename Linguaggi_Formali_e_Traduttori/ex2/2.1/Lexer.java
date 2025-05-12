import java.io.*;
import java.util.*;

public class Lexer {
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
        while (peek == ' ' || peek == '\t' || peek == '\n' || peek == '\r') {
            if (peek == '\n') line++;
            readch(br);
        }
        
        switch (peek) {
            case '!':
                peek = ' ';
                return Token.not;
                
            // Gestione caratteri singoli
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
                peek = ' ';
                return Token.div;
                
            case ';':
                peek = ' ';
                return Token.semicolon;
                
            case ',':
                peek = ' ';
                return Token.comma;
                
            // Gestione operatori composti
            case '&':
                readch(br);
                if (peek == '&') {
                    peek = ' ';
                    return Word.and;
                } else {
                    System.err.println("Erroneous character after & : " + peek);
                    return null;
                }
                
            case '|':
                readch(br);
                if (peek == '|') {
                    peek = ' ';
                    return Word.or;
                } else {
                    System.err.println("Erroneous character after | : " + peek);
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
                    System.err.println("Erroneous character after = : " + peek);
                    return null;
                }
                
            case ':':
                readch(br);
                if (peek == '=') {
                    peek = ' ';
                    return Word.init;
                } else {
                    System.err.println("Erroneous character after : : " + peek);
                    return null;
                }
                
            case (char)-1:
                return new Token(Tag.EOF);
                
            default:
                // Gestione identificatori e parole chiave
                if (Character.isLetter(peek)) {
                    StringBuilder buffer = new StringBuilder();
                    do {
                        buffer.append(peek);
                        readch(br);
                    } while (Character.isLetterOrDigit(peek));
                    
                    String s = buffer.toString();
                    
                    switch (s) {
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
                            return new Word(Tag.ID, s);
                    }
                    
                // Gestione numeri
                } else if (Character.isDigit(peek)) {
                    // Se inizia con 0, può essere solo 0
                    if (peek == '0') {
                        readch(br);
                        return new NumberTok(Tag.NUM, 0);
                    } else { // Se inizia con 1-9, può essere seguito da 0-9
                        int num = 0;
                        do {
                            num = num * 10 + Character.digit(peek, 10);
                            readch(br);
                        } while (Character.isDigit(peek));
                        
                        return new NumberTok(Tag.NUM, num);
                    }
                    
                } else {
                    System.err.println("Erroneous character: " + peek);
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