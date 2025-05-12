public class Word extends Token {
    public String lexeme = "";
    public Word(int tag, String s) { super(tag); lexeme=s; }
    public String toString() { return "<" + tag + ", " + lexeme + ">"; }
    public static final Word
	assign = new Word(Tag.ASSIGN, "assign"),
	to = new Word(Tag.TO, "to"),
	iftok = new Word(Tag.IF, "if"),
	elsetok = new Word(Tag.ELSE, "else"),
	fortok = new Word(Tag.FOR, "for"), // Sostituito whiletok con fortok
	dotok = new Word(Tag.DO, "do"), // Aggiunto dotok
	init = new Word(Tag.INIT, ":="), // Aggiunto init per l'assegnazione nel for
	begin = new Word(Tag.BEGIN, "begin"),
	end = new Word(Tag.END, "end"),
	print = new Word(Tag.PRINT, "print"),
	read = new Word(Tag.READ, "read"),
	or = new Word(Tag.OR, "||"),
	and = new Word(Tag.AND, "&&"),
	lt = new Word(Tag.RELOP, "<"),
	gt = new Word(Tag.RELOP, ">"),
	eq = new Word(Tag.RELOP, "=="),
	le = new Word(Tag.RELOP, "<="),
	ne = new Word(Tag.RELOP, "<>"),
	ge = new Word(Tag.RELOP, ">=");    
}
