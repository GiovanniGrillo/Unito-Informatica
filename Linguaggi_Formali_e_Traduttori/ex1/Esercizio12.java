public class Esercizio12
{
    public static boolean scan(String s)
    {
	int state = 0;
	int i = 0;

	while (state >= 0 && i < s.length()) {
	    final char ch = s.charAt(i++);

	    switch (state) {
	    case 0:
		    if (ch >= '0' && ch<='9')
		      state = 3;
		    else if (ch >='a' && ch<='z'|| ch>='A' && ch<='Z')
		      state = 1;
        else if (ch == '_')
          state = 2; //1
        else
          state = -1;
		    break;

      case 1:
        if (ch >= '0' && ch<='9')
          state = 1;
        else if (ch >= 'a' && ch<='z'|| ch>='A' && ch<='Z')
          state = 1;
        else if (ch == '_')
          state = 1; //2
        else
          state = -1;
        break;

    case 2:
      if (ch >= '0' && ch<='9')
        state = 1;
      else if (ch >= 'a' && ch<='z'|| ch>='A' && ch<='Z')
        state = 1;
      else if (ch == '_')
        state = 2;//4
      else
        state = -1;
      break;
    }
  }

   return state == 1;
   }

    public static void main(String[] args){
       System.out.println("Stringhe riconosciute"); //si
       System.out.println(scan("x") ? "OK" : "NOPE"); //si
       System.out.println(scan("flag1") ? "OK" : "NOPE"); //si
       System.out.println(scan("x2y2") ? "OK" : "NOPE"); //si
       System.out.println(scan("x_1") ? "OK" : "NOPE"); //si
       System.out.println(scan("lft_lab") ? "OK" : "NOPE"); //si
       System.out.println(scan("temp_") ? "OK" : "NOPE"); //si
       System.out.println(scan("x_1_y_2_") ? "OK" : "NOPE"); //si
       System.out.println(scan("x___") ? "OK" : "NOPE"); //si
       System.out.println(scan("___Pippo") ? "OK" : "NOPE"); //si
       System.out.println("Stringhe NON riconosciute"); //si
       System.out.println(scan("5") ? "OK" : "NOPE"); //no
       System.out.println(scan("221B") ? "OK" : "NOPE"); //no
       System.out.println(scan("123") ? "OK" : "NOPE"); //no
       System.out.println(scan("9_to_5") ? "OK" : "NOPE"); //no
       System.out.println(scan("___") ? "OK" : "NOPE"); //no

     }
}
