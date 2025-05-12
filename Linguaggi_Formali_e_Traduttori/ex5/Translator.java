import java.io.*;
import java.util.LinkedList;
import java.util.List;

public class Translator {
  private Lexer lex;
  private BufferedReader pbr;
  private Token look;

  SymbolTable st = new SymbolTable();
  CodeGenerator code = new CodeGenerator();
  int count=0;

  public Translator(Lexer l, BufferedReader br) {
    lex = l;
    pbr = br;
    move();
  }

  void move() {
    look = lex.lexical_scan(pbr);
    System.out.println("token = " + look);
  }

  void error(String s) {
		throw new Error("Near line " + lex.line + ": " + s);
  }

  void match(int t) {
    if (look.tag == t) {
      if (look.tag != Tag.EOF) move();
    } else
      error("syntax error");
    }


  public void prog() {
      statlist();
      match(Tag.EOF);
      try {
        code.toJasmin();
      }
      catch(java.io.IOException e) {
        System.out.println("IO error\n");
      }
  }


  private void statlist() {
      stat();
      statlistp();
  }


  private void statlistp() {
      switch (look.tag){
        case ';':
          match(';');
          stat();
          statlistp();
          break;
        case Tag.EOF:
          break;
        case '}':
          break;
        default:
          error("Error in statlistp");
       }
    }


  public void stat() {
      switch (look.tag) {
        case Tag.ASSIGN:
          match(Tag.ASSIGN);
          expr();
          match(Tag.TO);
          List<String> idl = idlist();
            for (int i = 0; i < idl.size(); i++) {
              if (i < idl.size() - 1) {
                code.emit(OpCode.dup);
              }
          int id_addr = st.lookupAddress(idl.get(i));
            if (id_addr == -1) {
              id_addr = count;
              st.insert(idl.get(i), count++);
            }
            code.emit(OpCode.istore, id_addr);
          }
          break;

        case Tag.PRINT:
          match(Tag.PRINT);
          match ('(');
          exprlist(new Instruction (OpCode.invokestatic, 1));
          code.emit(OpCode.invokestatic, 1);
          match (')');
          break;

        case Tag.READ:
          match(Tag.READ);
          match ('(');
          List<String> ids = idlist();
          match (')');
            for (String id : ids) {
              int id_addr = st.lookupAddress(id);
              if (id_addr == -1) {
                id_addr = count;
                st.insert(id, count++);
              }
              code.emit(OpCode.invokestatic, 0);
              code.emit(OpCode.istore, id_addr);
            }
          break;

        case Tag.FOR:
          match(Tag.FOR);
          match('(');
          // Gestione dell'inizializzazione: ID := <expr>
          Token id_token = look; // Salva il token ID
          match(Tag.ID);
          String varName = ((Word)id_token).lexeme;
          match(Tag.INIT); // Assumendo Tag.INIT per ':='
          expr(); // Valuta l'espressione, il risultato va sullo stack

          int id_addr = st.lookupAddress(varName);
          if (id_addr == -1) {
              id_addr = count;
              st.insert(varName, count++);
          }
          code.emit(OpCode.istore, id_addr); // Memorizza il valore iniziale nell'ID

          match(';');

          // Struttura del ciclo
          int condition_label = code.newLabel();
          int body_label = code.newLabel();
          int end_label = code.newLabel();

          code.emitLabel(condition_label); // Etichetta per il controllo della condizione

          // Condizione: <bexpr>
          // bexpr(true_target_label, false) significa: se la condizione e' vera, salta a true_target_label
          bexpr(body_label, false);
          code.emit(OpCode.GOto, end_label); // Se la condizione e' falsa (fall-through), esci dal ciclo

          match(')');
          match(Tag.DO);

          code.emitLabel(body_label); // Etichetta per il corpo del ciclo
          stat(); // Esegui il corpo del ciclo

          code.emit(OpCode.GOto, condition_label); // Salta indietro al controllo della condizione

          code.emitLabel(end_label); // Etichetta per la terminazione del ciclo
          break;

        case Tag.IF:
          int lnext_false = code.newLabel();
          int lnext_end = code.newLabel();
          int lnext_true = code.newLabel();
              match(Tag.IF);
              match('(');
              bexpr(lnext_true, false);
              match(')');
              code.emit(OpCode.GOto, lnext_false);
              code.emitLabel(lnext_true);
              stat();
              code.emit(OpCode.GOto, lnext_end);
              switch (look.tag) { //unisco a statp
                case Tag.ELSE:
          				code.emitLabel(lnext_false);
                  match(Tag.ELSE);
                  stat();
                  code.emitLabel(lnext_end);
                  match(Tag.END);
                  break;
                case Tag.END:
                  code.emitLabel(lnext_false);
                  code.emitLabel(lnext_end);
                  match(Tag.END);
                  break;
                default:
                  error("Error in stat");
              }
          break;

        case '{':
          match ('{');
          statlist();
          match ('}');
          break;

        default:
          if(look.tag==Tag.EOF){
            break;
          }else{
          error("Error in stat");}
        }
      }


  private List<String> idlist() {
    List<String> ids = new LinkedList<>();
    if (look.tag == Tag.ID) {
      ids.add(((Word) look).lexeme);
    }
    match(Tag.ID);
    idlistp(ids);
    return ids;
  }


  private void idlistp(List<String> ids) {
    if (look.tag == ',') {
      match(',');
      if (look.tag == Tag.ID) {
        ids.add(((Word) look).lexeme);
      }
      match(Tag.ID);
      idlistp(ids);
    }
  }


  private void bexpr(int lnext, boolean result) {
    Token t = look;
    OpCode cond = OpCode.if_icmpeq;
        match(Tag.RELOP);
        expr();
  		  expr();
        switch(((Word)t).lexeme){
            case "==":
              code.emit(cond = OpCode.if_icmpeq, lnext);
              break;
            case "<>":
              code.emit(cond = OpCode.if_icmpne, lnext);
              break;
            case "<":
              code.emit(cond = OpCode.if_icmplt, lnext);
              break;
            case "<=":
              code.emit(cond = OpCode.if_icmple, lnext);
              break;
            case ">":
              code.emit(cond = OpCode.if_icmpgt, lnext);
              break;
            case ">=":
              code.emit(cond = OpCode.if_icmpge, lnext);
              break;
          default:
            error("Error in grammar (bexprp)");
        }
		}


  private void expr(  ) {
    switch(look.tag) {
      case '+':
        match ('+');
        match ('(');
        exprlist(new Instruction(OpCode.iadd));
        code.emit(OpCode.iadd);
        match (')');
        break;
      case '-':
        match('-');
        expr();
        expr();
        code.emit(OpCode.isub);
        break;
      case '*':
        match('*');
        match ('(');
        exprlist(new Instruction(OpCode.imul));
        code.emit(OpCode.imul);
        match (')');
        break;
      case '/':
        match('/');
        expr();
        expr();
        code.emit(OpCode.idiv);
        break;
      case Tag.NUM:
        code.emit(OpCode.ldc, ((NumberTok) look).lexeme);
        match(Tag.NUM);
				break;
			case Tag.ID:
				int read_id_addr = st.lookupAddress(((Word)look).lexeme);
				if(read_id_addr != -1)
				  code.emit(OpCode.iload, read_id_addr);
				else
				  error("Variable doesn't exist!");
				match(Tag.ID);
				break;
        default:
          if(look.tag==Tag.EOF){
            break;
          }else{
          error("Error in stat");}
    }
  }


  private void exprlist(Instruction instruction) {
        expr();
        exprlistp(instruction);
      }


  private void exprlistp(Instruction instruction) {
      switch (look.tag) {
        case ',':
          match(',');
          expr();
          exprlistp(instruction);
          break;
        case ')':
          break;
        default:
            error ("error in exprlisp");
      }
    }


  public static void main(String[] args) {
    Lexer lex = new Lexer();
    String path = "max_tre_num.lft";
    try {
        BufferedReader br = new BufferedReader(new FileReader(path));
        Translator traduttore = new Translator(lex, br);
        traduttore.prog();
        br.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
}
}
