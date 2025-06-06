public class ex1_2 {
    public static boolean scan(String s) {
        int state = 0, i = 0;

        while (state >= 0 && i < s.length()) {
            final char ch = s.charAt(i++);

            switch (state) {
                case 0:
                    if (ch >= '0' && ch <= '9')
                        state = 3;
                    else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
                        state = 1;
                    else if (ch == '_')
                        state = 2;
                    else
                        state = -1;
                    break;

                case 1:
                    if ((ch >= '0' && ch <= '9') ||
                        (ch >= 'a' && ch <= 'z') ||
                        (ch >= 'A' && ch <= 'Z') ||
                        (ch == '_'))
                        state = 1;
                    else
                        state = -1;
                    break;

                case 2:
                    if (ch >= '0' && ch <= '9')
                        state = 1;
                    else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
                        state = 1;
                    else if (ch == '_')
                        state = 2;
                    else
                        state = -1;
                    break;
            }
        }
        return state == 1;
    }

    public static void main(String[] args) {
        System.out.println("Stringhe riconosciute");
        System.out.println(scan("x")        ? "OK" : "NOPE"); // OK
        System.out.println(scan("flag1")    ? "OK" : "NOPE"); // OK
        System.out.println(scan("x2y2")     ? "OK" : "NOPE"); // OK
        System.out.println(scan("x_1")      ? "OK" : "NOPE"); // OK
        System.out.println(scan("lft_lab")  ? "OK" : "NOPE"); // OK
        System.out.println(scan("temp_")    ? "OK" : "NOPE"); // OK
        System.out.println(scan("x_1_y_2_") ? "OK" : "NOPE"); // OK
        System.out.println(scan("x___")     ? "OK" : "NOPE"); // OK
        System.out.println(scan("___Pippo") ? "OK" : "NOPE"); // OK

        System.out.println("\nStringhe NON riconosciute");
        System.out.println(scan("5")        ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("221B")     ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("123")      ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("9_to_5")   ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("___")      ? "OK" : "NOPE"); // NOPE
    }
}