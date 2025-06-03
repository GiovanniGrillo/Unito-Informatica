public class ex1_6 {
    public static boolean scan(String s) {
        int state = 0;
        int i = 0;

        while (state >= 0 && i < s.length()) {
            final char ch = s.charAt(i++);

            switch (state) {
                case 0:
                    if (ch == '/') {
                        state = 1;
                    } else if (ch == 'a' || ch == '*') {
                        state = 0;
                    } else {
                        state = -1;
                    }
                    break;

                case 1:
                    if (ch == '*') {
                        state = 2;
                    } else if (ch == '/') {
                        state = 1;
                    } else if (ch == 'a') {
                        state = 0;
                    } else {
                        state = -1;
                    }
                    break;

                case 2:
                    if (ch == '*') {
                        state = 3;
                    } else if (ch == 'a' || ch == '/') {
                        state = 2;
                    } else {
                        state = -1;
                    }
                    break;

                case 3:
                    if (ch == '/') {
                        state = 0;
                    } else if (ch == '*') {
                        state = 3;
                    } else if (ch == 'a') {
                        state = 2;
                    } else {
                        state = -1;
                    }
                    break;
            }
        }
        return state == 0 || state == 1;
    }

    public static void main(String[] args) {
        System.out.println("Stringhe accettate");
        System.out.println(scan("aaa/****/aa") ? "OK" : "NOPE");   // OK
        System.out.println(scan("aa/*a*a*/") ? "OK" : "NOPE");     // OK
        System.out.println(scan("aaaa") ? "OK" : "NOPE");          // OK
        System.out.println(scan("/****/") ? "OK" : "NOPE");        // OK
        System.out.println(scan("/*aa*/") ? "OK" : "NOPE");        // OK
        System.out.println(scan("*/a") ? "OK" : "NOPE");           // OK
        System.out.println(scan("a/**/***a") ? "OK" : "NOPE");     // OK
        System.out.println(scan("a/**/***/a") ? "OK" : "NOPE");    // OK
        System.out.println(scan("a/**/aa/***/a") ? "OK" : "NOPE"); // OK
        
        System.out.println("\nStringhe non accettate");
        System.out.println(scan("aaa/*/aa") ? "OK" : "NOPE");      // NOPE
        System.out.println(scan("a/**//***a") ? "OK" : "NOPE");    // NOPE
        System.out.println(scan("aa/*aa") ? "OK" : "NOPE");        // NOPE
    }
}