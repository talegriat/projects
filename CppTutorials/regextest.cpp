#include <iostream>
#include <string>
#include <regex>
using namespace std;
 
int main () {

    regex str_pgnExpr ("(((\\d+)(\\.)) ((([PNBRQK]?)(([a-h]?)([1-8]?)?)([x]?)(([a-h])([1-8]))(=[NBRQ]+)?|(O\\-O\\-O|O\\-O))(\\+|\\#)?)  ((([PNBRQK]?)(([a-h]?)([1-8]?)?)([x]?)(([a-h])([1-8]))(=[NBRQ]+)?|(O\\-O\\-O|O\\-O))(\\+|\\#)?))|(([10][\\-][10])|(1\\/2[\\-]1\\/2))*"); 
 

 
    const char gmStr[] = "1. d4  Nf6 2. Nf3  d5 3. Bf4  c5 4. e3  Nc6 5. Nbd2  cxd4 6. exd4  Qb6 7. Nb3  Bf5 8. Be2  e6 9. O-O  Be7 10. a4  a6 11. a5  Qd8 12. Ne5  Rc8 13. c3  O-O 14. Re1  Ne4 15. Bd3  Nxe5 16. Bxe5  Bg6 17. Bf4  Nd6 18. Bxg6  hxg6 19. Bxd6  Bxd6 20. g3  b5 21. axb6  Qxb6 22. Re2  Rb8 23. Nc1  a5 24. Nd3  Qb5 25. h4  Rfc8 26. Rd2  Ra8 27. h5  gxh5 28. Qxh5  g6 29. Qh6  a4 30. Kg2  Bf8 31. Qf4  Bg7 32. Ne5  Qe8 33. Rd3  f6 34. Ng4  Qf8 35. Rf3  a3 36. bxa3  f5 37. Qg5  Kf7 38. Rh1  Rxa3 39. Rh7  Rcxc3 40. Nh6+  Ke8 41. Qxg6+  Kd8 1-0";
    cmatch gm;
    regex_search (gmStr,gm,str_pgnExpr);
    cout << "the game moves are: ";
    cout<< gm[0]<< endl;
    cout<< gm[1]<< endl;
    cout<< gm[2]<< endl;    
    cout<< gm[3]<< endl;
    cout<< gm[4]<< endl;    
    cout<< gm[5]<< endl;
   




    string gmstr ("1. Nd4xe3+  Nf6++ 2. Nf3  d5 3. Bf4  c5 4. e3  Nc6 5. Nbd2  cxd4 6. exd4  Qb6 7. Nb3  Bf5 8. Be2  e6 9. O-O  Be7 10. a4  a6 11. a5  Qd8 12. Ne5  Rc8 13. c3  O-O 14. Re1  Ne4 15. Bd3  Nxe5 16. Bxe5  Bg6 17. Bf4  Nd6 18. Bxg6  hxg6 19. Bxd6  Bxd6 20. g3  b5 21. axb6  Qxb6 22. Re2  Rb8 23. Nc1  a5 24. Nd3  Qb5 25. h4  Rfc8 26. Rd2  Ra8 27. h5  gxh5 28. Qxh5  g6 29. Qh6  a4 30. Kg2  Bf8 31. Qf4  Bg7 32. Ne5  Qe8 33. Rd3  f6 34. Ng4  Qf8 35. Rf3  a3 36. bxa3  f5 37. Qg5  Kf7 38. Rh1  Rxa3 39. Rh7  Rcxc3 40. Nh6+  Ke8 41. Qxg6+  Kd8 1-0");
    string gmstr1 ("1. Nd4xe3+  Nf6++ ");
    string gmstr2 ("13. c3  O-O ");
    string gmstr3 ("14. c3  O-O-O ");
    string gmstr4 ("15. O-O  d3 ");
    string gmstr5 ("16. O-O-0  d3 ");
    string gmstr6 ("1-0");
    string gmstr7 ("0-1");
    string gmstr8 ("1/2-1/2");
  
    smatch xm;
    regex_search (gmstr1,xm,str_pgnExpr);

    cout << gmstr1<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }


    regex_search (gmstr2,xm,str_pgnExpr);

    cout << gmstr2<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }

        regex_search (gmstr3,xm,str_pgnExpr);

    cout << gmstr3<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }

        regex_search (gmstr4,xm,str_pgnExpr);

    cout << gmstr4<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }

        regex_search (gmstr5,xm,str_pgnExpr);

    cout << gmstr5<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }

        regex_search (gmstr6,xm,str_pgnExpr);

    cout << gmstr6<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }

        regex_search (gmstr7,xm,str_pgnExpr);

    cout << gmstr7<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }

        regex_search (gmstr8,xm,str_pgnExpr);

    cout << gmstr8<<endl;
    cout << "the matches are: "<<xm.size()<<endl;
    for (unsigned i=0; i<xm.size(); ++i) {
      cout << i << '-' << "[" << xm[i] << "] "<<endl;
    }

   return 0;
}