public class ex1_4 {
    public static boolean scan(String s) {
        int state = 0, i = 0;

        while (state >= 0 && i < s.length()) {
            final char ch = s.charAt(i++);

            switch (state) {
                case 0: // Stato iniziale
                    if (ch >= '0' && ch <= '9')
                        state = 1;
                    else if (ch == '+' || ch == '-')
                        state = 3;
                    else if (ch == '.')
                        state = 2;
                    else
                        state = -1;
                    break;

                case 1: //Letto numero intero
                    if (ch >= '0' && ch <= '9')
                        state = 1;
                    else if (ch == 'e')
                        state = 5;
                    else if (ch == '.')
                        state = 2;
                    else
                        state = -1;
                    break;

                case 2: // Letto punto decimale
                    if (ch >= '0' && ch <= '9')
                        state = 4;
                    else
                        state = -1;
                    break;

                case 3: // Letto segno iniziale
                    if (ch >= '0' && ch <= '9')
                        state = 1;
                    else if (ch == '.')
                        state = 2;
                    else
                        state = -1;
                    break;

                case 4: // Letto numero decimale
                    if (ch >= '0' && ch <= '9')
                        state = 4;
                    else if (ch == 'e')
                        state = 5;
                    else
                        state = -1;
                    break;

                case 5: // Letto 'e' per notazione scientifica
                    if (ch >= '0' && ch <= '9')
                        state = 6;
                    else if (ch == '.')
                        state = 8;
                    else if (ch == '+' || ch == '-')
                        state = 7;
                    else
                        state = -1;
                    break;

                case 6: // Letto esponente positivo
                    if (ch >= '0' && ch <= '9')
                        state = 6;
                    else if (ch == '.')
                        state = 8;
                    else
                        state = -1;
                    break;

                case 7: // Letto segno dopo 'e'
                    if (ch >= '0' && ch <= '9')
                        state = 6;
                    else if (ch == '.')
                        state = 8;
                    else
                        state = -1;
                    break;

                case 8: // Punto dopo 'e'
                    if (ch >= '0' && ch <= '9')
                        state = 4;
                    else
                        state = -1;
                    break;
            }
        }
        return state == 1 || state == 4 || state == 6;
    }

    public static void main(String[] args) {
        System.out.println("Stringhe riconosciute:");
        System.out.println(scan("123")   ? "OK" : "NOPE"); // OK
        System.out.println(scan("123.5") ? "OK" : "NOPE"); // OK
        System.out.println(scan(".567")  ? "OK" : "NOPE"); // OK
        System.out.println(scan("+7.5")  ? "OK" : "NOPE"); // OK
        System.out.println(scan("-.7")   ? "OK" : "NOPE"); // OK
        System.out.println(scan("67e10") ? "OK" : "NOPE"); // OK
        System.out.println(scan("1e-2")  ? "OK" : "NOPE"); // OK
        System.out.println(scan("-.7e2") ? "OK" : "NOPE"); // OK
        System.out.println(scan("1e2.3") ? "OK" : "NOPE"); // OK (roba strana ma accettata)

        System.out.println("\nStringhe NON riconosciute:");
        System.out.println(scan(".")     ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("e3")    ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("123.")  ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("+e6")   ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("1.2.3") ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("4e5e6") ? "OK" : "NOPE"); // NOPE
        System.out.println(scan("++3")   ? "OK" : "NOPE"); // NOPE
    }
}