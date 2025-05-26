public class Esercizio1_3 {
    public static boolean scan(String s) {
        int state = 0;
        int i = 0;

        while (state >= 0 && i < s.length()) {
            final char ch = s.charAt(i++);

            switch (state) {
                case 0: // Stato iniziale
                    if (ch >= '0' && ch <= '9') {
                        if ((ch - '0') % 2 == 0) // Cifra pari
                            state = 1;
                        else // Cifra dispari
                            state = 2;
                    } else {
                        state = -1;
                    }
                    break;

                case 1: // Matricola pari
                    if (ch >= '0' && ch <= '9') {
                        state = 1; // Rimane pari se ultima cifra
                    } else if ((ch >= 'A' && ch <= 'K') || (ch >= 'a' && ch <= 'k')) {
                        state = 3; // T2: matricola pari + cognome A-K
                    } else {
                        state = -1;
                    }
                    break;

                case 2: // Matricola dispari
                    if (ch >= '0' && ch <= '9') {
                        state = 2; // Rimane dispari se ultima cifra
                    } else if ((ch >= 'L' && ch <= 'Z') || (ch >= 'l' && ch <= 'z')) {
                        state = 4; // T3: matricola dispari + cognome L-Z
                    } else {
                        state = -1;
                    }
                    break;

                case 3: // T2 - Accettante
                    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
                        state = 3;
                    } else {
                        state = -1;
                    }
                    break;

                case 4: // T3 - Accettante
                    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
                        state = 4;
                    } else {
                        state = -1;
                    }
                    break;
            }
        }

        return state == 3 || state == 4;
    }

    public static void main(String[] args) {
        System.out.println("Stringhe accettate (T2 e T3):");
        System.out.println(scan("123456Bianchi") ? "OK" : "NOPE");  // T2: OK
        System.out.println(scan("654321Rossi") ? "OK" : "NOPE");    // T3: OK
        System.out.println(scan("2Bianchi") ? "OK" : "NOPE");       // T2: OK
        System.out.println(scan("122B") ? "OK" : "NOPE");           // T2: OK
        
        System.out.println("\nStringhe non accettate:");
        System.out.println(scan("654321Bianchi") ? "OK" : "NOPE");  // No: dispari + A-K
        System.out.println(scan("123456Rossi") ? "OK" : "NOPE");    // No: pari + L-Z
        System.out.println(scan("654322") ? "OK" : "NOPE");         // No: solo numeri
        System.out.println(scan("Rossi") ? "OK" : "NOPE");          // No: solo cognome
        
        // Test aggiuntivi
        System.out.println("\nAltri test:");
        System.out.println(scan("1234Ferrero") ? "OK" : "NOPE");    // T2: OK
        System.out.println(scan("12345Zorro") ? "OK" : "NOPE");     // T3: OK
        System.out.println(scan("12345Ferrero") ? "OK" : "NOPE");   // No: dispari + A-K
    }
}