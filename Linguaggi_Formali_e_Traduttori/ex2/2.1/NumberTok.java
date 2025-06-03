public class NumberTok extends Token {
    public int num;

    public NumberTok(int tag, int n) {
        super(tag);
        num = n;
    }

    public String toString() {
        return "<" + tag + ", " + num + ">";
    }
}