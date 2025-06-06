public class ex1_1 {
    public static boolean scan(String s) {
        int state = 0, i = 0;

        while (state >= 0 && i < s.length()) {
            final char ch = s.charAt(i++);

            switch (state) {
                case 0:
                    if (ch == '0')
                        state = 1;
                    else if (ch == '1')
                        state = 0;
                    else
                        state = -1;
                    break;

                case 1:
                    if (ch == '0')
                        state = 2;
                    else if (ch == '1')
                        state = 0;
                    else
                        state = -1;
                    break;

                case 2:
                    if (ch == '0')
                        state = 3;
                    else if (ch == '1')
                        state = 0;
                    else
                        state = -1;
                    break;

                case 3:
                    if (ch == '0' || ch == '1')
                        state = 3;
                    else
                        state = -1;
                    break;
            }
        }
        return state == 0 || state == 1 || state == 2; // Stato finale accettante: 0, 1, 2
    }

    public static void main(String[] args) {
        // Testing esericizio originale
        System.out.println(scan("010101")     ? "OK" : "NOPE"); // OK
        System.out.println(scan("1100011001") ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("10214")      ? "OK" : "NOPE"); // NOPE

        // Altri test
        System.out.println(scan("00")         ? "OK" : "NOPE"); // OK (non ha 3 zeri consecutivi)
        System.out.println(scan("001")        ? "OK" : "NOPE"); // OK (non ha 3 zeri consecutivi)
        System.out.println(scan("000")        ? "OK" : "NOPE"); // NOPE (ha 3 zeri consecutivi)
    }
}