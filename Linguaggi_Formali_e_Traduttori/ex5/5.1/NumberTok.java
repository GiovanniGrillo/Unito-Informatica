public class NumberTok extends Token {
	public int lexeme;
    public NumberTok(int tag, String s) { super(tag); lexeme=Integer.parseInt(s); }
    public NumberTok(int tag, int n) { super(tag); lexeme=n; }
    public String toString() { return "<" + tag + ", " + lexeme + ">"; }
}
//non sono sicuro di questa parte da rivisitare