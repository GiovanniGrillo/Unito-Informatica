public class Esercizio13bis
{
    public static boolean scan(String s)
    {
	int state = 0;
	int i = 0;

	while (state >= 0 && i < s.length()) {
	    final char ch = s.charAt(i);

	    switch (state) {

      case 0:
    		if(ch=='0' || ch == '2' || ch == '4' || ch== '6' || ch =='8'){
    		    state = 1;
    		}else{
            if (ch == '1' || ch == '3' || ch== '5' || ch =='7' || ch =='9'){
      		    state = 2;
      		  }else{
      		    state = -1;
            }
        }
		break;

	    case 1:
      if(ch == '0' || ch == '2' || ch== '4' || ch =='6'|| ch =='8'){
        state =1;
		  }else{
         if(ch == '1' || ch == '3' || ch== '5' || ch =='7'|| ch =='9'){
      		    state = 2;
          }else{
               if (ch >='l'&& ch <='z'){
              state = 3;
          }else{
              if (ch >='L'&& ch <='Z'){
                state = 3;
             }else{
      		    state = -1;
            }
          }
        }
      }
		break;

    case 2:
      if (ch == '1' || ch == '3' || ch== '5' || ch =='7'|| ch =='9'){
		    state = 2;
      }else{
           if (ch == '2' || ch == '4' || ch== '6' || ch =='8'){
          state = 1;
        }else{
           if (ch >='a'&& ch <='k'){
          state = 3;
        }else{
          if (ch >='A'&& ch <='K'){
            state = 3;
        }else{
          state = -1;
        }
        }
      }
    }
  break;

	    case 3:
    		if (ch >='a' || ch<='k' && ch >='A' || ch<='K'){
    		    state = 3;
    		}else{
           if (ch>='l' || ch<='z' && ch>='L' || ch<='Z'){
    		    state = 3;
        }else{
          state = -1;
        }
        }
		break;


	    }
      i++;
	}
	return state == 3;
    }

    public static void main(String[] args){
       System.out.println("Strighe riconosciute");
	     System.out.println(scan("654321Bianchi") ? "OK" : "NOPE"); //si
       System.out.println(scan("123456Rossi") ? "OK" : "NOPE"); //si
       System.out.println("Strighe non riconosciute");
       System.out.println(scan("123456Bianchi") ? "OK" : "NOPE"); //no
       System.out.println(scan("654321Rossi") ? "OK" : "NOPE"); //no
    }
}
